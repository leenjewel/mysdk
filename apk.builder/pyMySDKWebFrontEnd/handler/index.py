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
from ahandler import AHandler

class IndexHandler(AHandler) :

    layout = "default.html"

    def get(self) :
        workspace_entry_list = []
        settings = self.application.settings
        if settings.has_key("workspace") :
            for workspace in settings["workspace"] :
                if not os.path.exists(workspace) :
                    continue
                workspace_entry = {
                    "name" : os.path.split(workspace)[1],
                }
                for path, dirs, files in os.walk(workspace) :
                    workspace_entry["count"] = len(dirs)
                    break
                workspace_entry_list.append(workspace_entry)
        self.render("index.html", workspace_entry_list = workspace_entry_list)

