#APP_STL := c++_static
#NDK_TOOLCHAIN_VERSION=clang
APP_PLATFORM:=android-8
APP_STL := gnustl_static
NDK_TOOLCHAIN_VERSION=4.9

APP_CPPFLAGS := -frtti -std=c++11 -fsigned-char
APP_LDFLAGS := -latomic

APP_DEBUG := $(strip $(NDK_DEBUG))
ifeq ($(APP_DEBUG),1)
  APP_OPTIM := debug
else
  APP_OPTIM := release
endif