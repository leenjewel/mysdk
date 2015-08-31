LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE        :=  mysdk


LOCAL_C_INCLUDES    :=  $(JNI_H_INCLUDE)\
	$(LOCAL_PATH)/../jni \
	$(LOCAL_PATH)/../../src
	
	
LOCAL_SRC_FILES     := \
	./MySDKJavaNativeMethod.cpp \
	../../src/MySDKListener.cpp \
	../../src/MySDKCallback.cpp \
	../../src/MySDKJNIHelper.cpp \
	../../src/MySDK.cpp

LOCAL_LDLIBS :=  -llog

include $(BUILD_SHARED_LIBRARY)
