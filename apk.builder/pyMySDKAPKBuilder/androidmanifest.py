#-*- coding:utf-8 -*-
from xmlutil import *

class AndroidManifest :

    def __init__(self, android_manifest_xml) :
        self.manifest_root = XMLUtil.parseXML(android_manifest_xml)
        self.application_root = self.manifest_root.find("application")


    def get_package_name(self) :
        return self.manifest_root.get("package")


    def set_package_name(self, package_name) :
        return self.manifest_root.set("package", package_name)


    def has_uses_permission(self, permission, tag = "uses-permission") :
        condition = "%s[@android:name='%s']"  %(tag, permission)
        uses_permission = XMLUtil.find_element(self.manifest, condition)
        if None == uses_permission :
            return False
        return True


    def add_uses_permission(self, permission, tag = "uses-permission") :
        uses_permission = None
        if not self.has_uses_permission(permission, tag) :
            uses_permission = XMLUtil.new_element(tag)
            XMLUtil.set_element_attr(uses_permission, name, permission)
            self.manifest.insert(0, uses_permission)
        return uses_permission


    def get_meta_data(self, name) :
        condition = "meta-data[@android:name='%s']"  %(name)
        return XMLUtil.find_element(self.application_root, condition)


    def add_meta_data(self, name, value) :
        meta_data = self.get_meta_data(name)
        if None == meta_data :
            meta_data = XMLUtil.new_element("meta-data")
            XMLUtil.set_element_attr(meta_data, "name", name)
            self.application_root.insert(0, meta_data)
        XMLUtil.set_element_attr(meta_data, "value", value)
        return meta_data


