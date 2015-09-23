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

#include "MySDK.h"
#include "MySDKCallback.h"
#import <Foundation/Foundation.h>
#import "MySDKKit.h"
#import "MySDKiOSCallback.h"

using namespace mysdk;


bool MySDK::hasSDK(std::string sdkName)
{
    if ([[MySDKKit getInstance] hasSDK:CString2NSString(sdkName)]) {
        return true;
    }
    return false;
}


int MySDK::applySDKMethodAndReturnInt(std::string sdkName, std::string methodName, std::string params)
{
    return [[MySDKKit getInstance] applySDK:CString2NSString(sdkName)
                                     Method:CString2NSString(methodName)
                               AndReturnInt:CString2NSString(params)];
}


long MySDK::applySDKMethodAndReturnLong(std::string sdkName, std::string methodName, std::string params)
{
    return [[MySDKKit getInstance] applySDK:CString2NSString(sdkName)
                                     Method:CString2NSString(methodName)
                              AndReturnLong:CString2NSString(params)];
}


float MySDK::applySDKMethodAndReturnFloat(std::string sdkName, std::string methodName, std::string params)
{
    return [[MySDKKit getInstance] applySDK:CString2NSString(sdkName)
                                     Method:CString2NSString(methodName)
                             AndReturnFloat:CString2NSString(params)];
}


double MySDK::applySDKMethodAndReturnDouble(std::string sdkName, std::string methodName, std::string params)
{
    return [[MySDKKit getInstance] applySDK:CString2NSString(sdkName)
                                     Method:CString2NSString(methodName)
                            AndReturnDouble:CString2NSString(params)];
}


bool MySDK::applySDKMethodAndReturnBoolean(std::string sdkName, std::string methodName, std::string params)
{
    return [[MySDKKit getInstance] applySDK:CString2NSString(sdkName)
                                     Method:CString2NSString(methodName)
                           AndReturnBoolean:CString2NSString(params)];
}


std::string MySDK::applySDKMethodAndReturnString(std::string sdkName, std::string methodName, std::string params)
{
    NSString* ret = [[MySDKKit getInstance] applySDK:CString2NSString(sdkName)
                                              Method:CString2NSString(methodName)
                                     AndReturnString:CString2NSString(params)];
    return NSString2CString(ret, "");
}


void MySDK::applySDKMethodWithCallback(std::string sdkName, std::string methodName, std::string params, int callbackHandle)
{
    MySDKiOSCallback* callback = [[MySDKiOSCallback alloc] init:callbackHandle];
    [[MySDKKit getInstance] applySDK:CString2NSString(sdkName)
                              Method:CString2NSString(methodName)
                          WithParams:CString2NSString(params)
                         AndCallback:callback];
}


void MySDK::applySDKMethodWithCallback(std::string sdkName, std::string methodName, std::string params, MySDKListener *listener)
{
    MySDKCallback* cCallback = new MySDKCallback(listener);
    int handler = MySDKCallback::addCallback(cCallback);
    applySDKMethodWithCallback(sdkName, methodName, params, handler);
}


void MySDK::applySDKPay(std::string sdkName, std::string productID, std::string orderID, std::string params, int callbackHandle)
{
    MySDKiOSCallback* callback = [[MySDKiOSCallback alloc] init:callbackHandle];
    [[MySDKKit getInstance] applySDK:CString2NSString(sdkName)
                                 Pay:CString2NSString(productID)
                               Order:CString2NSString(orderID)
                          WithParams:CString2NSString(params)
                         AndCallback:callback];
}


void MySDK::applySDKPay(std::string sdkName, std::string productID, std::string orderID, std::string params, MySDKListener *listener)
{
    MySDKCallback* cCallback = new MySDKCallback(listener);
    int handler = MySDKCallback::addCallback(cCallback);
    applySDKPay(sdkName, productID, orderID, params, handler);
}
