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

import os,sys
import threading,subprocess
import tornado.websocket
import tornado.web
from ahandler import AHandler
try :
    import pyMySDKAPKBuilder.workspace
    import pyMySDKAPKBuilder.command
except ImportError :
    pwd = os.path.split(os.path.realpath(__file__))[0]
    sys.path.append(os.path.abspath(os.path.join(pwd, os.pardir, os.pardir)))
    import pyMySDKAPKBuilder.workspace
    import pyMySDKAPKBuilder.command

class BuildHandler(AHandler) :

    layout = "default.html"

    def get(self, workspace_name, project_id) :
        workspace_project = self.get_workspace(workspace_name, project_id)
        workspace_project.init_sdk()
        self.render("project.html", **{
            "is_create_project" : False,
            "is_build_project" : True,
            "workspace_name" : workspace_name,
            "project_name" : project_id,
            "workspace_project" : workspace_project,
            "workspace_sdks" : {sdk_config.get_config("id") : sdk_config for sdk_config in workspace_project.context["sdk_list"]},
        })


class BuildProgressHandler(tornado.websocket.WebSocketHandler) :

    def build_workspace_project(self, workspace_name, project_id) :
        self.workspace_project = None
        for workspace in self.application.settings["workspace"] :
            if workspace_name != os.path.split(workspace)[1] :
                continue
            self.workspace_project = pyMySDKAPKBuilder.workspace.WorkSpace(project_id, workspace)
        pwd = os.path.split(os.path.realpath(__file__))[0]
        mysdk_bin = os.path.join(pwd, os.pardir, os.pardir, "bin", "mysdk.py")
        work_dir = self.workspace_project.context["work_dir"]
        commands = [
            "python",
            mysdk_bin,
            "--work-space", work_dir,
            "--name", self.workspace_project.name,
        ]
        self.write_message(" ".join(commands) + "\n")
        self.subprocess = subprocess.Popen(
            commands,
            stdout = subprocess.PIPE,
            stderr = subprocess.PIPE,
            bufsize = 1
        )
        self.write_message("Building...\n")
        while True :
            out = self.subprocess.stdout.readline()
            if out :
                self.write_message(out)
            else :
                break;
        err = self.subprocess.stderr.read().strip()
        if err and len(err) > 0 :
            self.write_message(err)


    def open(self, workspace_name, project_id) :
        self.write_message("Start build...\n")
        threading.Thread(target = self.build_workspace_project, args = (workspace_name, project_id)).start()
        self.write_message("Please wait...\n")


    def on_message(self, message) :
        pass


    def on_close(self) :
        pass

