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

import os, sys
import tornado.web
try :
    import pyMySDKAPKBuilder.workspace
except ImportError :
    pwd = os.path.split(os.path.realpath(__file__))[0]
    sys.path.append(os.path.abspath(os.path.join(pwd, os.pardir, os.pardir)))
    import pyMySDKAPKBuilder.workspace

class AHandler(tornado.web.RequestHandler) :

    layout = None


    def initialize(self, app) :
        self.app = app


    def get_workspace(self, workspace_name, project_name = "") :
        for workspace in self.app.settings["workspace"] :
            if workspace_name != os.path.split(workspace)[1] :
                continue
            return pyMySDKAPKBuilder.workspace.WorkSpace(project_name, workspace)
        return None


    def render(self, template_name, **kwargs) :
        if None == self.layout :
            return tornado.web.RequestHandler.render(self, template_name, **kwargs)
        else :
            kwargs["content"] = self.render_string(template_name, **kwargs)
            return tornado.web.RequestHandler.render(self, "layouts/" + self.layout, **kwargs)



