#include "MySDKLuaCallback.h"
#include "MySDKLog.h"
#include "CCLuaEngine.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"

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
    auto engine = cocos2d::LuaEngine::getInstance();
    cocos2d::ScriptEngineManager::getInstance()->setScriptEngine(engine);
    cocos2d::LuaStack *stack =  engine->getLuaStack();
    stack->executeFunctionByHandler(_luaHandle, argc);
}

#define CPPSTRING2CONSTCHAR(cstr) (cstr.empty()?"":cstr.c_str())

void MySDKLuaCallback::onSuccess(std::string sdkName, std::string methodName, std::string result)
{
    lua_pushboolean(_l, false);
    lua_pushnumber(_l, 0);
    lua_pushstring(_l, "");
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(sdkName));
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(methodName));
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(result));
    _executeLuaFunction(6);
}

void MySDKLuaCallback::onFail(std::string sdkName, std::string methodName, int errorCode, std::string errorMessage, std::string result)
{
    lua_pushboolean(_l, true);
    lua_pushnumber(_l, errorCode);
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(errorMessage));
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(sdkName));
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(methodName));
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(result));
    _executeLuaFunction(6);
}

void MySDKLuaCallback::onCancel(std::string sdkName, std::string methodName, std::string result)
{
    lua_pushboolean(_l, true);
    lua_pushnumber(_l, 1);
    lua_pushstring(_l, "user canceled");
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(sdkName));
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(methodName));
    lua_pushstring(_l, CPPSTRING2CONSTCHAR(result));
    _executeLuaFunction(6);
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


