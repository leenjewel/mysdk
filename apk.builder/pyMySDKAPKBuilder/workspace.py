# -*- coding:utf-8 -*-
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

import os
import json
import shutil
from sdkconfig import SDKConfig

class WorkSpace(object) :

    def __init__(self, name, root = None) :
        if None == root :
            self.root = os.getcwd()
        else :
            self.root = root
        self.context = {
                "sdk_search_path" : [],
                "sdk_id_list" : [],
        }
        self.init_work_space(name, root)
        self.init_android_sdk()
        self.init_java_sdk()
        self.init_apktool()


    def init_work_space(self, name, root) :
        self.name = name
        self.root = root
        work_dir = os.path.join(root, name)
        if not os.path.exists(work_dir) :
            os.mkdir(work_dir)
        self.context["work_dir"] = work_dir
        work_space_json = os.path.join(work_dir, "workspace.json")
        if os.path.isfile(work_space_json) :
            self.open(work_space_json)


    def is_exe(self, file_path) :
        return (os.path.isfile(file_path) and os.access(file_path, os.X_OK))


    def which(self, exe, path = None) :
        file_path, file_name = os.path.split(exe)
        if file_path :
            if self.is_exe(exe):
                return exe
        else :
            if None == path :
                path = os.environ["PATH"]
            for file_path in path.split(os.pathsep) :
                file_path = file_path.strip('"')
                exe_file = os.path.join(file_path, exe)
                if self.is_exe(exe_file) :
                    return exe_file
        return None


    def init_android_sdk(self) :
        tools = ["aapt", "dx", "zipalign"]
        for tool in tools :
            find_path = self.which(tool)
            if None == find_path :
                android_sdk_root = os.environ.get("ANDROID_SDK_ROOT")
                if None == android_sdk_root :
                    raise Exception("ANDROID_SDK_ROOT not found.")
                android_build_tool = os.path.join(android_sdk_root, "build-tools")
                android_build_ver = {}
                for path, dirs, files in os.walk(android_build_tool) :
                    for build_ver_dir in dirs :
                        ver = int("".join([(max(0, 6-len(v))*"0")+v for v in build_ver_dir.split(".")]))
                        android_build_ver[ver] = build_ver_dir
                    break
                android_build_dir = os.path.join(android_build_tool, android_build_ver[max(android_build_ver.keys())])
                find_path = self.which(tool, android_build_dir)
            if None == find_path :
                raise Exception("Android SDK not found.")
            break

        find_dir = os.path.split(find_path)[0]
        self.context["android_sdk_root"] = os.path.abspath(os.path.join(find_dir, os.pardir, os.pardir))
        for tool in tools :
            self.context[tool] = os.path.abspath(os.path.join(find_dir, tool))


    def init_java_sdk(self) :
        tools = ["java", "javac", "jar", "jarsigner"]
        for tool in tools :
            find_path = self.which(tool)
            if None == find_path :
                raise Exception("Java SDK not found.")
            self.context[tool] = os.path.abspath(find_path)


    def init_apktool(self) :
        pwd = os.path.split(os.path.realpath(__file__))[0]
        self.context["apktool"] = os.path.abspath(os.path.join(pwd, "jar", "apktool.jar"))
        self.context["baksmali"] = os.path.abspath(os.path.join(pwd, "jar", "baksmali.jar"))


    def init_apk(self, apk_file = None) :
        if not isinstance(apk_file, str) or not os.path.isfile(apk_file) :
            if self.context.has_key("apk_path") and os.path.isfile(self.context["apk_path"]) :
                apk_file = self.context["apk_path"]
            else :
                raise Exception("Android APK file not found.")
        apk_file_path, apk_file_name = os.path.split(apk_file)
        work_apk_file = os.path.join(self.context["work_dir"], apk_file_name)
        if not os.path.isfile(work_apk_file) :
            shutil.copy(apk_file, work_apk_file)
        self.context["apk_path"] = os.path.abspath(work_apk_file)


    def init_sdk(self, sdk_list = None, sdk_path_list = None) :
        self.context["sdk_list"] = []
        sdks = {}

        sdk_search_paths = self.context["sdk_search_path"]
        if isinstance(sdk_path_list, list) :
            sdk_search_paths += sdk_path_list
        sdk_search_paths = list(set(sdk_search_paths))

        if not isinstance(sdk_list, list) or len(sdk_list) == 0:
            sdk_list = self.context["sdk_id_list"]

        for sdk_search_path in sdk_search_paths :
            self.context["sdk_search_path"].append(sdk_search_path)
            for path, dirs, files in os.walk(sdk_search_path) :
                for sdk_dir in dirs :
                    sdk_path = os.path.join(path, sdk_dir)
                    try :
                        sdk = SDKConfig(sdk_path)
                        sdk_id = sdk.get_config("id")
                        if not sdks.has_key(sdk_id) and sdk_id in sdk_list :
                            sdks[sdk_id] = sdk
                    except :
                        continue
                break
        for sdk_id in sdk_list :
            if not sdks.has_key(sdk_id) :
                raise Exception("SDK %s not found."  %(sdk_id))
            self.context["sdk_list"].append(sdks[sdk_id])
        self.context["sdk_search_path"] = sdk_search_paths


    def get_context(self) :
        return self.context


    def open(self, json_path) :
        fp = open(json_path, "r")
        out = json.load(fp, "utf-8")
        for k, v in out.items() :
            self.context[k] = v
        fp.close()


    def save(self, save_path = None) :
        out = {
            "sdk_id_list" : [sdk.get_config("id") for sdk in self.context["sdk_list"]],
            "sdk_search_path" : list(set(self.context["sdk_search_path"])),
            "apk_path" : self.context["apk_path"],
        }
        if None == save_path :
            save_path = (os.path.join(self.context["work_dir"], "workspace.json"))
        fp = open(save_path, "w")
        json.dump(out, fp)
        fp.close()


