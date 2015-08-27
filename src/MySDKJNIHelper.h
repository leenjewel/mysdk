#ifndef __MYSDK_JNIHELPER_H__
#define __MYSDK_JNIHELPER_H__

#include <jni.h>
#include <string>
#include "MySDKLog.h"

namespace mysdk
{
    typedef struct _JniMethodInfo
    {
        JNIEnv*    env;
        jclass     classID;
        jmethodID  methodID;
    } JNIMethodInfo;

    class MySDKJNIHelper
    {
        public:
            static void setJavaVM(JavaVM* jvm);
            static JavaVM* getJavaVM();
            static JNIEnv* getJNIEnv();

            static std::string jstring2string(jstring jstr);

            static bool getStaticMethodInfo(
                    JNIMethodInfo &jniMethodInfo,
                    std::string className,
                    std::string methodName,
                    std::string paramCode);

        private:
            static jclass getClassID(std::string className);
            static JNIEnv* cacheJNIEnv(JavaVM* jvm);

    };
};

#endif
