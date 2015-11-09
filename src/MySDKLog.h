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

#ifndef __MYSDK_LOG_H__
#define __MYSDK_LOG_H__

#if MYSDK_FOR_ANDROID
#include <android/log.h>

#define LOG_TAG    "MySDK"
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#if MYSDK_DEBUG
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define LOGD(...)  do{}while(0)
#endif
#endif

#if MYSDK_FOR_IOS
#define LOG_TAG    @"MySDK"
#define LOGW(...)  do{}while(0)
#define LOGE(...)  do{}while(0)
#if MYSDK_DEBUG
#define LOGD(...)  do{}while(0)
#else
#define LOGD(...)  do{}while(0)
#endif
#endif

#endif

