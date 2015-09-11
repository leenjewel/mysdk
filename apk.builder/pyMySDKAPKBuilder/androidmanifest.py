#-*- coding:utf-8 -*-
#
# Copyright 2015 leenjewel
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

from xmlutil import *

class AndroidManifest :

    def __init__(self, android_manifest_xml) :
        self.manifest_root = XMLUtil.parse_xml(android_manifest_xml)
        self.application_root = self.manifest_root.find("application")


    def get_manifest_element(self) :
        return self.manifest_root


    def get_application_element(self) :
        return self.application_root


    def get_package_name(self) :
        return self.manifest_root.get("package")


    def set_package_name(self, package_name) :
        return self.manifest_root.set("package", package_name)


    def has_uses_permission(self, permission, tag = "uses-permission") :
        condition = "%s[@android:name='%s']"  %(tag, permission)
        uses_permission = XMLUtil.find_element(self.manifest_root, condition)
        if None == uses_permission :
            return False
        return True


    def add_uses_permission(self, permission, tag = "uses-permission") :
        uses_permission = None
        if not self.has_uses_permission(permission, tag) :
            uses_permission = XMLUtil.new_element(tag)
            XMLUtil.set_element_attr(uses_permission, "name", permission)
            self.manifest_root.insert(0, uses_permission)
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


    def save(self, save_path) :
        fp = open(save_path, "w")
        fp.write(XMLUtil.pretty_xml(self.manifest_root))
        fp.close()


    def merge(self, other_manifest) :
        other_manifest_root = XMLUtil.parse_xml(other_manifest)
        for child_element in other_manifest_root :
            if child_element.tag == "uses-permission" :
                self.add_uses_permission(XMLUtil.get_element_attr(child_element, "name"))
            elif child_element.tag == "application" :
                for application_child_element in child_element :
                    self.application_root.append(application_child_element)
            else :
                self.manifest_root.append(child_element)



