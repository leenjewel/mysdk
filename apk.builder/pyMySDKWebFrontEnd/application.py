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

import sys,os
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



if __name__ == "__main__" :
    import json, argparse
    parser = argparse.ArgumentParser()

    parser.add_argument('config', help = "Config file path")

    parser.add_argument('--port', default=8080, help = "Listen port")

    args = parser.parse_args()

    if not os.path.isfile(args.config) :
        raise Exception("%s not found."  %(args.config))
    fp = open(args.config, "r")
    settings = json.load(fp)
    fp.close()
    os.chdir(os.path.split(args.config)[0])

    Application(settings).run(args.port)

