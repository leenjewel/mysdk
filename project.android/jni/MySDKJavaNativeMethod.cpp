#include <jni.h>
#include <android/log.h>
#include "MySDKCallback.h"

#define LOG_TAG    "MySDK"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace mysdk;

extern "C"
{
    std::string jstring2string(JNIEnv* env, jstring jstr)
    {
        if (!env || !jstr) {
            return "";
        }
        const char* chars = env->GetStringUTFChars(jstr, NULL);
        std::string ret(chars);
        env->ReleaseStringUTFChars(jstr, chars);
        return ret;
    }

    int Java_com_leenjewel_mysdk_callback_MySDKCallback_onSuccessByHandle(JNIEnv* env, jobject thisz, jint handle, jstring jsdkName, jstring jmethodName, jstring jresult)
    {
        if (!handle) {
            return 0;
        }
        MySDKCallback *callback = MySDKCallback::getCallback(handle);
        if (!callback) {
            return 0;
        }
        std::string sdkName = jstring2string(env, jsdkName);
        std::string methodName = jstring2string(env, jmethodName);
        std::string result = jstring2string(env, jresult);
        callback->onSuccess(sdkName, methodName, result);
        MySDKCallback::cleanCallback(handle);
    }

    int Java_com_leenjewel_mysdk_callback_MySDKCallback_onFailByHandle(JNIEnv* env, jobject thisz, jint handle, jstring jsdkName, jstring jmethodName, jint errorCode, jstring jerrorMessage, jstring jresult)
    {
        if (!handle) {
            return 0;
        }
        MySDKCallback *callback = MySDKCallback::getCallback(handle);
        if (!callback) {
            return 0;
        }
        std::string errorMessage = jstring2string(env, jerrorMessage);
        std::string sdkName = jstring2string(env, jsdkName);
        std::string methodName = jstring2string(env, jmethodName);
        std::string result = jstring2string(env, jresult);
        callback->onFail(sdkName, methodName, errorCode, errorMessage, result);
        MySDKCallback::cleanCallback(handle);
    }

    int Java_com_leenjewel_mysdk_callback_MySDKCallback_onCancelByHandle(JNIEnv* env, jobject thisz, jint handle, jstring jsdkName, jstring jmethodName, jstring jresult)
    {
        if (!handle) {
            return 0;
        }
        MySDKCallback *callback = MySDKCallback::getCallback(handle);
        if (!callback) {
            return 0;
        }
        std::string sdkName = jstring2string(env, jsdkName);
        std::string methodName = jstring2string(env, jmethodName);
        std::string result = jstring2string(env, jresult);
        callback->onCancel(sdkName, methodName, result);
        MySDKCallback::cleanCallback(handle);
    }

    int Java_com_leenjewel_mysdk_callback_MySDKCallback_onPayResultByHandle(JNIEnv* env, jobject thisz, jint handle, jboolean isError, jint errorCode, jstring jerrorMessage, jstring jsdkName, jstring jproductID, jstring jorderID, jstring jresult)
    {
        if (!handle) {
            return 0;
        }
        MySDKCallback *callback = MySDKCallback::getCallback(handle);
        if (!callback) {
            return 0;
        }
        std::string errorMessage = jstring2string(env, jerrorMessage);
        std::string sdkName = jstring2string(env, jsdkName);
        std::string productID = jstring2string(env, jproductID);
        std::string orderID = jstring2string(env, jorderID);
        std::string result = jstring2string(env, jresult);
        callback->onPayResult(isError, errorCode, errorMessage, sdkName, productID, orderID, result);
        MySDKCallback::cleanCallback(handle);
        return 0;
    }
}

