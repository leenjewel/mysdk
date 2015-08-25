LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE        :=  mysdk


LOCAL_C_INCLUDES    :=  $(LOCAL_PATH)/../jni \
	$(LOCAL_PATH)/../../src
	
	
LOCAL_SRC_FILES     :=  ./MySDKJavaNativeMethod.cpp \
	../../src/MySDKCallback.cpp

include $(BUILD_SHARED_LIBRARY)
