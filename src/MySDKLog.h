#ifndef __MYSDK_LOG_H__
#define __MYSDK_LOG_H__

#include <android/log.h>

#define LOG_TAG    "MySDK"
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#if MYSDK_DEBUG
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define LOGD(...)  do{}while(0);
#endif

#endif

