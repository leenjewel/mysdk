#!/usr/bin/env python
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

    work_space_help = 'work space path'
    parser.add_argument("--work-space", dest = "work_space", default = os.getcwd(), help = work_space_help)

    apk_path_help = 'Android APK file path'
    parser.add_argument("--apk-path", dest = "apk_path", help = apk_path_help)

    output_help = 'Output Android APK file path'
    parser.add_argument("--output", help = output_help)

    name_help = 'Project name'
    parser.add_argument("--name", help = name_help)

    args = parser.parse_args()


    work_space = WorkSpace(args.name, args.work_space)

    if None == args.apk_path :
        raise Exception("APK file not found.")
    work_space.init_apk(args.apk_path)

    work_space.init_sdk(args.sdk_list, args.sdk_path)

    apk_builder = APKBuilder(work_space)
    apk_builder.build()

