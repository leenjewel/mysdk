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

#import <Foundation/Foundation.h>
#include "MySDK.h"

using namespace mysdk;


bool MySDK::hasSDK(std::string sdkName)
{
    return false;
}


int MySDK::applySDKMethodAndReturnInt(std::string sdkName, std::string methodName, std::string params)
{
    return -1;
}


long MySDK::applySDKMethodAndReturnLong(std::string sdkName, std::string methodName, std::string params)
{
    return -1;
}


float MySDK::applySDKMethodAndReturnFloat(std::string sdkName, std::string methodName, std::string params)
{
    return -1.0f;
}


double MySDK::applySDKMethodAndReturnDouble(std::string sdkName, std::string methodName, std::string params)
{
    return -1.0;
}


bool MySDK::applySDKMethodAndReturnBoolean(std::string sdkName, std::string methodName, std::string params)
{
    return false;
}


std::string MySDK::applySDKMethodAndReturnString(std::string sdkName, std::string methodName, std::string params)
{
    return "";
}


void MySDK::applySDKMethodWithCallback(std::string sdkName, std::string methodName, std::string params, int callbackHandle)
{
    
}


void MySDK::applySDKMethodWithCallback(std::string sdkName, std::string methodName, std::string params, MySDKListener *listener)
{
    
}


void MySDK::applySDKPay(std::string sdkName, std::string productID, std::string orderID, std::string params, int callbackHandle)
{
    
}


void MySDK::applySDKPay(std::string sdkName, std::string productID, std::string orderID, std::string params, MySDKListener *listener)
{
    
}
