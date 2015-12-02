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
    from pyMySDKAPKBuilder.importlib import import_module
    from pyMySDKAPKBuilder.apkbuilder import APKBuilder
    from pyMySDKWebFrontEnd.application import Application
    from pyMySDKWebFrontEnd.application import ApplicationDaemon
except ImportError :
    pwd = os.path.split(os.path.realpath(__file__))[0]
    sys.path.append(os.path.abspath(os.path.join(pwd, os.pardir)))
    from pyMySDKAPKBuilder.workspace import WorkSpace
    from pyMySDKAPKBuilder.importlib import import_module
    from pyMySDKAPKBuilder.apkbuilder import APKBuilder
    from pyMySDKWebFrontEnd.application import Application
    from pyMySDKWebFrontEnd.application import ApplicationDaemon


class MySDKCommand(argparse.ArgumentParser) :

    def __init__(self) :
        usage = '''
        %(prog)s  {build, create-server, start-server, stop-server, restart-server}  [options]
        \t
        \tbuild\tBuild project
        \tcreate-server\tCreate MySDK Web frontend server
        \tstart-server\tStart MySDK Web frontend server
        \tstop-server\tStop MySDK Web frontend server
        \trestart-server\tRestart MySDK Web frontend server
        '''
        argparse.ArgumentParser.__init__(self, usage = usage)

        command_help = ''
        self.add_argument("command", help = command_help,
                choices = ("build", "create-server", "start-server", "stop-server", "restart-server"))

        sdk_list_help = 'SDK ID list which you want to build'
        self.add_argument("--sdk", help = sdk_list_help,
                dest = "sdk_list", metavar = "SDK-ID", nargs = "*")

        sdk_path_help = 'SDK search paths'
        self.add_argument("--sdk-path", help = sdk_path_help,
                dest = "sdk_path", metavar = "path", nargs = "*")

        work_space_help = 'Work space path'
        self.add_argument("--work-space", help = work_space_help,
                dest = "work_space", metavar = "", default = os.getcwd())

        apk_path_help = 'Android APK file path'
        self.add_argument("--apk-path", help = apk_path_help,
                dest = "apk_path", metavar = "")

        output_help = 'Output Android APK file path'
        self.add_argument("--output", help = output_help,
                metavar = "")

        android_platform_help = 'Android platform'
        self.add_argument("--platform", help = android_platform_help,
                metavar = "")

        keystore_help = 'Android Keystore file path'
        self.add_argument("--keystore", help = keystore_help,
                metavar = "")

        storepass_help = 'Android Keystore store password'
        self.add_argument("--storepass", help = storepass_help,
                metavar = "")

        storealias_help = 'Android Keystore alias'
        self.add_argument("--alias", help = storealias_help,
                metavar = "")

        keypass_help = "Android Keystore private password"
        self.add_argument("--keypass", help = keypass_help,
                metavar = "")

        name_help = 'Project name'
        self.add_argument("--name", help = name_help,
                metavar = "")

        meta_data_help = 'Meta data'
        self.add_argument("--meta-data", help = meta_data_help,
                nargs = "*", dest = "meta_data", metavar = "key=value")

        package_name_help = 'Android application package name'
        self.add_argument("--package", help = package_name_help,
                metavar = "")

        server_config_help = 'Web frontend server settings file path'
        self.add_argument("--server-config", help = server_config_help,
                dest = "server_config", metavar = "")

        server_port_help = 'Web frontend server listen port'
        self.add_argument("--with-port", help = server_port_help,
                dest = "port", default=None, metavar = "")

        daemon_help = 'Start web frontend server with daemon'
        self.add_argument("--with-daemon", help = daemon_help,
                dest = "daemon", action = "store_true", default = False)

        server_path_help = 'Web fronted server path'
        self.add_argument("--server-path", help = server_path_help,
                dest = "server_path", metavar = "")


    def parse_args(self) :
        self.args = argparse.ArgumentParser.parse_args(self)
        command = self.args.command
        command = command.replace("-", "_")
        command_method = getattr(self, command)
        if command_method :
            command_method(self.args)


    def create_server(self, args) :
        server_path = args.server_path
        if None == server_path :
            server_path = os.getcwd()
        if not os.path.exists(server_path) :
            os.makedirs(server_path)
        print "Create MySDK server on %s"  %(server_path)
        init_py = open(os.path.join(server_path, "__init__.py"), "w")
        init_py.write("")
        init_py.close()
        settings = '''
import os
pwd = os.path.split(os.path.realpath(__file__))[0]
settings = {
    "debug" : True,
    "sdk_search_paths" : [{{sdk_search_paths}},],
}
'''
        sdk_path = args.sdk_path
        if isinstance(sdk_path, list) or isinstance(sdk_path, tuple) :
            sdk_search_paths = []
            for sdk_dir in sdk_path :
                if os.path.exists(sdk_dir) :
                    sdk_search_paths.append(os.path.abspath(sdk_dir))
            settings = settings.replace("{{sdk_search_paths}}", '"%s"'  %('","'.join(sdk_search_paths)))
        else :
            settings = settings.replace("{{sdk_search_paths}},", "")

        settings_py_path = os.path.join(server_path, "settings.py")
        settings_py = open(settings_py_path, "w")
        settings_py.write(settings)
        settings_py.close()
        print "Now you can run\n\n\tmysdk.py start-server --server-config %s  --with-port 8080\n\nto start server."  %(os.path.abspath(settings_py_path))


    def server_settings(self, args) :
        settings = {}
        if not args.server_config :
            return settings
        if os.path.isfile(args.server_config) :
            cwd,config_file = os.path.split(os.path.abspath(args.server_config))
            os.chdir(cwd)
            sys.path.append(cwd)
            sys.path.append(os.path.join(cwd, os.pardir))
            if '.json' == args.server_config[-5:] :
                import json
                json_file = open(args.server_config, 'r')
                settings = json.load(json_file)
                json_file.close()
            if '.py' == args.server_config[-3:] :
                config_module = import_module("settings")
                settings = config_module.settings
        else :
            cwd = os.path.abspath(args.server_config)
            sys.path.append(cwd)
            sys.path.append(os.path.join(cwd, os.pardir))
        return settings


    def start_server(self, args) :
        print "Start MySDK Server..."
        settings = self.server_settings(args)
        if args.daemon :
            if args.port :
                settings["port"] = args.port
            ApplicationDaemon(settings).run()
        else :
            port = args.port
            if not port :
                port = 8080
            try :
                Application(settings).run(port)
            except KeyboardInterrupt :
                sys.exit(0)
            except Exception, e :
                sys.stderr.write("Error : %s \n" %(str(e)))
                os._exit(1)


    def stop_server(self, args) :
        print "Stop MySDK Server..."
        settings = self.server_settings(args)
        ApplicationDaemon(settings).stop()


    def restart_server(self, args) :
        print "Restart MySDK Server..."
        settings = self.server_settings(args)
        ApplicationDaemon(settings).restart()


    def build(self, args) :
        if not os.path.exists(args.work_space) :
            os.makedirs(args.work_space)

        work_space = os.path.abspath(args.work_space)
        init_py = os.path.join(work_space, "__init__.py")
        with open(init_py, "a") :
            os.utime(init_py, None)
        sys.path.append(work_space)

        name = args.name
        if None == args.name or len(args.name) == 0 :
            for path, dirs, files in os.walk(work_space) :
                if os.path.samefile(path, work_space) :
                    if len(dirs) == 0 :
                        raise Exception("need project name")
                    name = dirs[0]
                    break
        work_space = WorkSpace(name, work_space)

        if args.apk_path :
            work_space.init_apk(args.apk_path)

        if args.output :
            work_space.init_output_apk(args.output)

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
            work_space.init_metadata("PACKAGE", args.package)

        work_space.init_keystore(args.keystore, args.storepass, args.alias, args.keypass)

        apk_builder = APKBuilder(work_space)
        ret = apk_builder.build()

        if ret.output_apk is not None and os.path.isfile(ret.output_apk) :
            print "Output : %s"  %(os.path.abspath(ret.output_apk))
        else :
            print "Build Failed"

        work_space.save()



if __name__ == '__main__' :

    MySDKCommand().parse_args()

