#-*- coding:utf-8 -*-

import os
try:
    import xml.etree.cElementTree as ET
except ImportError:
    import xml.etree.ElementTree as ET
from xml.dom import minidom

try:
    register_namespace = ET.register_namespace
except AttributeError:
    def register_namespace(prefix, uri):
        ET._namespace_map[uri] = prefix

android_namespace_uri = "http://schemas.android.com/apk/res/android"
android_namespace_dct = {"android" : android_namespace_uri}
android_namespace_tag = "{%s}" %(android_namespace_uri)
register_namespace("android", android_namespace_uri)

class XMLUtil:

    # elemnt为传进来的Elment类，参数indent用于缩进，newline用于换行    
    @staticmethod
    def prettyXML(element, indent = "    ", newline = "\n", level = 0):
        if element:  # 判断element是否有子元素    
            if element.text == None or element.text.isspace(): # 如果element的text没有内容    
                element.text = newline + indent * (level + 1)
            else:
                element.text = newline + indent * (level + 1) + element.text.strip() + newline + indent * (level + 1)
        temp = list(element) # 将elemnt转成list    
        for subelement in temp:
            if temp.index(subelement) < (len(temp) - 1): # 如果不是list的最后一个元素，说明下一个行是同级别元素的起始，缩进应一致    
                subelement.tail = newline + indent * (level + 1)
            else:  # 如果是list的最后一个元素， 说明下一行是母元素的结束，缩进应该少一个    
                subelement.tail = newline + indent * level
            XMLUtil.prettyXML(subelement, indent, newline, level = level + 1) # 对子元素进行递归操作
        return ET.tostring(element, 'utf-8') #要转化的xml文件


    @staticmethod
    def parseXML(a_xml) :
        if os.path.isfile(a_xml) :
            return ET.parse(a_xml).getroot()
        else :
            return ET.fromstring(a_xml)


    @staticmethod
    def mergeXML(a_xml, other_xml) :
        a_xml_root = XMLUtil.parseXML(a_xml)
        other_xml_root = XMLUtil.parseXML(other_xml)
        for child_element in other_xml_root :
            a_xml_root.append(child_element)
        return a_xml_root


    @staticmethod
    def new_element(tag) :
        return ET.Element(tag)


    @staticmethod
    def find_element(element, condition, with_namespace = True) :
        if with_namespace :
            return element.find(condition, android_namespace_dct)
        else :
            return element.find(condition)

 
    @staticmethod
    def set_element_attr(element, name, value, with_namespace = True) :
        if with_namespace :
            name = android_namespace_tag + name
        element.set(name, value)
        return element



