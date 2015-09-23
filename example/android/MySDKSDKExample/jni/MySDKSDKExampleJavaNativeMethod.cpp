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

extern "C"
{
    jstring Java_com_leenjewel_mysdk_sdk_AexamplesdkMySDK_sayHello(JNIEnv* env, jobject thisz)
    {
        return env->NewStringUTF("Hi I say Hello!");
    }
}

