LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := mysdk

LOCAL_SRC_FILES := ../../../../project.android/libs/$(TARGET_ARCH_ABI)/libmysdk.so 

include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE        :=  mysdkappexample


LOCAL_C_INCLUDES    :=  $(JNI_H_INCLUDE)\
	$(LOCAL_PATH)/../jni \
	$(LOCAL_PATH)/../../../../src
	
	
LOCAL_SRC_FILES     := \
	../jni/MySDKAPPExampleJavaNativeMethod.cpp

LOCAL_LDLIBS :=  -llog
LOCAL_SHARED_LIBRARIES := mysdk

include $(BUILD_SHARED_LIBRARY)
