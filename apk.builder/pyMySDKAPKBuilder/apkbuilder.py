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

import os
import json
import shutil
from command import CommandUtil
from xmlutil import XMLUtil
from androidmanifest import AndroidManifest
from sdkconfig import SDKConfig

class APKBuilderContext(object) :

    def __init__(self, init_dct = {}) :
        self.context = {}
        for k,v in init_dct.items() :
            self.context[k] = v


    def __getattr__(self, key) :
        return self.context.get(key)


    def __setattr__(self, key, val) :
        if "context" == key :
            super(APKBuilderContext, self).__setattr__(key, val)
        else:
            self.context[key] = val




class APKBuilder :

    def __init__(self, work_space) :
        self.context = APKBuilderContext(work_space.get_context())
        self.context.pwd = os.path.split(os.path.realpath(__file__))[0]
        self.check(self.context)


    def build(self) :
        context = self.decode_apk(self.context)
        context = self.parse_manifest(context)

        for sdk_config in context.sdk_list :
            context = self.sdk_check(context, sdk_config)
            context = self.sdk_manifest(context, sdk_config)
            context = self.sdk_permission(context, sdk_config)
            context = self.sdk_libs(context, sdk_config)
            context = self.sdk_setup(context, sdk_config)

        context = self.finish_manifest(context)
        context = self.write_manifest(context)
        context = self.write_mysdk_config(context)

        for sdk_config in context.sdk_list :
            context = self.sdk_build_res(context, sdk_config)
            context = self.sdk_build_src(context, sdk_config)

        context = self.javac_R(context)
        context = self.jar_class(context, context.apk_dir, "bin")
        context = self.dex_jar(context, context.apk_dir)
        context = self.aapt_res_assets(context)
        context = self.rebuild_apk(context)
        if context.keystore and os.path.isfile(context.keystore) :
            context = self.sign_apk(context, context.keystore, context.storepass, context.alias, context.keypass)
            context = self.align_apk(context)
        context = self.clean(context)
        return context


    def check(self, context) :
        android_platforms = os.path.join(context.android_sdk_root, "platforms")
        if None == context.android_platform or \
            not os.path.exists(os.path.join(android_platforms, context.android_platform)) :
                raise Exception("Android platform %s not found."  %(str(context.android_platform)))
        context.sdk_config_list = []
        context.mysdk_config = {
            "sdk_list" : [],
            "sdk_config" : {},
        }
        return context


    def decode_apk(self, context) :
        apk_dir = os.path.split(os.path.realpath(context.apk_path))[0]
        out_dir = os.path.join(apk_dir, "out")
        if not os.path.exists(out_dir) :
            os.makedirs(out_dir)
        commands = [
            context.java, "-jar",
            "-Xmx512M", "-Djava.awt.headless=true",
            context.apktool, "-f",
            "--output", out_dir,
            "d", context.apk_path,
        ]
        error = CommandUtil.run(*commands)
        if error != None :
            exception = "APKBuilder decode apk %s ERROR:\n%s\n%s"  %(context.apk_path, " ".join(commands), error)
            raise Exception(exception)
        context.apk_dir = out_dir
        apk_manifest_xml = os.path.join(context.apk_dir, "AndroidManifest.xml")
        context.apk_manifest = AndroidManifest(apk_manifest_xml)
        return context


    def parse_manifest(self, context) :
        apk_application_element = context.apk_manifest.get_application_element()
        context.apk_activity_main = XMLUtil.find_element(apk_application_element, "activity/intent-filter/action[@android:name='android.intent.action.MAIN']/../..")
        context.apk_activity_main_filter = XMLUtil.find_element(context.apk_activity_main, "intent-filter/action[@android:name='android.intent.action.MAIN']/..")
        context.apk_activity_main.remove(context.apk_activity_main_filter)

        context.meta_data["LAUNCH_ACTIVITY"] = XMLUtil.get_element_attr(context.apk_activity_main, "name")
        if (not context.meta_data.has_key("PACKAGE")) :
            context.meta_data["PACKAGE"] = context.apk_manifest.get_package_name()
        else :
            context.apk_manifest.set_package_name(context.meta_data["PACKAGE"])
        return context


    def sdk_check(self, context, sdk_config) :
        meta_data, error_key = sdk_config.check_metadata(context.meta_data)
        if False == meta_data :
            raise Exception("APKBulder sdk_check:\n%s meta_data %s check fail."  %(sdk_config.get_config("id"), str(error_key)))
        context.meta_data = meta_data
        return context


    def sdk_manifest(self, context, sdk_config) :
        sdk_path = sdk_config.sdk_path
        sdk_android_manifest = os.path.join(sdk_path, "sdk_android_manifest.xml")
        if os.path.isfile(sdk_android_manifest) :
            fp = open(sdk_android_manifest, "r")
            sdk_android_manifest_data = fp.read()
            fp.close()
            for key, val in context.meta_data.items() :
                sdk_android_manifest_data = sdk_android_manifest_data.replace("{{"+key+"}}", val)
            context.apk_manifest.merge(sdk_android_manifest_data)
        return context


    def sdk_permission(self, context, sdk_config) :
        sdk_path = sdk_config.sdk_path
        sdk_uses_permission = os.path.join(sdk_path, "sdk_uses_permission.xml")
        if os.path.isfile(sdk_uses_permission) :
            fp = open(sdk_uses_permission, "r")
            sdk_uses_permission_data = fp.read()
            fp.close()
            for key, val in context.meta_data.items() :
                sdk_uses_permission_data = sdk_uses_permission_data.replace("{{"+key+"}}", val)
            context.apk_manifest.merge(sdk_uses_permission_data)
        return context


    def sdk_libs(self, context, sdk_config) :
        apk_lib = os.path.join(context.apk_dir, "lib")
        if not os.path.exists(apk_lib) :
            os.mkdir(apk_lib)
        sdk_path = sdk_config.sdk_path
        lib_find_paths = ["lib", "libs"]
        for lib_find_path in lib_find_paths :
            sdk_lib = os.path.join(sdk_path, lib_find_path)
            if not os.path.exists(sdk_lib) :
                continue
            for path, dirs, files in os.walk(sdk_lib) :
                for lib_dir in dirs :
                    mkdir = os.path.join(apk_lib, lib_dir)
                    if not os.path.exists(mkdir) :
                        os.mkdir(mkdir)
                for lib_file in files :
                    if ".so" == lib_file[-3:] :
                        mkfile = os.path.join(apk_lib, path.replace(sdk_lib, "."), lib_file)
                        if not os.path.isfile(mkfile) :
                            shutil.copy(os.path.join(path, lib_file), mkfile)
        return context


    def sdk_setup(self, context, sdk_config) :
        sdk_id = sdk_config.get_config("id")
        context.mysdk_config["sdk_list"].append(sdk_id)
        context.mysdk_config["sdk_config"][sdk_id] = {
                "class_path" : sdk_config.get_sdk_class_path(),
        }
        return context


    def sdk_build_res(self, context, sdk_config) :
        self.aapt_package_R(context, sdk_config.sdk_path)
        return context


    def sdk_build_src(self, context, sdk_config) :
        src = sdk_config.get_config("src")
        if None == src :
            src = "src"
        self.javac_class(context, sdk_config.sdk_path, src)
        return context



    def finish_manifest(self, context) :
        apk_application_element = context.apk_manifest.get_application_element()
        apk_launch_activity = XMLUtil.find_element(apk_application_element, "activity/intent-filter/action[@android:name='android.intent.action.MAIN']/../..")
        if None == apk_launch_activity :
            context.apk_activity_main.insert(0, context.apk_activity_main_filter)
        return context


    def write_manifest(self, context) :
        save_path = os.path.join(context.apk_dir, "AndroidManifest.xml")
        context.apk_manifest.save(save_path)
        return context


    def write_mysdk_config(self, context) :
        apk_assets = os.path.join(context.apk_dir, "assets")
        if not os.path.exists(apk_assets) :
            os.mkdir(apk_assets)
        mysdk_config = os.path.join(apk_assets, "mysdk.conf")
        fp = open(mysdk_config, "w")
        json.dump(context.mysdk_config, fp)
        fp.close()
        return context


    def aapt_package_R(self, context, project_path) :
        gen_dir = os.path.join(context.apk_dir, "gen")
        if not os.path.exists(gen_dir) :
            os.mkdir(gen_dir)
        commands = [
            context.aapt,
            "package",
            "-m",
            "--auto-add-overlay",
            "-J", gen_dir,
            "-M", os.path.join(project_path, "AndroidManifest.xml"),
            "-I", os.path.join(context.android_sdk_root, "platforms", context.android_platform, "android.jar"),
            "-S", os.path.join(context.apk_dir, "res"),
        ]
        res_dir = (os.path.join(project_path, "res"))
        if os.path.exists(res_dir) :
            commands.append("-S")
            commands.append(res_dir)

        error = CommandUtil.run(*commands)
        if error :
            raise Exception("APKBuilder aapt_package(%s) ERROR:\n%s\n%s"  %(project_path, " ".join(commands), error))
        return context


    def aapt_res_assets(self, context) :
        resources_apk = os.path.join(context.apk_dir, "resources._ap")
        commands = [
            context.aapt,
            "package",
            "-f",
            "--auto-add-overlay",
            "-M", os.path.join(context.apk_dir, "AndroidManifest.xml"),
            "-I", os.path.join(context.android_sdk_root, "platforms", context.android_platform, "android.jar"),
            "-F", resources_apk,
            "-S", os.path.join(context.apk_dir, "res"),
            "-A", os.path.join(context.apk_dir, "assets"),
        ]
        for sdk in context.sdk_list :
            sdk_res_path = os.path.join(sdk.sdk_path, "res")
            if os.path.exists(sdk_res_path) :
                commands.append("-S")
                commands.append(sdk_res_path)
            sdk_assets_path = os.path.join(sdk.sdk_path, "assets")
            if os.path.exists(sdk_assets_path) :
                commands.append("-A")
                commands.append(sdk_assets_path)

        error = CommandUtil.run(*commands)
        if error :
            raise Exception("APKBuilder aapt_res_assets ERROR:\n%s\n%s"  %(" ".join(commands), error))
        context.resources_apk = resources_apk

        resources_out = os.path.join(context.apk_dir, "resources_out")
        commands = [
            context.java, "-jar",
            context.apktool,
            "-f",
            "d", context.resources_apk,
            "-o", resources_out
        ]
        error = CommandUtil.run(*commands)
        if error :
            raise Exception("APKBuilder aapt_res_assets ERROR:\n%s\n%s"  %(" ".join(commands), error))
        if os.path.exists(os.path.join(resources_out, "assets")) :
            shutil.rmtree(os.path.join(context.apk_dir, "assets"))
            shutil.copytree(os.path.join(resources_out, "assets"), os.path.join(context.apk_dir, "assets"))
        if os.path.exists(os.path.join(resources_out, "res")) :
            shutil.rmtree(os.path.join(context.apk_dir, "res"))
            shutil.copytree(os.path.join(resources_out, "res"), os.path.join(context.apk_dir, "res"))
        return context


    def javac_class(self, context, project_path, src_path) :
        gen_dir = os.path.join(context.apk_dir, "gen")
        bin_dir = os.path.join(context.apk_dir, "bin")
        if not os.path.exists(bin_dir) :
            os.mkdir(bin_dir)
        commands = [
            context.javac,
            "-target", "1.7",
            "-source", "1.7",
            "-classpath", gen_dir,
            "-bootclasspath", os.path.join(context.android_sdk_root, "platforms", context.android_platform, "android.jar"),
            "-d", bin_dir
        ]
        libs_dir = os.path.join(project_path, "libs")
        if os.path.exists(libs_dir) :
            commands.append("-extdirs")
            commands.append(libs_dir)

        if not isinstance(src_path, list) :
            src_path = [src_path]
        for src in src_path :
            src_dir = os.path.join(project_path, src)
            if os.path.exists(src_dir) :
                for path, dirs, files in os.walk(src_dir) :
                    for java_file in files :
                        if ".java" == java_file[-5:] :
                            commands.append(os.path.join(path, java_file))

        error = CommandUtil.run(*commands)
        if error :
            raise Exception("APKBuilder javac_class(%s) ERROR:\n%s\n%s"  %(src_dir, " ".join(commands), error))
        return context


    def javac_R(self, context) :
        self.javac_class(context, context.apk_dir, "gen")
        return context


    def jar_class(self, context, project_path, class_path) :
        commands = [
            context.jar,
            "cvf",
            os.path.join(project_path, "bin", "classes.jar"),
            "-C", os.path.join(project_path, class_path), "."
        ]
        error = CommandUtil.run(*commands)
        if error :
            raise Exception("APKBuilder jar_class(%s) ERROR:\n%s\n%s"  %(project_path, " ".join(commands), error))
        return context


    def dex_jar(self, context, project_path) :
        commands = [
            context.dx,
            "--dex",
            "--output", os.path.join(project_path, "bin", "classes.dex"),
            os.path.join(project_path, "bin", "classes.jar")
        ]
        error = CommandUtil.run(*commands)
        if error :
            raise Exception("APKBuilder dex_jar(%s) ERROR:\n%s\n%s"  %(project_path, " ".join(commands), error))
        return context


    def rebuild_apk(self, context) :
        smali_dir = os.path.join(context.apk_dir, "smali")
        dex_dir = os.path.join(context.apk_dir, "bin", "classes.dex")
        commands = [
            context.java, "-jar",
            context.baksmali,
            "-o", smali_dir,
            dex_dir,
        ]
        error = CommandUtil.run(*commands)
        if error:
            raise Exception("APKBuilder rebuild_apk baksmali ERROR:\n%s\n%s"  %(" ".join(commands), error))
        unsigned_apk_path = os.path.join(os.path.split(os.path.realpath(context.apk_path))[0], "out.unsigned.apk")
        commands = [
            context.java, "-jar",
            "-Xmx512M", "-Djava.awt.headless=true",
            context.apktool, "-f",
            "--output", unsigned_apk_path,
            "b", context.apk_dir,
        ]
        error = CommandUtil.run(*commands)
        if error:
            raise Exception("APKBuilder rebuild_apk rebuild ERROR:\n%s\n%s"  %(" ".join(commands), error))
        context.unsigned_apk_path = unsigned_apk_path
        return context


    def sign_apk(self, context, keystore, storepass, alias, keypass = None) :
        if None == keypass :
            keypass = storepass
        signed_apk_path = os.path.join(os.path.split(context.unsigned_apk_path)[0], "out.signed.apk")
        commands = [
            context.jarsigner,
            "-digestalg", "SHA1",
            "-sigalg", "MD5withRSA",
            "-verbose",
            "-keystore", keystore,
            "-storepass", storepass,
            "-keypass", keypass,
            "-signedjar", signed_apk_path,
            context.unsigned_apk_path, alias,
        ]
        error = CommandUtil.run(*commands)
        if error:
            raise Exception("APKBuilder sign_apk ERROR:\n%s\n%s"  %(" ".join(commands), error))
        context.signed_apk_path = signed_apk_path
        return context


    def align_apk(self, context) :
        align_apk_path = os.path.join(os.path.split(context.signed_apk_path)[0], "out.signed.align.apk")
        commands = [
            context.zipalign,
            "-f",
            "4",
            context.signed_apk_path,
            align_apk_path,
        ]
        error = CommandUtil.run(*commands)
        if error :
            raise Exception("APKBuilder zipalign ERROR:\n%s\n%s"  %(" ".join(commands), error))
        context.align_apk_path = align_apk_path
        return context


    def clean(self, context) :
        if context.apk_dir and os.path.exists(context.apk_dir) :
            shutil.rmtree(context.apk_dir)
        output_apk = context.output_apk
        if context.align_apk_path and os.path.isfile(context.align_apk_path) :
            if context.unsigned_apk_path and os.path.isfile(context.unsigned_apk_path) :
                os.remove(context.unsigned_apk_path)
            if context.signed_apk_path and os.path.isfile(context.signed_apk_path) :
                os.remove(context.signed_apk_path)
            os.rename(context.align_apk_path, output_apk)
        elif context.signed_apk_path and os.path.isfile(context.signed_apk_path) :
            if context.unsigned_apk_path and os.path.isfile(context.unsigned_apk_path) :
                os.remove(context.unsigned_apk_path)
            os.rename(context.signed_apk_path, output_apk)
        elif context.unsigned_apk_path and os.path.isfile(context.unsigned_apk_path) :
            os.rename(context.unsigned_apk_path, output_apk)
        return context

