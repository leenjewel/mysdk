LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE        :=  mysdksdkexample


LOCAL_C_INCLUDES    :=  $(JNI_H_INCLUDE)\
	$(LOCAL_PATH)/../jni
	
	
LOCAL_SRC_FILES     := \
	../jni/MySDKSDKExampleJavaNativeMethod.cpp

LOCAL_LDLIBS :=  -llog

include $(BUILD_SHARED_LIBRARY)
