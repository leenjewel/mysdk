LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE        :=  mysdk


LOCAL_C_INCLUDES    :=  $(JNI_H_INCLUDE)\
	$(LOCAL_PATH)/../jni \
	$(LOCAL_PATH)/../../src \
	$(LOCAL_PATH)/../../src/lua \
	$(LOCAL_PATH)/../../src/tolua
	
	
LOCAL_SRC_FILES     := \
    ../../src/lua/lapi.c \
    ../../src/lua/lauxlib.c \
    ../../src/lua/lbaselib.c \
    ../../src/lua/lcode.c \
    ../../src/lua/ldblib.c \
    ../../src/lua/ldebug.c \
    ../../src/lua/ldo.c \
    ../../src/lua/ldump.c \
    ../../src/lua/lfunc.c \
    ../../src/lua/lgc.c \
    ../../src/lua/linit.c \
    ../../src/lua/liolib.c \
    ../../src/lua/llex.c \
    ../../src/lua/lmathlib.c \
    ../../src/lua/lmem.c \
    ../../src/lua/loadlib.c \
    ../../src/lua/lobject.c \
    ../../src/lua/lopcodes.c \
    ../../src/lua/loslib.c \
    ../../src/lua/lparser.c \
    ../../src/lua/lstate.c \
    ../../src/lua/lstring.c \
    ../../src/lua/lstrlib.c \
    ../../src/lua/ltable.c \
    ../../src/lua/ltablib.c \
    ../../src/lua/ltm.c \
    ../../src/lua/lua.c \
    ../../src/lua/lundump.c \
    ../../src/lua/lvm.c \
    ../../src/lua/lzio.c \
    ../../src/lua/print.c \
    ../../src/tolua/tolua_event.c \
    ../../src/tolua/tolua_mysdk.cpp \
    ../../src/tolua/tolua_is.c \
    ../../src/tolua/tolua_map.c \
    ../../src/tolua/tolua_push.c \
    ../../src/tolua/tolua_to.c \
	./MySDKJavaNativeMethod.cpp \
	../../src/MySDKListener.cpp \
	../../src/MySDKCallback.cpp \
	../../src/MySDKJNIHelper.cpp \
	../../src/MySDKLuaBind.cpp \
	../../src/MySDKLuaCallback.cpp \
	../../src/MySDK.cpp

LOCAL_LDLIBS :=  -llog

include $(BUILD_SHARED_LIBRARY)
