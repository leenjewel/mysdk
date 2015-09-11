/**
 * Copyright 2015 leenjewel
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <jni.h>
#include <android/log.h>
#include "MySDKJNIHelper.h"
#include "MySDKCallback.h"

using namespace mysdk;

#define MYSDK_CHECK_HANDLE(handle) \
        if (!handle) {\
            LOGD("MySDKJavaNativeMethod CallbackHandle %d not found.", handle);\
            return 0;\
        }\
        MySDKCallback *callback = MySDKCallback::getCallback(handle);\
        if (!callback) {\
            LOGD("MySDKJavaNativeMethod CallbackHandle %d not found.", handle);\
            return 0;\
        }

extern "C"
{
    jint JNI_OnLoad(JavaVM* jvm, void* reserved)
    {
        MySDKJNIHelper::setJavaVM(jvm);
        return JNI_VERSION_1_4;
    }

    int Java_com_leenjewel_mysdk_callback_MySDKCallback_onSuccessByHandle(JNIEnv* env, jobject thisz, jint handle, jstring jsdkName, jstring jmethodName, jstring jresult)
    {
        MYSDK_CHECK_HANDLE(handle)
        std::string sdkName = MySDKJNIHelper::jstring2string(jsdkName);
        std::string methodName = MySDKJNIHelper::jstring2string(jmethodName);
        std::string result = MySDKJNIHelper::jstring2string(jresult);
        LOGD("MySDKJavaNativeMethod %p -> onSuccessByHandle(%d)", callback, handle);
        callback->onSuccess(sdkName, methodName, result);
        LOGD("MySDKJavaNativeMethod cleanCallback(%d)", handle);
        MySDKCallback::cleanCallback(handle);
    }

    int Java_com_leenjewel_mysdk_callback_MySDKCallback_onFailByHandle(JNIEnv* env, jobject thisz, jint handle, jstring jsdkName, jstring jmethodName, jint errorCode, jstring jerrorMessage, jstring jresult)
    {
        MYSDK_CHECK_HANDLE(handle)
        std::string errorMessage = MySDKJNIHelper::jstring2string(jerrorMessage);
        std::string sdkName = MySDKJNIHelper::jstring2string(jsdkName);
        std::string methodName = MySDKJNIHelper::jstring2string(jmethodName);
        std::string result = MySDKJNIHelper::jstring2string(jresult);
        LOGD("MySDKJavaNativeMethod %p -> onFailByHandle(%d)", callback, handle);
        callback->onFail(sdkName, methodName, errorCode, errorMessage, result);
        LOGD("MySDKJavaNativeMethod cleanCallback(%d)", handle);
        MySDKCallback::cleanCallback(handle);
    }

    int Java_com_leenjewel_mysdk_callback_MySDKCallback_onCancelByHandle(JNIEnv* env, jobject thisz, jint handle, jstring jsdkName, jstring jmethodName, jstring jresult)
    {
        MYSDK_CHECK_HANDLE(handle)
        std::string sdkName = MySDKJNIHelper::jstring2string(jsdkName);
        std::string methodName = MySDKJNIHelper::jstring2string(jmethodName);
        std::string result = MySDKJNIHelper::jstring2string(jresult);
        LOGD("MySDKJavaNativeMethod %p -> onCancelByHandle(%d)", callback, handle);
        callback->onCancel(sdkName, methodName, result);
        LOGD("MySDKJavaNativeMethod cleanCallback(%d)", handle);
        MySDKCallback::cleanCallback(handle);
    }

    int Java_com_leenjewel_mysdk_callback_MySDKCallback_onPayResultByHandle(JNIEnv* env, jobject thisz, jint handle, jboolean isError, jint errorCode, jstring jerrorMessage, jstring jsdkName, jstring jproductID, jstring jorderID, jstring jresult)
    {
        MYSDK_CHECK_HANDLE(handle)
        std::string errorMessage = MySDKJNIHelper::jstring2string(jerrorMessage);
        std::string sdkName = MySDKJNIHelper::jstring2string(jsdkName);
        std::string productID = MySDKJNIHelper::jstring2string(jproductID);
        std::string orderID = MySDKJNIHelper::jstring2string(jorderID);
        std::string result = MySDKJNIHelper::jstring2string(jresult);
        LOGD("MySDKJavaNativeMethod %p -> onPayResultByHandle(%d)", callback, handle);
        callback->onPayResult(isError, errorCode, errorMessage, sdkName, productID, orderID, result);
        LOGD("MySDKJavaNativeMethod cleanCallback(%d)", handle);
        MySDKCallback::cleanCallback(handle);
        return 0;
    }
}

