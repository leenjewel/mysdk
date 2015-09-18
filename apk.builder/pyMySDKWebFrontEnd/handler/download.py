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
import tornado.web
try :
    import pyMySDKAPKBuilder.workspace
except ImportError :
    pwd = os.path.split(os.path.realpath(__file__))[0]
    sys.path.append(os.path.abspath(os.path.join(pwd, os.pardir, os.pardir)))
    import pyMySDKAPKBuilder.workspace

class DownloadHandler(tornado.web.StaticFileHandler) :

    def initialize(self) :
        pass

    def head(self, workspace_name, project_id) :
        print "download head"
        return self.get(workspace_name, project_id, False)


    def get(self, workspace_name, project_id, include_body = True) :
        print "download get"
        workspace_project = None
        for workspace in self.application.settings["workspace"] :
            if workspace_name != os.path.split(workspace)[1] :
                continue
            workspace_project = pyMySDKAPKBuilder.workspace.WorkSpace(project_id, workspace)
        self.root, self.default_filename = os.path.split(workspace_project.context["output_apk"])
        return tornado.web.StaticFileHandler.get(self, self.default_filename, include_body)


