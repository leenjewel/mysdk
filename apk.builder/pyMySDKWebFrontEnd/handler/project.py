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

class ProjectHandler(AHandler) :

    layout = "default.html"

    def update_project(self, workspace_project) :
        new_project_platform = self.get_body_argument("new_project_platform")
        new_project_storepass = self.get_body_argument("new_project_storepass")
        new_project_alias = self.get_body_argument("new_project_alias")
        new_project_keypass = self.get_body_argument("new_project_keypass")

        project_name = self.get_body_argument("project_name")
        project_desc = self.get_body_argument("project_desc")
        workspace_project.init_project_info(project_name, project_desc)

        project_output_apk = self.get_body_argument("project_output_apk")
        workspace_project.init_output_apk(project_output_apk)

        workspace_project.init_android_platform(new_project_platform)

        apk_file_list = self.request.files.get("new_project_apk")
        if apk_file_list :
            for apk_file_dict in apk_file_list :
                apk_file_path = os.path.join(workspace_project.context["work_dir"], workspace_project.name+".apk")
                fp = open(apk_file_path, "wb")
                fp.write(apk_file_dict["body"])
                fp.close()
                workspace_project.init_apk(apk_file_path)
                break

        keystore_file_list = self.request.files.get("new_project_keystore")
        if keystore_file_list :
            for keystore_file_dict in keystore_file_list :
                keystore_file_path = os.path.join(workspace_project.context["work_dir"], workspace_project.name+".keystore")
                fp = open(keystore_file_path, "wb")
                fp.write(keystore_file_dict["body"])
                fp.close()
                workspace_project.init_keystore(keystore_file_path, new_project_storepass, new_project_alias, new_project_keypass)
                break

        settings = self.application.settings
        sdk_search_paths = settings.get("sdk_search_paths")
        sdk_search_paths, workspace_sdks = workspace_project.all_sdk(sdk_search_paths)
        sdk_id_list = []
        sdk_index = 0
        sdk_id = self.get_body_argument("sdk_list["+str(sdk_index)+"]", None)
        while sdk_id :
            sdk_id_list.append(sdk_id)
            sdk_index += 1
            sdk_id = self.get_body_argument("sdk_list["+str(sdk_index)+"]", None)
        workspace_project.context["sdk_list"] = []
        workspace_project.context["sdk_id_list"] = []
        workspace_project.init_sdk(sdk_id_list, sdk_search_paths)

        metadata_dict = {}
        for sdk_id in sdk_id_list :
            sdk_config = workspace_sdks[sdk_id]
            sdk_metadata = sdk_config.get_config("metadata")
            for meta_key, meta_conf in sdk_metadata.items() :
                metadata_key = "sdk_config[%s][metadata][%s]"  %(sdk_id, meta_key)
                metadata_val = self.get_body_argument(metadata_key, None)
                if metadata_val :
                    metadata_dict[meta_key] = metadata_val
        workspace_project.context["meta_data"] = {}
        workspace_project.init_metadata(metadata_dict)

        project_package_name = self.get_body_argument("project_package_name")
        if project_package_name :
            workspace_project.init_metadata("PACKAGE", project_package_name)

        workspace_project.save()
        return workspace_project

    def get(self, workspace_name, project_name) :
        workspace_project = self.get_workspace(workspace_name, project_name)
        workspace_project.init_sdk()
        settings = self.application.settings
        sdk_search_paths = settings.get("sdk_search_paths")

        sdk_search_paths, workspace_sdks = workspace_project.all_sdk(sdk_search_paths)
        self.render("project.html", **{
            "is_create_project" : False,
            "is_build_project" : False,
            "workspace_name" : workspace_name,
            "project_name" : project_name,
            "workspace_project" : workspace_project,
            "workspace_sdks" : workspace_sdks,
        })


    def post(self, workspace_name, project_name) :
        workspace_project = self.get_workspace(workspace_name, project_name)
        workspace_project = self.update_project(workspace_project)
        return self.redirect("/workspace/%s"  %(workspace_name))



class NewHandler(ProjectHandler) :

    layout = "default.html"

    def get(self, workspace_name) :
        workspace_project = self.get_workspace(workspace_name)
        settings = self.application.settings
        sdk_search_paths = settings.get("sdk_search_paths")
        sdk_search_paths, workspace_sdks = workspace_project.all_sdk(sdk_search_paths)
        self.render("project.html", **{
            "is_create_project" : True,
            "is_build_project" : False,
            "workspace_name" : workspace_name,
            "project_name" : "",
            "workspace_project" : workspace_project,
            "workspace_sdks" : workspace_sdks,
        })


    def post(self, workspace_name) :
        new_project_id = self.get_body_argument("new_project_id")

        workspace_project = None
        settings = self.application.settings
        sdk_search_paths = settings.get("sdk_search_paths")
        for workspace in self.settings["workspace"] :
            if workspace_name != os.path.split(workspace)[1] :
                continue
            if os.path.exists(os.path.join(workspace, new_project_id)) :
                return self.redirect("/project/%s/%s"  %(workspace_name, new_project_id))
            workspace_project = pyMySDKAPKBuilder.workspace.WorkSpace(new_project_id, workspace)
            break
        workspace_project = self.update_project(workspace_project)
        return self.redirect("/workspace/%s"  %(workspace_name))


class DelHandler(AHandler) :

    def get(self, workspace_name, project_id) :
        return self.post(workspace_name, project_id)


    def post(self, workspace_name, project_id) :
        workspace_project = self.get_workspace(workspace_name, project_id)
        if workspace_project and os.path.exists(workspace_project.context["work_dir"]):
            if os.path.samefile(workspace_project.context["work_dir"], workspace_project.root) :
                self.application.del_workspace(workspace_project.root)
            shutil.rmtree(workspace_project.context["work_dir"])
        return self.redirect("/workspace/%s"  %(workspace_name))


