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
import module.ui

handlers = [
    (r"/index", index.IndexHandler),
    (r"/workspace/([^/]*)", workspace.WorkspaceHandler),
    (r"/project/([^/]*)/([^/]*)", project.ProjectHandler),
    (r"/new/([^/]*)", project.NewHandler),
    (r"/build/([^/]*)/([^/]*)", build.BuildHandler),
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
        init_dict = {
            "app" : self,
        }
        handler_list = []
        for handler in handlers :
            handler = list(handler)
            if len(handler) > 2 :
                handler[2].update(init_dict)
            else :
                handler.append(init_dict)
            handler_list.append(handler)
        tornado.web.Application.__init__(self, handler_list, **self.settings)


    def run(self, port = 8080) :
        http_server = tornado.httpserver.HTTPServer(self)
        http_server.listen(port)
        tornado.ioloop.IOLoop.current().start()


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

