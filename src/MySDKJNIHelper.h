#ifndef __MYSDK_JNIHELPER_H__
#define __MYSDK_JNIHELPER_H__

#include <jni.h>
#include <string>
#include <android/log.h>

#define LOG_TAG    "MySDK"
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#if MYSDK_DEBUG
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define LOGD(...)  do{}while(0);
#endif

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
