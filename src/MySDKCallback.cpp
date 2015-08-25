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

    int Java_com_leenjewel_mysdk_callback_MySDKCallback_onSuccessByHandle(JNIEnv* env, jobject thisz, jint handle, jstring jsdkName, jstring jresult)
    {
        if (!handle) {
            return 0;
        }
        MySDKCallback *callback = MySDKCallback::getCallback(handle);
        if (!callback) {
            return 0;
        }
        std::string sdkName = jstring2string(env, jsdkName);
        std::string result = jstring2string(env, jresult);
        callback->onSuccess(sdkName, result);
        MySDKCallback::cleanCallback(handle);
    }

    int Java_com_leenjewel_mysdk_callback_MySDKCallback_onFailByHandle(JNIEnv* env, jobject thisz, jint handle, jstring jsdkName, jstring jerror, jstring jresult)
    {
        if (!handle) {
            return 0;
        }
        MySDKCallback *callback = MySDKCallback::getCallback(handle);
        if (!callback) {
            return 0;
        }
        std::string error = jstring2string(env, jerror);
        std::string sdkName = jstring2string(env, jsdkName);
        std::string result = jstring2string(env, jresult);
        callback->onFail(sdkName, error, result);
        MySDKCallback::cleanCallback(handle);
    }

    int Java_com_leenjewel_mysdk_callback_MySDKCallback_onCancelByHandle(JNIEnv* env, jobject thisz, jint handle, jstring jsdkName, jstring jresult)
    {
        if (!handle) {
            return 0;
        }
        MySDKCallback *callback = MySDKCallback::getCallback(handle);
        if (!callback) {
            return 0;
        }
        std::string sdkName = jstring2string(env, jsdkName);
        std::string result = jstring2string(env, jresult);
        callback->onCancel(sdkName, result);
        MySDKCallback::cleanCallback(handle);
    }

    int Java_com_leenjewel_mysdk_callback_MySDKCallback_onPayResultByHandle(JNIEnv* env, jobject thisz, jint handle, jboolean isError, jstring jerror, jstring jsdkName, jstring jproductID, jstring jorderID, jstring jresult)
    {
        if (!handle) {
            return 0;
        }
        MySDKCallback *callback = MySDKCallback::getCallback(handle);
        if (!callback) {
            return 0;
        }
        std::string error = jstring2string(env, jerror);
        std::string sdkName = jstring2string(env, jsdkName);
        std::string productID = jstring2string(env, jproductID);
        std::string orderID = jstring2string(env, jorderID);
        std::string result = jstring2string(env, jresult);
        callback->onPayResult(isError, error, sdkName, productID, orderID, result);
        MySDKCallback::cleanCallback(handle);
        return 0;
    }
}

static MySDKCallback* _head = NULL;

MySDKCallback* MySDKCallback::getCallback(int handle)
{
    MySDKCallback* callback = _head;
    while (callback) {
        if (callback->handle == handle) {
            return callback;
        }
        callback = callback->next;
    }
    return NULL;
}

int MySDKCallback::addCallback(MySDKCallback *callback)
{
    int handle = 1;
    while (MySDKCallback::getCallback(handle)) {
        handle += 1;
    }
    callback->handle = handle;
    callback->next = _head;
    _head = callback;
    return handle;
}

int MySDKCallback::cleanCallback(int handle)
{
    MySDKCallback* last = NULL;
    MySDKCallback* callback = _head;
    while (callback) {
        if (callback->handle == handle) {
            if (last) {
                last->next = callback->next;
                delete callback;
                return handle;
            } else {
                _head = callback->next;
                delete callback;
                return handle;
            }
        }
        last = callback;
        callback = callback->next;
    }
    return 0;
}

MySDKCallback::~MySDKCallback()
{
}

void MySDKCallback::onSuccess(std::string sdkName, std::string result)
{
}

void MySDKCallback::onFail(std::string sdkName, std::string error, std::string result)
{
}

void MySDKCallback::onCancel(std::string sdkName, std::string result)
{
}

void MySDKCallback::onPayResult(bool isError, std::string error, std::string sdkName, std::string productID, std::string orderID, std::string result)
{
}

