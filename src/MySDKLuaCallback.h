#ifndef __MYSDK_LUA_CALLBACK_H__
#define __MYSDK_LUA_CALLBACK_H__

#include "MySDKCallback.h"
extern "C"
{
#include "lua.h"
}

namespace mysdk
{
    class MySDKLuaCallback : public MySDKCallback
    {
        public:
            MySDKLuaCallback(lua_State* L, int handle);
            virtual ~MySDKLuaCallback();
            virtual void onSuccess(std::string sdkName, std::string methodName, std::string result);
            virtual void onFail(std::string sdkName, std::string methodName, int errorCode, std::string errorMessage, std::string result);
            virtual void onCancel(std::string sdkName, std::string methodName, std::string result);
            virtual void onPayResult(bool isError, int errorCode, std::string errorMessage, std::string sdkName, std::string productID, std::string orderID, std::string result);
            
        private:
            int _luaHandle;
            lua_State* _l;
            bool _executeLuaFunction(int argc);
    };
};

#endif
