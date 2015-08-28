#include "MySDKJNIHelper.h"
#include <pthread.h>

using namespace mysdk;

static pthread_key_t _g_key;
static JavaVM* _jvm = nullptr;

void MySDKJNIHelper::setJavaVM(JavaVM* jvm)
{
#if MYSDK_DEBUG
    pthread_t thisthread = pthread_self();
    LOGD("setJavaVM(%p) pthread_self() = %ld", jvm, thisthread);
#endif
    _jvm = jvm;
    pthread_key_create(&_g_key, nullptr);
}

JavaVM* MySDKJNIHelper::getJavaVM()
{
#if MYSDK_DEBUG
    pthread_t thisthread = pthread_self();
    LOGD("getJavaVM pthread_self() = %ld", thisthread);
#endif
    return _jvm;
}

JNIEnv* MySDKJNIHelper::cacheJNIEnv(JavaVM* jvm)
{
    JNIEnv* env = nullptr;
    jint ret = jvm->GetEnv((void**)&env, JNI_VERSION_1_4);
    switch (ret) {
    case JNI_OK:
        pthread_setspecific(_g_key, env);
        return env;
    case JNI_EDETACHED:
        if (jvm->AttachCurrentThread(&env, nullptr) < 0) {
            return nullptr;
        } else {
            pthread_setspecific(_g_key, env);
            return env;
        }
    }
    return nullptr;
}

JNIEnv* MySDKJNIHelper::getJNIEnv()
{
    JNIEnv* env = (JNIEnv*)pthread_getspecific(_g_key);
    if (nullptr == env) {
        env = MySDKJNIHelper::cacheJNIEnv(_jvm);
    }
    return env;
}

std::string MySDKJNIHelper::jstring2string(jstring jstr)
{
    if (nullptr == jstr) {
        return "";
    }
    JNIEnv* env = MySDKJNIHelper::getJNIEnv();
    if (!env) {
        return nullptr;
    }
    const char* chars = env->GetStringUTFChars(jstr, nullptr);
    std::string ret(chars);
    env->ReleaseStringUTFChars(jstr, chars);
    return ret;
}

jclass MySDKJNIHelper::getClassID(std::string className)
{
    if (className.empty()) {
        return nullptr;
    }
    JNIEnv* env = MySDKJNIHelper::getJNIEnv();
    if (!env) {
        return nullptr;
    }
    return env->FindClass(className.c_str());
}

bool MySDKJNIHelper::getStaticMethodInfo(JNIMethodInfo &jniMethodInfo, std::string className, std::string methodName, std::string paramCode)
{
    if (className.empty() || methodName.empty() || paramCode.empty()) {
        return false;
    }
    JNIEnv* env = MySDKJNIHelper::getJNIEnv();
    if (!env) {
        return false;
    }
    jclass classID = MySDKJNIHelper::getClassID(className);
    if (!classID) {
        env->ExceptionClear();
        return false;
    }
    jmethodID methodID = env->GetStaticMethodID(classID, methodName.c_str(), paramCode.c_str());
    if (!methodID) {
        env->ExceptionClear();
        return false;
    }
    jniMethodInfo.classID = classID;
    jniMethodInfo.env = env;
    jniMethodInfo.methodID = methodID;
    return true;
}

