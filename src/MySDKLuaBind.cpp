#include "MySDKLuaBind.h"
#include "MySDK.h"
#include "MySDKLuaCallback.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "lauxlib.h"
#include "lualib.h"
#include "tolua++.h"
#ifdef __cplusplus
}
#endif
#include "tolua_mysdk.h"

typedef int LUA_FUNCTION;

using namespace mysdk;

bool luaval_to_std_string(lua_State* L, int lo, std::string* ret)
{
    if (NULL == L || NULL == ret) {
        return false;
    }
    if (lua_isnil(L,lo) || lua_isstring(L, lo)) {
        *ret = tolua_tocppstring(L,lo,NULL);
    }
    return true;
}

int mysdk_has_sdk(lua_State* L)
{
    int argc = lua_gettop(L) - 1;
    if (argc >= 1) {
        bool ok = true;
        std::string sdkName;
        ok &= luaval_to_std_string(L, 2, &sdkName);
        if (!ok) {
            return 0;
        }
        bool ret = MySDK::hasSDK(sdkName);
        tolua_pushboolean(L, ret);
    }
    return 0;
}

#define LUA_MYSDK_APPLY_BEGIN \
    do {\
        int argc = lua_gettop(L) - 1; \
        if (argc >= 3) { \
            bool ok = true; \
            std::string sdkName; \
            std::string methodName; \
            std::string params; \
            ok &= luaval_to_std_string(L, 2, &sdkName); \
            if (!ok) return 0; \
            ok &= luaval_to_std_string(L, 3, &methodName); \
            if (!ok) return 0; \
            ok &= luaval_to_std_string(L, 4, &params); \
            if (!ok) return 0;

#define LUA_MYSDK_APPLY_END \
        }\
    } while(0);\
    return 0;

int mysdk_apply_sdk_method_and_return_int(lua_State* L)
{
LUA_MYSDK_APPLY_BEGIN
        int ret = MySDK::applySDKMethodAndReturnInt(sdkName, methodName, params);
        tolua_pushnumber(L, ret);
LUA_MYSDK_APPLY_END
}

int mysdk_apply_sdk_method_and_return_long(lua_State* L)
{
LUA_MYSDK_APPLY_BEGIN
        long ret = MySDK::applySDKMethodAndReturnLong(sdkName, methodName, params);
        tolua_pushnumber(L, ret);
LUA_MYSDK_APPLY_END
}

int mysdk_apply_sdk_method_and_return_float(lua_State* L)
{
LUA_MYSDK_APPLY_BEGIN
        float ret = MySDK::applySDKMethodAndReturnFloat(sdkName, methodName, params);
        tolua_pushnumber(L, ret);
LUA_MYSDK_APPLY_END
}

int mysdk_apply_sdk_method_and_return_double(lua_State* L)
{
LUA_MYSDK_APPLY_BEGIN
        double ret = MySDK::applySDKMethodAndReturnDouble(sdkName, methodName, params);
        tolua_pushnumber(L, ret);
LUA_MYSDK_APPLY_END
}

int mysdk_apply_sdk_method_and_return_boolean(lua_State* L)
{
LUA_MYSDK_APPLY_BEGIN
        bool ret = MySDK::applySDKMethodAndReturnBoolean(sdkName, methodName, params);
        tolua_pushboolean(L, ret);
LUA_MYSDK_APPLY_END
}

int mysdk_apply_sdk_method_and_return_string(lua_State* L)
{
LUA_MYSDK_APPLY_BEGIN
        std::string ret = MySDK::applySDKMethodAndReturnString(sdkName, methodName, params);
        tolua_pushstring(L, ret.c_str());
LUA_MYSDK_APPLY_END
}

int mysdk_apply_sdk_method_with_callback(lua_State* L)
{
LUA_MYSDK_APPLY_BEGIN
    LUA_FUNCTION luaFunctionHandle = toluamysdk_ref_function(L, 5, 0);
    int callbackHandle = MySDKCallback::addCallback(new MySDKLuaCallback(L, luaFunctionHandle));
    MySDK::applySDKMethodWithCallback(sdkName, methodName, params, callbackHandle);
LUA_MYSDK_APPLY_END
}

int mysdk_apply_sdk_pay(lua_State* L)
{
    int argc = lua_gettop(L) - 1;
    if (argc >= 5) {
        bool ok = true;
        std::string sdkName;
        std::string productID;
        std::string orderID;
        std::string params;
        ok &= luaval_to_std_string(L,2,&sdkName);
        if (!ok) return 0;
        ok &= luaval_to_std_string(L,3,&productID);
        if (!ok) return 0;
        ok &= luaval_to_std_string(L,4,&orderID);
        if (!ok) return 0;
        ok &= luaval_to_std_string(L,5,&params);
        if (!ok) return 0;
        LUA_FUNCTION luaFunctionHandle = toluamysdk_ref_function(L, 6, 0);
        int callbackHandle = MySDKCallback::addCallback(new MySDKLuaCallback(L, luaFunctionHandle));
        MySDK::applySDKPay(sdkName, productID, orderID, params, callbackHandle);
    }
    return 0;
}

int register_mysdk_to_lua(lua_State* L)
{
    toluamysdk_open(L);
    luaL_Reg mysdkRegs[] = {
        {"hasSDK", mysdk_has_sdk},
        {"applySDKMethodAndReturnInt", mysdk_apply_sdk_method_and_return_int},
        {"applySDKMethodAndReturnLong", mysdk_apply_sdk_method_and_return_long},
        {"applySDKMethodAndReturnFloat", mysdk_apply_sdk_method_and_return_float},
        {"applySDKMethodAndReturnDouble", mysdk_apply_sdk_method_and_return_double},
        {"applySDKMethodAndReturnBoolean", mysdk_apply_sdk_method_and_return_boolean},
        {"applySDKMethodAndReturnString", mysdk_apply_sdk_method_and_return_string},
        {"applySDKMethodWithCallback", mysdk_apply_sdk_method_with_callback},
        {"applySDKPay", mysdk_apply_sdk_pay},
        {NULL,NULL}
    };
    luaL_newmetatable(L, "mysdk_MySDK");
    luaL_register(L, NULL, mysdkRegs);
    lua_setfield(L, -1, "__index");
    lua_setglobal(L, "MySDK");
    return 0;
}

