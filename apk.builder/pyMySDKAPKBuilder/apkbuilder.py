#-*- coding:utf-8 -*-
import os
from command import CommandUtil

class APKBuilder :

    def __init__(self, apk_path, sdk) :
        self.pwd = os.path.split(os.path.realpath(__file__))[0]
        self.apk_path = apk_path
        self.sdk = sdk
        self.check()


    def build(self) :
        self.decode_apk(self.apk_path)


    def check(self) :
        pass


    def decode_apk(self, apk_path) :
        apk_dir = os.path.split(os.path.realpath(apk_path))[0]
        out_dir = os.path.join(apk_dir, "out")
        if not os.path.exists(out_dir) :
            os.makedirs(out_dir)
        apktool_jar = os.path.join(self.pwd, "jar", "apktool.jar")
        error = CommandUtil.run("java", "-jar", "-Xmx512M", "-Djava.awt.headless=true", apktool_jar, "-f", "--output", out_dir, "d", apk_path)
        if error != None :
            exception = "APKBuilder decode apk %s ERROR : %s"  %(apk_path, error)
            raise Exception(exception)





if __name__ == "__main__" :
    import sys
    apk_builder = APKBuilder(sys.argv[1], None)
    apk_builder.build()

