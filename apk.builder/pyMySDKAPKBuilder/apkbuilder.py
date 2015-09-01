#-*- coding:utf-8 -*-
import os
from command import CommandUtil
from xmlutil import XMLUtil
from androidmanifest import AndroidManifest

class APKBuilder :

    def __init__(self, apk_path, sdk) :
        self.pwd = os.path.split(os.path.realpath(__file__))[0]
        self.apk_path = apk_path
        self.sdk = sdk
        self.check()


    def build(self) :
        self.decode_apk()
        self.parse_manifest()
        self.finish_manifest()
        self.write_manifest()


    def check(self) :
        pass


    def decode_apk(self) :
        apk_dir = os.path.split(os.path.realpath(self.apk_path))[0]
        out_dir = os.path.join(apk_dir, "out")
        if not os.path.exists(out_dir) :
            os.makedirs(out_dir)
        apktool_jar = os.path.join(self.pwd, "jar", "apktool.jar")
        error = CommandUtil.run("java", "-jar", "-Xmx512M", "-Djava.awt.headless=true", apktool_jar, "-f", "--output", out_dir, "d", self.apk_path)
        if error != None :
            exception = "APKBuilder decode apk %s ERROR : %s"  %(self.apk_path, error)
            raise Exception(exception)
        self.apk_dir = out_dir
        apk_manifest_xml = os.path.join(self.apk_dir, "AndroidManifest.xml")
        self.apk_manifest = AndroidManifest(apk_manifest_xml)


    def parse_manifest(self) :
        apk_application_element = self.apk_manifest.get_application_element()
        self.apk_activity_main = XMLUtil.find_element(apk_application_element, "activity/intent-filter/action[@android:name='android.intent.action.MAIN']/../..")
        self.apk_activity_main_filter = XMLUtil.find_element(self.apk_activity_main, "intent-filter/action[@android:name='android.intent.action.MAIN']/..")
        self.apk_activity_main.remove(self.apk_activity_main_filter)


    def finish_manifest(self) :
        apk_application_element = self.apk_manifest.get_application_element()
        apk_launch_activity = XMLUtil.find_element(apk_application_element, "activity/intent-filter/action[@android:name='android.intent.action.MAIN']/../..")
        if None == apk_launch_activity :
            self.apk_activity_main.insert(0, self.apk_activity_main_filter)


    def write_manifest(self) :
        save_path = os.path.join(self.apk_dir, "AndroidManifest.xml")
        self.apk_manifest.save(save_path)





if __name__ == "__main__" :
    import sys
    apk_builder = APKBuilder(sys.argv[1], None)
    apk_builder.build()

