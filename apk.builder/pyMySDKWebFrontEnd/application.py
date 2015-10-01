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

import sys,os,time,atexit
from signal import SIGTERM
import tornado.ioloop
import tornado.web
import tornado.httpserver
from handler import index
from handler import workspace
from handler import project
from handler import build
from handler import download
import module.ui

handlers = [
    (r"/index", index.IndexHandler),
    (r"/workspace/([^/]*)/?", workspace.WorkspaceHandler),
    (r"/project/([^/]*)/([^/]*)/?", project.ProjectHandler),
    (r"/new/([^/]*)/?", project.NewHandler),
    (r"/del/([^/]*)/([^/]*)/?", project.DelHandler),
    (r"/build/([^/]*)/([^/]*)/?", build.BuildHandler),
    (r"/build/progress/([^/]*)/([^/]*)/?", build.BuildProgressHandler),
    (r"/download/([^/]*)/([^/]*)/?", download.DownloadHandler),
]

pwd = os.path.split(os.path.realpath(__file__))[0]
default_settings = {
    "debug" : False,
}
app_settings = {
    "template_path" : os.path.join(pwd, "templates"),
    "static_path" : os.path.join(pwd, "resources"),
    "ui_modules" : module.ui,
}

class Application(tornado.web.Application) :

    def __init__(self, user_settings) :
        self.settings = {}
        self.settings.update(default_settings)
        self.settings.update(user_settings)
        self.settings.update(app_settings)
        self.init_workspace()
        tornado.web.Application.__init__(self, handlers, **self.settings)


    def run(self, port = 8080) :
        http_server = tornado.httpserver.HTTPServer(self)
        http_server.listen(port)
        tornado.ioloop.IOLoop.current().start()


    def init_workspace(self) :
        if not self.settings.has_key("workspace") or not isinstance(self.settings["workspace"], list) :
            self.settings["workspace"] = []
        else :
            self.settings["workspace"] = [workspace_root for workspace_root in self.settings["workspace"] if os.path.exists(workspace_root)]
        for path, dirs, files in os.walk(os.getcwd()) :
            for workspace_dir in dirs :
                self.add_workspace(os.path.join(path, workspace_dir))


    def has_workspace(self, workspace_path) :
        for workspace_root in self.settings["workspace"] :
            if os.path.samefile(workspace_root, workspace_path) :
                return True
        return False


    def add_workspace(self, workspace_path) :
        if not self.has_workspace(workspace_path) :
            self.settings["workspace"].append(workspace_path)


    def del_workspace(self, workspace_path) :
        self.settings["workspace"] = [workspace_root for workspace_root in self.settings["workspace"] if os.path.exists(workspace_root)]



class ApplicationDaemon(object) :

    def __init__(self, user_settings) :
        self.settings = user_settings


    def pidfile(self) :
        pid_file = self.settings.get("pidfile")
        if None is pid_file or len(pid_file) == 0 :
            pid_file = os.path.join(os.getcwd(), "mysdk-server.pid")
        return pid_file


    def daemonize(self) :
        try :
            if os.fork() > 0 :
                sys.exit(0)
        except OSError, e :
            sys.stderr.write("fork #1 failed : %d %s\n"  %(e.errno, e.strerror))
            sys.exit(1)

        os.setsid()
        os.umask(0)

        try :
            if os.fork() > 0 :
                sys.exit(0)
        except OSError, e:
            sys.stderr.write("fork #2 failed : %d %s\n"  %(e.errno, e.strerror))
            sys.exit(1)

        sys.stdout.flush()
        sys.stderr.flush()

        stdout_file = self.settings.get("stdout")
        if None is stdout_file or len(stdout_file) == 0 :
            stdout_file = os.path.join(os.getcwd(), "std.out")
        stdout = file(stdout_file, "a+")
        os.dup2(stdout.fileno(), sys.stdout.fileno())

        stderr_file = self.settings.get("stderr")
        if None is stderr_file or len(stderr_file) == 0 :
            stderr_file = os.path.join(os.getcwd(), "std.err")
        stderr = file(stderr_file, "a+", 0)
        os.dup2(stderr.fileno(), sys.stderr.fileno())

        atexit.register(self.delpid)
        pid = str(os.getpid())
        pid_file = self.pidfile()
        pid_fp = open(pid_file, 'w+')
        pid_fp.write("%s\n"  %(pid))
        pid_fp.close()


    def delpid(self) :
        os.remove(self.pidfile())


    def getpid(self) :
        try :
            pid_fp = file(self.pidfile(), "r")
            pid = int(pid_fp.read().strip())
            pid_fp.close()
        except IOError :
            pid = None
        return pid


    def start(self) :
        pid = self.getpid()
        if pid :
            sys.stderr.write("pid file %s already exist. Daemon already running?\n"  %(self.pidfile()))
            sys.exit(1)

        self.daemonize()

        Application(self.settings).run(self.settings.get("port", 8080))


    def stop(self) :
        pid = self.getpid()
        if not pid :
            sys.stderr.write("pid file %s not exists. Daemon not running?\n"  %(self.pidfile()))
            return

        try :
            while True :
                os.kill(pid, SIGTERM)
                time.sleep(0.1)
        except OSError, e :
            error = str(e)
            if error.find("No such process") > 0 :
                if os.path.exists(self.pidfile()) :
                    os.remove(self.pidfile())
            else :
                sys.stderr.write(error)
                sys.exit(1)


    def restart(self) :
        self.stop()
        time.sleep(0.5)
        self.start()


    def run(self, port = None) :
        if port :
            self.settings["port"] = port
        self.start()



if __name__ == "__main__" :
    import json, argparse
    parser = argparse.ArgumentParser()

    parser.add_argument('config', help = "Config file path")

    parser.add_argument('--port', default=8080, help = "Listen port")

    parser.add_argument('--daemon', action = 'store_true', default = False, help = "Start server with daemon")

    args = parser.parse_args()

    if not os.path.isfile(args.config) :
        raise Exception("%s not found."  %(args.config))
    fp = open(args.config, "r")
    settings = json.load(fp)
    fp.close()
    os.chdir(os.path.split(args.config)[0])

    if args.daemon :
        ApplicationDaemon(settings).run(args.port)
    else :
        Application(settings).run(args.port)

