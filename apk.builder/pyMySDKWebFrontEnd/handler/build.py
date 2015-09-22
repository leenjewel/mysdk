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
import json
import threading,subprocess
import tornado.websocket
import tornado.web
from ahandler import AHandler
try :
    import pyMySDKAPKBuilder.workspace
    import pyMySDKAPKBuilder.command
    import pyMySDKAPKBuilder.lock
except ImportError :
    pwd = os.path.split(os.path.realpath(__file__))[0]
    sys.path.append(os.path.abspath(os.path.join(pwd, os.pardir, os.pardir)))
    import pyMySDKAPKBuilder.workspace
    import pyMySDKAPKBuilder.command
    import pyMySDKAPKBuilder.lock

class BuildHandler(AHandler) :

    layout = "default.html"


    def build_workspace_project(self, workspace_name, project_id) :
        self.workspace_project = None
        for workspace in self.application.settings["workspace"] :
            if workspace_name != os.path.split(workspace)[1] :
                continue
            self.workspace_project = pyMySDKAPKBuilder.workspace.WorkSpace(project_id, workspace)
        pwd = os.path.split(os.path.realpath(__file__))[0]
        mysdk_bin = os.path.join(pwd, os.pardir, os.pardir, "bin", "mysdk.py")
        work_dir = self.workspace_project.context["work_dir"]
        build_lock_file = os.path.join(work_dir, "build.lock")
        build_lock = pyMySDKAPKBuilder.lock.FileLock(build_lock_file)
        if not build_lock.lock(True) :
            return
        commands = [
            "python",
            mysdk_bin,
            "build",
            "--work-space", os.path.join(work_dir, os.pardir),
            "--name", self.workspace_project.name,
        ]
        print " ".join(commands)
        self.build_out = open(os.path.join(work_dir, "build.out"), "w")
        self.build_err = open(os.path.join(work_dir, "build.err"), "w")
        self.subprocess = subprocess.Popen(
            commands,
            stdout = self.build_out.fileno(),
            stderr = self.build_err.fileno(),
            bufsize = 1
        )
        while self.subprocess.poll() is None :
            pass
        self.build_out.close()
        self.build_err.close()
        build_lock.unlock()
        os.remove(build_lock_file)


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


    def post(self, workspace_name, project_id) :
        threading.Thread(target = self.build_workspace_project, args = (workspace_name, project_id)).start()
        self.write(json.dumps({"ret" : 0}))


class BuildProgressHandler(tornado.websocket.WebSocketHandler) :

    def progress_workspace_project(self, workspace_name, project_id, seek = 0, is_websocket = True) :
        out = ""
        workspace_project = None
        for workspace in self.application.settings["workspace"] :
            if workspace_name != os.path.split(workspace)[1] :
                continue
            workspace_project = pyMySDKAPKBuilder.workspace.WorkSpace(project_id, workspace)
        work_dir = workspace_project.context["work_dir"]
        build_lock_file = os.path.join(work_dir, "build.lock")
        build_out = open(os.path.join(work_dir, "build.out"), "r")
        build_out.seek(seek)
        try :
            if not os.path.isfile(build_lock_file) :
                out = build_out.read()
                seek = -1
                if is_websocket :
                    self.write_message(json.dumps({"seek" : seek, "data" : out}))
            else :
                while os.path.isfile(build_lock_file) :
                    out = build_out.readline()
                    if not out :
                        if not is_websocket :
                            out = ""
                            break;
                        continue
                    seek += len(out)
                    if is_websocket :
                        self.write_message(json.dumps({"seek" : seek, "data" : out}))
                    else :
                        break;
        except tornado.websocket.WebSocketClosedError :
            pass
        finally :
            build_out.close();
        try :
            build_err = open(os.path.join(work_dir, "build.err"), "r")
            error = build_err.read()
            if error :
                if is_websocket :
                    self.write_message(json.dumps({"seek" : seek, "data" : error}))
                else :
                    out += error
        except tornado.websocket.WebSocketClosedError :
            pass
        finally :
            build_err.close()
        if is_websocket :
            self.write_message(json.dumps({"seek" : -1, "data" : ""}))
        else :
            self.write(json.dumps({"seek" : seek, "data" : out.decode('string_escape')}))


    def open(self, workspace_name, project_id) :
        pass


    def on_message(self, message) :
        data = json.loads(message)
        workspace_name = data["workspace_name"]
        project_id = data["project_id"]
        seek = data.get("seek", 0)
        threading.Thread(target = self.progress_workspace_project, args = (workspace_name, project_id, seek)).start()


    def on_close(self) :
        pass


    def post(self, workspace_name, project_id) :
        seek = self.get_body_argument("seek", 0)
        self.progress_workspace_project(workspace_name, project_id, int(seek), False)

