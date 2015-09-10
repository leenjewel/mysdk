#-*- coding:utf-8 -*-
#
# Copyright [2015] [leenjewel]
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

import json
import os

#-------------------------------------------
#  SDK Config Template
#  {
#      id          : "sdk-id",
#      package     : "sdk-package",
#      class       : "sdk-class",
#      name        : "sdk-name",
#      description : "sdk-description",
#      author      : "sdk-author",
#      email       : "sdk-author-email",
#      site        : "sdk-site-url",
#      icon        : "sdk-icon-file",
#      src         : ["src"],
#  }
#-------------------------------------------
class SDKConfig :

    def __init__(self, sdk_path) :
        self.sdk_path = sdk_path
        config = os.path.join(self.sdk_path, "mysdk.conf")
        if os.path.isfile(config) :
            fp = open(config, "r")
            self.config = json.load(fp, "utf-8")
            fp.close()
        else :
            raise Exception("%s is not a SDK Project"  %(str(sdk_path)))


    def get_config(self, name, default = None) :
        return self.config.get(name, default)


    def get_sdk_class_path(self) :
        sdk_id = self.get_config("id")
        sdk_package = self.get_config("package")
        sdk_class = self.get_config("class")
        if None == sdk_id or len(sdk_id) == 0 :
            raise Exception("SDK ID is empty.")
        if None == sdk_package or len(sdk_package) == 0 :
            sdk_package = "com.leenjewel.mysdk.sdk"
        if None == sdk_class or len(sdk_class) == 0 :
            sdk_class = "%sMySDK"  %(sdk_id.lower().capitalize())
        return "%s.%s"  %(sdk_package, sdk_class)

