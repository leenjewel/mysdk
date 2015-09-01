#-*- coding:utf-8 -*-
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
#  }
#-------------------------------------------
class SDKConfig :

    def __init__(self, config) :
        if os.path.isfile(config) :
            self.config = json.load(open(config, "r"), "utf-8")
        else:
            self.config = json.loads(config, "utf-8")


    def getConfig(self, name, default = None) :
        return self.config.get(name, default)


    def get_sdk_class_path(self) :
        sdk_id = self.getConfig("id")
        sdk_package = self.getConfig("package")
        sdk_class = self.getConfig("class")
        if None == sdk_id or len(sdk_id) == 0 :
            raise Exception("SDK ID is empty.")
        if None == sdk_package or len(sdk_package) == 0 :
            sdk_package = "com.leenjewel.mysdk.sdk"
        if None == sdk_class or len(sdk_class) == 0 :
            sdk_class = "%sMySDK"  %(sdk_id.lower().capitalize())
        return "%s.%s"  %(sdk_package, sdk_class)

