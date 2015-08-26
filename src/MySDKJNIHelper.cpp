#include "MySDKJNIHelper.h"
#include <pthread.h>

using namespace mysdk;

static pthread_key_t _g_key;
static JavaVM* _jvm = nullptr;

void MySDKJNIHelper::setJavaVM(JavaVM* jvm)
{
    _jvm = jvm;
}

JavaVM* MySDKJNIHelper::getJavaVM()
{
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
    if (!env) {
        env = MySDKJNIHelper::cacheJNIEnv(_jvm);
    }
    return env;
}

std::string MySDKJNIHelper::jstring2string(jstring jstr)
{
    JNIEnv* env = MySDKJNIHelper::getJNIEnv();
    if (!env || !jstr) {
        return "";
    }
    const char* chars = env->GetStringUTFChars(jstr, NULL);
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

