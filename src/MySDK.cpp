#include "MySDK.h"
#include "MySDKJNIHelper.h"
#include "MySDKCallback.h"

#define MYSDK_CLASS_NAME "com/leenjewel/mysdk/sdk/MySDK"

#define MYSDK_APPLY_BEGIN(methodName,paramCode) \
    std::string applyMethodName = std::string(methodName);\
    JNIMethodInfo jniMethodInfo; \
    bool isMethodExists = MySDKJNIHelper::getStaticMethodInfo(\
            jniMethodInfo,\
            MYSDK_CLASS_NAME,\
            methodName,\
            paramCode\
    );\
    if (isMethodExists) {\
        LOGD("%s has found.\n", applyMethodName.c_str());

#define MYSDK_INIT_APPLY_PARAMS \
    jstring jsdkName = jniMethodInfo.env->NewStringUTF(sdkName.c_str());\
    jstring jmethodName = jniMethodInfo.env->NewStringUTF(methodName.c_str());\
    jstring jparams = jniMethodInfo.env->NewStringUTF(params.c_str());

#define MYSDK_CLEAN_APPLY_PARAMS \
    jniMethodInfo.env->DeleteLocalRef(jsdkName);\
    jniMethodInfo.env->DeleteLocalRef(jmethodName);\
    jniMethodInfo.env->DeleteLocalRef(jparams);
            
#define MYSDK_METHOD_NOT_EXISTS } else { \
    LOGE("%s not found.\n", applyMethodName.c_str());
#define MYSDK_APPLY_END }

using namespace mysdk;

bool MySDK::hasSDK(std::string sdkName)
{
MYSDK_APPLY_BEGIN("hasSDK", "(Ljava/lang/String;)Z")
    jstring jsdkName = jniMethodInfo.env->NewStringUTF(sdkName.c_str());
    jboolean ret = jniMethodInfo.env->CallStaticBooleanMethod(jniMethodInfo.classID, jniMethodInfo.methodID, jsdkName);
    jniMethodInfo.env->DeleteLocalRef(jsdkName);
    return (ret?true:false);
MYSDK_METHOD_NOT_EXISTS
    return false;
MYSDK_APPLY_END
}

int MySDK::applySDKMethodAndReturnInt(std::string sdkName, std::string methodName, std::string params)
{
MYSDK_APPLY_BEGIN("applySDKMethodAndReturnInt", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I")
    MYSDK_INIT_APPLY_PARAMS
    jint ret = jniMethodInfo.env->CallStaticIntMethod(jniMethodInfo.classID, jniMethodInfo.methodID, jsdkName, jmethodName, jparams);
    MYSDK_CLEAN_APPLY_PARAMS
    return (int)ret;
MYSDK_METHOD_NOT_EXISTS
    return -1;
MYSDK_APPLY_END
}

long MySDK::applySDKMethodAndReturnLong(std::string sdkName, std::string methodName, std::string params)
{
MYSDK_APPLY_BEGIN("applySDKMethodAndReturnLong", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)J")
    MYSDK_INIT_APPLY_PARAMS
    jlong ret = jniMethodInfo.env->CallStaticLongMethod(jniMethodInfo.classID, jniMethodInfo.methodID, jsdkName, jmethodName, jparams);
    MYSDK_CLEAN_APPLY_PARAMS
    return ret;
MYSDK_METHOD_NOT_EXISTS
    return -1;
MYSDK_APPLY_END
}

float MySDK::applySDKMethodAndReturnFloat(std::string sdkName, std::string methodName, std::string params)
{
MYSDK_APPLY_BEGIN("applySDKMethodAndReturnFloat", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)F")
    MYSDK_INIT_APPLY_PARAMS
    jfloat ret = jniMethodInfo.env->CallStaticFloatMethod(jniMethodInfo.classID, jniMethodInfo.methodID, jsdkName, jmethodName, jparams);
    MYSDK_CLEAN_APPLY_PARAMS
    return ret;
MYSDK_METHOD_NOT_EXISTS
    return -1;
MYSDK_APPLY_END
}

double MySDK::applySDKMethodAndReturnDouble(std::string sdkName, std::string methodName, std::string params)
{
MYSDK_APPLY_BEGIN("applySDKMethodAndReturnDouble", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)D")
    MYSDK_INIT_APPLY_PARAMS
    jdouble ret = jniMethodInfo.env->CallStaticDoubleMethod(jniMethodInfo.classID, jniMethodInfo.methodID, jsdkName, jmethodName, jparams);
    MYSDK_CLEAN_APPLY_PARAMS
    return ret;
MYSDK_METHOD_NOT_EXISTS
    return -1;
MYSDK_APPLY_END
}

bool MySDK::applySDKMethodAndReturnBoolean(std::string sdkName, std::string methodName, std::string params)
{
MYSDK_APPLY_BEGIN("applySDKMethodAndReturnBoolean", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z")
    MYSDK_INIT_APPLY_PARAMS
    jboolean ret = jniMethodInfo.env->CallStaticBooleanMethod(jniMethodInfo.classID, jniMethodInfo.methodID, jsdkName, jmethodName, jparams);
    MYSDK_CLEAN_APPLY_PARAMS
    return (ret?true:false);
MYSDK_METHOD_NOT_EXISTS
    return false;
MYSDK_APPLY_END
}

std::string MySDK::applySDKMethodAndReturnString(std::string sdkName, std::string methodName, std::string params)
{
MYSDK_APPLY_BEGIN("applySDKMethodAndReturnString", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;")
    MYSDK_INIT_APPLY_PARAMS
    jstring jret = (jstring)jniMethodInfo.env->CallStaticObjectMethod(jniMethodInfo.classID, jniMethodInfo.methodID, jsdkName, jmethodName, jparams);
    std::string ret = MySDKJNIHelper::jstring2string(jret);
    MYSDK_CLEAN_APPLY_PARAMS
    jniMethodInfo.env->DeleteLocalRef(jret);
    return ret;
MYSDK_METHOD_NOT_EXISTS
    return "";
MYSDK_APPLY_END
}

void MySDK::applySDKMethodWithCallback(std::string sdkName, std::string methodName, std::string params, int callbackHandle)
{
    MYSDK_APPLY_BEGIN("applySDKMethodWithCallback", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V")
        MYSDK_INIT_APPLY_PARAMS
        jniMethodInfo.env->CallStaticVoidMethod(jniMethodInfo.classID, jniMethodInfo.methodID, jsdkName, jmethodName, jparams, callbackHandle);
        MYSDK_CLEAN_APPLY_PARAMS
    MYSDK_METHOD_NOT_EXISTS
        MySDKCallback* callback = MySDKCallback::getCallback(callbackHandle);
        if (callback) {
            callback->onFail(sdkName, methodName, -1, "applySDKMethodWithCallback not found.", "");
        }
    MYSDK_APPLY_END
}

void MySDK::applySDKMethodWithCallback(std::string sdkName, std::string methodName, std::string params, MySDKListener* listener)
{
    MySDKCallback* callback = new MySDKCallback(listener);
    int callbackHandle = MySDKCallback::addCallback(callback);
    MySDK::applySDKMethodWithCallback(sdkName, methodName, params, callbackHandle);
}

void MySDK::applySDKPay(std::string sdkName, std::string productID, std::string orderID, std::string params, int callbackHandle)
{
    MYSDK_APPLY_BEGIN("applySDKPay", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V")
        jstring jsdkName = jniMethodInfo.env->NewStringUTF(sdkName.c_str());
        jstring jproductID = jniMethodInfo.env->NewStringUTF(productID.c_str());
        jstring jorderID = jniMethodInfo.env->NewStringUTF(orderID.c_str());
        jstring jparams = jniMethodInfo.env->NewStringUTF(params.c_str());
        jniMethodInfo.env->CallStaticVoidMethod(jniMethodInfo.classID, jniMethodInfo.methodID, jsdkName, jproductID, jorderID, jparams, callbackHandle);
        jniMethodInfo.env->DeleteLocalRef(jsdkName);
        jniMethodInfo.env->DeleteLocalRef(jproductID);
        jniMethodInfo.env->DeleteLocalRef(jorderID);
        jniMethodInfo.env->DeleteLocalRef(jparams);
    MYSDK_METHOD_NOT_EXISTS
        MySDKCallback* callback = MySDKCallback::getCallback(callbackHandle);
        if (callback) {
            callback->onPayResult(1, -1, "applySDKPay not found.", sdkName, productID, orderID, params);
        }
    MYSDK_APPLY_END
}

void MySDK::applySDKPay(std::string sdkName, std::string productID, std::string orderID, std::string params, MySDKListener* listener)
{
    MySDKCallback* callback = new MySDKCallback(listener);
    int callbackHandle = MySDKCallback::addCallback(callback);
    MySDK::applySDKPay(sdkName, productID, orderID, params, callbackHandle);
}

