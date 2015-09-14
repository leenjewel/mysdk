/**
 * Copyright 2015 leenjewel

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

#include <stdio.h>
#include <jni.h>
#include "MySDK.h"
#include "MySDKJNIHelper.h"

using namespace mysdk;

void setTestResult(std::string ret)
{
    JNIMethodInfo jniMethodInfo;
    bool isHave = MySDKJNIHelper::getStaticMethodInfo(jniMethodInfo,
            "com/leenjewel/mysdk/appexample/MySDKAPPExampleActivity",
            "setTestResult",
            "(Ljava/lang/String;)V");
    if (isHave) {
        jstring jret = jniMethodInfo.env->NewStringUTF(ret.c_str());
        jniMethodInfo.env->CallStaticVoidMethod(jniMethodInfo.classID, jniMethodInfo.methodID, jret);
        jniMethodInfo.env->DeleteLocalRef(jret);
    }
}

extern "C"
{
    jint Java_com_leenjewel_mysdk_appexample_MySDKAPPExampleActivity_applySDKMethodAndReturnInt(JNIEnv* env, jobject thisz, jstring jsdkName, jstring jmethodName, jstring jparams)
    {
        std::string sdkName = MySDKJNIHelper::jstring2string(jsdkName);
        std::string methodName = MySDKJNIHelper::jstring2string(jmethodName);
        std::string params = MySDKJNIHelper::jstring2string(jparams);
        return MySDK::applySDKMethodAndReturnInt(sdkName, methodName, params);
    }
    
	jlong Java_com_leenjewel_mysdk_appexample_MySDKAPPExampleActivity_applySDKMethodAndReturnLong(JNIEnv* env, jobject thisz, jstring jsdkName, jstring jmethodName, jstring jparams)
    {
        std::string sdkName = MySDKJNIHelper::jstring2string(jsdkName);
        std::string methodName = MySDKJNIHelper::jstring2string(jmethodName);
        std::string params = MySDKJNIHelper::jstring2string(jparams);
        return MySDK::applySDKMethodAndReturnLong(sdkName, methodName, params);
    }
    
	jfloat Java_com_leenjewel_mysdk_appexample_MySDKAPPExampleActivity_applySDKMethodAndReturnFloat(JNIEnv* env, jobject thisz, jstring jsdkName, jstring jmethodName, jstring jparams)
    {
        std::string sdkName = MySDKJNIHelper::jstring2string(jsdkName);
        std::string methodName = MySDKJNIHelper::jstring2string(jmethodName);
        std::string params = MySDKJNIHelper::jstring2string(jparams);
        return MySDK::applySDKMethodAndReturnFloat(sdkName, methodName, params);
    }
    
	jdouble Java_com_leenjewel_mysdk_appexample_MySDKAPPExampleActivity_applySDKMethodAndReturnDouble(JNIEnv* env, jobject thisz, jstring jsdkName, jstring jmethodName, jstring jparams)
    {
        std::string sdkName = MySDKJNIHelper::jstring2string(jsdkName);
        std::string methodName = MySDKJNIHelper::jstring2string(jmethodName);
        std::string params = MySDKJNIHelper::jstring2string(jparams);
        return MySDK::applySDKMethodAndReturnDouble(sdkName, methodName, params);
    }
    
	jboolean Java_com_leenjewel_mysdk_appexample_MySDKAPPExampleActivity_applySDKMethodAndReturnBoolean(JNIEnv* env, jobject thisz, jstring jsdkName, jstring jmethodName, jstring jparams)
    {
        std::string sdkName = MySDKJNIHelper::jstring2string(jsdkName);
        std::string methodName = MySDKJNIHelper::jstring2string(jmethodName);
        std::string params = MySDKJNIHelper::jstring2string(jparams);
        return MySDK::applySDKMethodAndReturnBoolean(sdkName, methodName, params);
    }
    
	jstring Java_com_leenjewel_mysdk_appexample_MySDKAPPExampleActivity_applySDKMethodAndReturnString(JNIEnv* env, jobject thisz, jstring jsdkName, jstring jmethodName, jstring jparams)
    {
        std::string sdkName = MySDKJNIHelper::jstring2string(jsdkName);
        std::string methodName = MySDKJNIHelper::jstring2string(jmethodName);
        std::string params = MySDKJNIHelper::jstring2string(jparams);
        std::string ret = MySDK::applySDKMethodAndReturnString(sdkName, methodName, params);
        return env->NewStringUTF(ret.c_str());
    }

#define MYSDK_STR_CHAR(str) (str.empty()?"":str.c_str())
    
	void Java_com_leenjewel_mysdk_appexample_MySDKAPPExampleActivity_applySDKMethodWithCallback(JNIEnv* env, jobject thisz, jstring jsdkName, jstring jmethodName, jstring jparams)
    {
        MySDKListener* listener = new MySDKListener();
        listener->onSuccess = [](std::string sdkName, std::string methodName, std::string result)->void
        {
            LOGD("MySDKAPPExampleJavaNativeMethod listener->onSuccess");
            char ret[1024] = {0};
            int l = sprintf(ret, "[CPP Test]return: %s->%s(%s)\n", MYSDK_STR_CHAR(sdkName), MYSDK_STR_CHAR(methodName), MYSDK_STR_CHAR(result));
            LOGD("MySDKAPPExampleJavaNativeMethod setTestResult");
            setTestResult(std::string(ret));
        };
        listener->onFail = [](std::string sdkName, std::string methodName, int errorCode, std::string errorMessage, std::string result)->void
        {
            LOGD("MySDKAPPExampleJavaNativeMethod listener->onFail");
            char ret[1024] = {0};
            int l = sprintf(ret, "[CPP Test]return: %s->%s(%d, %s, %s)\n", MYSDK_STR_CHAR(sdkName), MYSDK_STR_CHAR(methodName), errorCode, MYSDK_STR_CHAR(errorMessage), MYSDK_STR_CHAR(result));
            LOGD("MySDKAPPExampleJavaNativeMethod setTestResult");
            setTestResult(std::string(ret));
        };
        listener->onCancel = [](std::string sdkName, std::string methodName, std::string result)->void
        {
            LOGD("MySDKAPPExampleJavaNativeMethod listener->onCancel");
            char ret[1024] = {0};
            int l = sprintf(ret, "[CPP Test]return: %s->%s(%s)\n", MYSDK_STR_CHAR(sdkName), MYSDK_STR_CHAR(methodName), MYSDK_STR_CHAR(result));
            LOGD("MySDKAPPExampleJavaNativeMethod setTestResult");
            setTestResult(std::string(ret));
        };
        std::string sdkName = MySDKJNIHelper::jstring2string(jsdkName);
        std::string methodName = MySDKJNIHelper::jstring2string(jmethodName);
        std::string params = MySDKJNIHelper::jstring2string(jparams);
        MySDK::applySDKMethodWithCallback(sdkName, methodName, params, listener);
    }
    
	void Java_com_leenjewel_mysdk_appexample_MySDKAPPExampleActivity_applySDKPay(JNIEnv* env, jobject thisz, jstring jsdkName, jstring jproductID, jstring jorderID, jstring jparams)
    {
        MySDKListener* listener = new MySDKListener();
        listener->onPayResult = [](bool isError, int errorCode, std::string errorMessage, std::string sdkName, std::string productID, std::string orderID, std::string result)->void
        {
            char ret[1024] = {0};
            int l = sprintf(ret, "[CPP Test]return: %s->pay(%d, %d, %s, %s, %s, %s)", sdkName.c_str(),  isError, errorCode, errorMessage.c_str(), productID.c_str(), orderID.c_str(), result.c_str());
            setTestResult(std::string(ret));
        };
        std::string sdkName = MySDKJNIHelper::jstring2string(jsdkName);
        std::string productID = MySDKJNIHelper::jstring2string(jproductID);
        std::string orderID = MySDKJNIHelper::jstring2string(jorderID);
        std::string params = MySDKJNIHelper::jstring2string(jparams);
        MySDK::applySDKPay(sdkName, productID, orderID, params, listener);
    }
    
}

