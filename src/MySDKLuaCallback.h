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

#ifndef __MYSDK_LUA_CALLBACK_H__
#define __MYSDK_LUA_CALLBACK_H__

#include "MySDKCallback.h"
#include "MySDKLuaBind.h"

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
