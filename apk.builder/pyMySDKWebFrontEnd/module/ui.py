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

import tornado.web

class AUIModule(tornado.web.UIModule) :

    def render(self, entry, **kwargs) :
        kwargs["entry"] = entry
        return self.render_string("ui/" + self.__class__.__name__.lower() + ".html", **kwargs)

class WorkSpaceEntry(AUIModule) :
    pass


class ProjectEntry(AUIModule) :
    pass


class SDKConfigEntry(AUIModule) :

    def render(self, entry, **kwargs) :
        if not kwargs.has_key("show_add") :
            kwargs["show_add"] = False
        if not kwargs.has_key("has_add") :
            kwargs["has_add"] = False
        if not kwargs.has_key("is_build") :
            kwargs["is_build"] = False
        if not kwargs.has_key("meta_data") :
            kwargs["meta_data"] = {}
        return AUIModule.render(self, entry, **kwargs)

