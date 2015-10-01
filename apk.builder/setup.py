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

from setuptools import setup

setup(
    name = "mysdk",
    version = "0.0.1",
    keywords = ("mysdk", "sdk"),
    description = "MySDK is a framework",
    license = "http=//www.apache.org/licenses/LICENSE-2.0",

    url = "http=//mysdk.leenjewel.io",
    author = "leenjewel",
    author_email = "leenjewel@gmail.com",

    packages = [
        "pyMySDKAPKBuilder",
        "pyMySDKWebFrontEnd",
        "pyMySDKWebFrontEnd.handler",
        "pyMySDKWebFrontEnd.module",
    ],
    package_data = {
        "pyMySDKAPKBuilder" : [
            "jar/baksmali.jar",
            "jar/apktool.jar",
        ],
        "pyMySDKWebFrontEnd" : [
            "templates/*.html",
            "templates/layouts/*",
            "templates/ui/*",
            "resources/css/*",
            "resources/js/*",
            "resources/fonts/*",
        ],
    },
    include_package_data = True,
    platforms = "any",
    install_requires = ["tornado"],
    scripts = ["bin/mysdk.py"]
)

