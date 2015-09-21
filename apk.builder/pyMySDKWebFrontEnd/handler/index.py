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

import os,sys,shutil
from ahandler import AHandler
try :
    import pyMySDKAPKBuilder.workspace
except ImportError :
    pwd = os.path.split(os.path.realpath(__file__))[0]
    sys.path.append(os.path.abspath(os.path.join(pwd, os.pardir, os.pardir)))
    import pyMySDKAPKBuilder.workspace

class IndexHandler(AHandler) :

    layout = "default.html"

    def get(self) :
        workspace_entry_list = []
        settings = self.application.settings
        if settings.has_key("workspace") :
            for workspace_path in settings["workspace"] :
                if not os.path.exists(workspace_path) :
                    continue
                workspace_entry = {
                    "name" : os.path.split(workspace_path)[1],
                    "workspace" : pyMySDKAPKBuilder.workspace.WorkSpace("./", workspace_path)
                }
                for path, dirs, files in os.walk(workspace_path) :
                    workspace_entry["count"] = len(dirs)
                    break
                workspace_entry_list.append(workspace_entry)
        self.render("index.html",
            workspace_entry_list = workspace_entry_list
        )


    def post(self) :
        workspace_path = self.get_body_argument("delete_workspace_path", None)
        if workspace_path :
            return self.delete()
        workspace_id = self.get_body_argument("new_workspace_id")
        workspace_name = self.get_body_argument("new_workspace_name")
        workspace_desc = self.get_body_argument("new_workspace_desc")
        cwd = os.getcwd()
        workspace_root = os.path.join(cwd, workspace_id)
        is_create_workspace = False
        if not os.path.exists(workspace_root) :
            is_create_workspace = True
            os.mkdir(workspace_root)
        workspace_project = pyMySDKAPKBuilder.workspace.WorkSpace("./", workspace_root)
        workspace_project.init_project_info(workspace_name, workspace_desc)
        if is_create_workspace :
            workspace_project.context["sdk_search_path"] = self.application.settings.get("sdk_search_paths", [])
        workspace_project.save()
        self.application.add_workspace(workspace_root)
        return self.get()


    def delete(self) :
        workspace_path = os.path.abspath(self.get_body_argument("delete_workspace_path"))
        if os.path.exists(workspace_path) :
            shutil.rmtree(workspace_path)
        self.application.del_workspace(workspace_path)
        return self.get()

