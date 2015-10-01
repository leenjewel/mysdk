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

#ifndef __MYSDK_LISTENER_H__
#define __MYSDK_LISTENER_H__

#include <functional>

namespace mysdk
{
    class MySDKListener
    {
        public:
            MySDKListener();

            typedef std::function<void(std::string,std::string,std::string)> MySDKOnSuccessCallback;
            typedef std::function<void(std::string,std::string,int,std::string,std::string)> MySDKOnFailCallback;
            typedef std::function<void(std::string,std::string,std::string)> MySDKOnCancelCallback;
            typedef std::function<void(bool,int,std::string,std::string,std::string,std::string,std::string)> MySDKOnPayResultCallback;

            MySDKOnSuccessCallback onSuccess;
            MySDKOnFailCallback onFail;
            MySDKOnCancelCallback onCancel;
            MySDKOnPayResultCallback onPayResult;

    };
};

#endif
