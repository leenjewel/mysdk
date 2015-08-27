#include "MySDKLuaCallback.h"
#include "tolua_mysdk.h"
#include "MySDKLog.h"

using namespace mysdk;

MySDKLuaCallback::MySDKLuaCallback(lua_State* L, int handle):
MySDKCallback(nullptr),
_l(L),
_luaHandle(handle)
{
}

MySDKLuaCallback::~MySDKLuaCallback()
{
}

bool MySDKLuaCallback::_executeLuaFunction(int argc)
{
    if (!_l) return false;
    toluamysdk_get_function_by_refid(_l, _luaHandle);
    if (!lua_isfunction(_l, -1)) {
        lua_pop(_l, 1);
        return false;
    }
    if (argc > 0) {
        lua_insert(_l, -(argc + 1));
    }
    int functionIndex = -(argc + 1);
    if (!lua_isfunction(_l, functionIndex)) {
        lua_pop(_l, argc + 1);
        lua_settop(_l, 0);
        return false;
    }
    int traceback = 0;
    lua_getglobal(_l, "__G__TRACKBACK__");
    if (!lua_isfunction(_l, -1)) {
        lua_pop(_l, 1);
    } else {
        lua_insert(_l, functionIndex - 1);
        traceback = functionIndex - 1;
    }
    int error = lua_pcall(_l, argc, 1, traceback);
    if (error) {
        if (traceback == 0) {
            LOGE("Lua Error : %s", lua_tostring(_l, -1));
            lua_pop(_l, 1);
        } else {
            lua_pop(_l, 2);
        }
        lua_settop(_l, 0);
        return false;
    }
    int luaRet = 0;
    if (lua_isnumber(_l, -1)) {
        luaRet = (int)lua_tointeger(_l, -1);
    } else if (lua_isboolean(_l, -1)) {
        luaRet = (int)lua_toboolean(_l, -1);
    }
    lua_pop(_l, 1);
    if (traceback) {
        lua_pop(_l, 1);
    }
    lua_settop(_l, 0);
    return true;
}

#define CPPSTRING2CONSTCHAR(cstr) (cstr.empty()?"":cstr.c_str())

void MySDKLuaCallback::onSuccess(std::string sdkName, std::string methodName, std::string result)
{
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(sdkName));
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(methodName));
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(result));
    _executeLuaFunction(3);
}

void MySDKLuaCallback::onFail(std::string sdkName, std::string methodName, int errorCode, std::string errorMessage, std::string result)
{
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(sdkName));
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(methodName));
    lua_pushnumber(_l, errorCode);
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(errorMessage));
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(result));
    _executeLuaFunction(5);
}

void MySDKLuaCallback::onCancel(std::string sdkName, std::string methodName, std::string result)
{
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(sdkName));
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(methodName));
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(result));
    _executeLuaFunction(3);
}

void MySDKLuaCallback::onPayResult(bool isError, int errorCode, std::string errorMessage, std::string sdkName, std::string productID, std::string orderID, std::string result)
{
    lua_pushboolean(_l, isError);
    lua_pushnumber(_l, errorCode);
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(errorMessage));
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(sdkName));
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(productID));
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(orderID));
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(result));
    _executeLuaFunction(7);
}


