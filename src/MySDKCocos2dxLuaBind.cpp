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

#include "MySDKLuaBind.h"
#include "MySDK.h"
#include "MySDKLuaCallback.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"

using namespace mysdk;

int mysdk_has_sdk(lua_State* L)
{
    int argc = lua_gettop(L);
    if (argc >= 1) {
        bool ok = true;
        std::string sdkName;
        ok &= luaval_to_std_string(L, 1, &sdkName);
        if (!ok) {
            return 0;
        }
        bool ret = MySDK::hasSDK(sdkName);
        tolua_pushboolean(L, ret);
        return 1;
    }
    return 0;
}

#define LUA_MYSDK_APPLY_BEGIN(applyName) \
    do {\
        LOGD("MySDKCocos2dxLuaBind BEGIN %s", #applyName);\
        int argc = lua_gettop(L); \
        if (argc >= 3) { \
            bool ok = true; \
            std::string sdkName; \
            std::string methodName; \
            std::string params; \
            ok &= luaval_to_std_string(L, 1, &sdkName); \
            if (!ok) { \
                LOGW("MySDKCocos2dxLuaBind %s sdkName error from luaval.", #applyName);\
                return 0;\
            } \
            LOGD("MySDKCocos2dxLuaBind sdkName = %s", sdkName.c_str());\
            ok &= luaval_to_std_string(L, 2, &methodName); \
            if (!ok) { \
                LOGW("MySDKCocos2dxLuaBind %s methodName error from luaval.", #applyName);\
                return 0;\
            } \
            LOGD("MySDKCocos2dxLuaBind methodName = %s", methodName.c_str());\
            ok &= luaval_to_std_string(L, 3, &params); \
            if (!ok) { \
                LOGW("MySDKCocos2dxLuaBind %s params error from luaval.", #applyName);\
                return 0;\
            } \
            LOGD("MySDKCocos2dxLuaBind params = %s", params.c_str());\

#define LUA_MYSDK_APPLY_END \
        } else {\
            LOGW("MySDKCocos2dxLuaBind argc = %d less than 3", argc);\
        }\
    } while(0);\
    return 0;

int mysdk_apply_sdk_method_and_return_int(lua_State* L)
{
LUA_MYSDK_APPLY_BEGIN(applySDKMethodAndReturnInt)
        int ret = MySDK::applySDKMethodAndReturnInt(sdkName, methodName, params);
        tolua_pushnumber(L, (lua_Number)ret);
        return 1;
LUA_MYSDK_APPLY_END
}

int mysdk_apply_sdk_method_and_return_long(lua_State* L)
{
LUA_MYSDK_APPLY_BEGIN(applySDKMethodAndReturnLong)
        long ret = MySDK::applySDKMethodAndReturnLong(sdkName, methodName, params);
        tolua_pushnumber(L, (lua_Number)ret);
        return 1;
LUA_MYSDK_APPLY_END
}

int mysdk_apply_sdk_method_and_return_float(lua_State* L)
{
LUA_MYSDK_APPLY_BEGIN(applySDKMethodAndReturnFloat)
        float ret = MySDK::applySDKMethodAndReturnFloat(sdkName, methodName, params);
        tolua_pushnumber(L, (lua_Number)ret);
        return 1;
LUA_MYSDK_APPLY_END
}

int mysdk_apply_sdk_method_and_return_double(lua_State* L)
{
LUA_MYSDK_APPLY_BEGIN(applySDKMethodAndReturnDouble)
        double ret = MySDK::applySDKMethodAndReturnDouble(sdkName, methodName, params);
        tolua_pushnumber(L, (lua_Number)ret);
        return 1;
LUA_MYSDK_APPLY_END
}

int mysdk_apply_sdk_method_and_return_boolean(lua_State* L)
{
LUA_MYSDK_APPLY_BEGIN(applySDKMethodAndReturnBoolean)
        bool ret = MySDK::applySDKMethodAndReturnBoolean(sdkName, methodName, params);
        tolua_pushboolean(L, ret);
        return 1;
LUA_MYSDK_APPLY_END
}

int mysdk_apply_sdk_method_and_return_string(lua_State* L)
{
LUA_MYSDK_APPLY_BEGIN(applySDKMethodAndReturnString)
        std::string ret = MySDK::applySDKMethodAndReturnString(sdkName, methodName, params);
        tolua_pushcppstring(L, ret);
        return 1;
LUA_MYSDK_APPLY_END
}

int mysdk_apply_sdk_method_with_callback(lua_State* L)
{
LUA_MYSDK_APPLY_BEGIN(applySDKMethodWithCallback)
    LUA_FUNCTION luaFunctionHandle = toluafix_ref_function(L, 4, 0);
    int callbackHandle = MySDKCallback::addCallback(new MySDKLuaCallback(L, luaFunctionHandle));
    MySDK::applySDKMethodWithCallback(sdkName, methodName, params, callbackHandle);
LUA_MYSDK_APPLY_END
}

int mysdk_apply_sdk_pay(lua_State* L)
{
    int argc = lua_gettop(L);
    if (argc >= 5) {
        bool ok = true;
        std::string sdkName;
        std::string productID;
        std::string orderID;
        std::string params;
        ok &= luaval_to_std_string(L,1,&sdkName);
        if (!ok) {
            LOGW("MySDKCocos2dxLuaBind applySDKPay sdkName error from luaval.");
            return 0;
        }
        ok &= luaval_to_std_string(L,2,&productID);
        if (!ok) {
            LOGW("MySDKCocos2dxLuaBind applySDKPay productID error from luaval.");
            return 0;
        }
        ok &= luaval_to_std_string(L,3,&orderID);
        if (!ok) {
            LOGW("MySDKCocos2dxLuaBind applySDKPay orderID error from luaval.");
            return 0;
        }
        ok &= luaval_to_std_string(L,4,&params);
        if (!ok) {
            LOGW("MySDKCocos2dxLuaBind applySDKPay params error from luaval.");
            return 0;
        }
        LUA_FUNCTION luaFunctionHandle = toluafix_ref_function(L, 5, 0);
        int callbackHandle = MySDKCallback::addCallback(new MySDKLuaCallback(L, luaFunctionHandle));
        MySDK::applySDKPay(sdkName, productID, orderID, params, callbackHandle);
    }
    return 0;
}

int register_mysdk_to_lua(lua_State* L)
{
    tolua_open(L);

    tolua_module(L, "MySDK", 0);
    tolua_beginmodule(L, "MySDK");

    tolua_function(L, "hasSDK", mysdk_has_sdk);
    tolua_function(L, "applySDKMethodAndReturnInt", mysdk_apply_sdk_method_and_return_int);
    tolua_function(L, "applySDKMethodAndReturnLong", mysdk_apply_sdk_method_and_return_long);
    tolua_function(L, "applySDKMethodAndReturnFloat", mysdk_apply_sdk_method_and_return_float);
    tolua_function(L, "applySDKMethodAndReturnDouble", mysdk_apply_sdk_method_and_return_double);
    tolua_function(L, "applySDKMethodAndReturnBoolean", mysdk_apply_sdk_method_and_return_boolean);
    tolua_function(L, "applySDKMethodAndReturnString", mysdk_apply_sdk_method_and_return_string);
    tolua_function(L, "applySDKMethodWithCallback", mysdk_apply_sdk_method_with_callback);
    tolua_function(L, "applySDKPay", mysdk_apply_sdk_pay);

    tolua_endmodule(L);
    return 0;
}

