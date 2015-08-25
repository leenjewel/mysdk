include $(CLEAR_VARS)

LOCAL_MODULE        :=  mysdk
LOCAL_C_INCLUDES    :=  $(LOCAL_PATH)/jni
LOCAL_SRC_FILES := myLibrary.cpp

include $(BUILD_SHARED_LIBRARY)
