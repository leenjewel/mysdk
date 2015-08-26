#include <jni.h>
#include <android/log.h>
#include "MySDKJNIHelper.h"
#include "MySDKCallback.h"

using namespace mysdk;

extern "C"
{
    jint JNI_OnLoad(JavaVM* jvm, void* reserved)
    {
        MySDKJNIHelper::setJavaVM(jvm);
        return JNI_VERSION_1_4;
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
        std::string sdkName = MySDKJNIHelper::jstring2string(jsdkName);
        std::string methodName = MySDKJNIHelper::jstring2string(jmethodName);
        std::string result = MySDKJNIHelper::jstring2string(jresult);
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
        std::string errorMessage = MySDKJNIHelper::jstring2string(jerrorMessage);
        std::string sdkName = MySDKJNIHelper::jstring2string(jsdkName);
        std::string methodName = MySDKJNIHelper::jstring2string(jmethodName);
        std::string result = MySDKJNIHelper::jstring2string(jresult);
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
        std::string sdkName = MySDKJNIHelper::jstring2string(jsdkName);
        std::string methodName = MySDKJNIHelper::jstring2string(jmethodName);
        std::string result = MySDKJNIHelper::jstring2string(jresult);
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
        std::string errorMessage = MySDKJNIHelper::jstring2string(jerrorMessage);
        std::string sdkName = MySDKJNIHelper::jstring2string(jsdkName);
        std::string productID = MySDKJNIHelper::jstring2string(jproductID);
        std::string orderID = MySDKJNIHelper::jstring2string(jorderID);
        std::string result = MySDKJNIHelper::jstring2string(jresult);
        callback->onPayResult(isError, errorCode, errorMessage, sdkName, productID, orderID, result);
        MySDKCallback::cleanCallback(handle);
        return 0;
    }
}

