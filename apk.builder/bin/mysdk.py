#!/usr/bin/env python
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

import sys,os,argparse
try :
    from pyMySDKAPKBuilder.workspace import WorkSpace
    from pyMySDKAPKBuilder.apkbuilder import APKBuilder
except ImportError :
    pwd = os.path.split(os.path.realpath(__file__))[0]
    sys.path.append(os.path.abspath(os.path.join(pwd, os.pardir)))
    from pyMySDKAPKBuilder.workspace import WorkSpace
    from pyMySDKAPKBuilder.apkbuilder import APKBuilder

if __name__ == '__main__' :

    parser = argparse.ArgumentParser()

    sdk_list_help = 'SDK_ID  SDK_ID  SDK_ID...'
    parser.add_argument("sdk_list", nargs = "*", help = sdk_list_help)

    sdk_path_help = 'SDK search dirs'
    parser.add_argument("--sdk-path", dest = "sdk_path", nargs = "*", help = sdk_path_help)

    work_space_help = 'Work space path'
    parser.add_argument("--work-space", dest = "work_space", default = os.getcwd(), help = work_space_help)

    apk_path_help = 'Android APK file path'
    parser.add_argument("--apk-path", dest = "apk_path", help = apk_path_help)

    output_help = 'Output Android APK file path'
    parser.add_argument("--output", help = output_help)

    android_platform_help = 'Android platform'
    parser.add_argument("--platform", help = android_platform_help)

    keystore_help = 'Android Keystore file path'
    parser.add_argument("--keystore", help = keystore_help)

    storepass_help = 'Android Keystore store password'
    parser.add_argument("--storepass", help = storepass_help)

    storealias_help = 'Android Keystore alias'
    parser.add_argument("--alias", help = storealias_help)

    keypass_help = "Android Keystore private password"
    parser.add_argument("--keypass", help = keypass_help)

    name_help = 'Project name'
    parser.add_argument("--name", help = name_help)

    meta_data_help = 'Meta data'
    parser.add_argument("--meta-data", nargs = "*", dest = "meta_data", help = meta_data_help)

    package_name_help = 'Android application package name'
    parser.add_argument("--package", help = package_name_help)

    args = parser.parse_args()

    if not os.path.exists(args.work_space) :
        os.makedirs(args.work_space)
    name = args.name
    if None == args.name or len(args.name) == 0 :
        for path, dirs, files in os.walk(args.work_space) :
            if len(dirs) == 0 :
                raise Exception("need project name")
            name = dirs[0]
            break
    work_space = WorkSpace(name, args.work_space)

    work_space.init_apk(args.apk_path)

    work_space.init_sdk(args.sdk_list, args.sdk_path)

    if args.platform :
        work_space.init_android_platform(args.platform)

    if args.meta_data and len(args.meta_data) > 0 :
        for meta_data_str in args.meta_data :
            if "&" in meta_data_str :
                meta_data_list = meta_data_str.split("&")
            else :
                meta_data_list = [meta_data_str]
            for meta_data_kv in meta_data_list :
                meta_data_kv = meta_data_kv.split("=")
                if len(meta_data_kv) > 1 :
                    work_space.init_metadata(meta_data_kv[0], meta_data_kv[1])
                else :
                    work_space.init_metadata(meta_data_kv[0])

    if args.package :
        work_space.init_metadata("{{PACKAGE}}", args.package)

    work_space.init_keystore(args.keystore, args.storepass, args.alias, args.keypass)

    apk_builder = APKBuilder(work_space)
    apk_builder.build()

    work_space.save()

