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

#import "MySDKiOSCallback.h"
#include "MySDKCallback.h"

using namespace mysdk;

@implementation MySDKiOSCallback

- (id) init:(int)handler
{
    self = [super init];
    _handler = handler;
    return self;
}


- (void) onApplySDK:(NSString*)sdkname Method:(NSString*)methodname Success:(NSString*)result
{
    dispatch_async(dispatch_get_main_queue(), ^{
        MySDKCallback* callback = MySDKCallback::getCallback(_handler);
        std::string cSDKName = NSString2CString(sdkname, "");
        std::string cMethodName = NSString2CString(methodname, "");
        std::string cResult = NSString2CString(result, "");
        callback->onSuccess(cSDKName, cMethodName, cResult);
        MySDKCallback::cleanCallback(_handler);
    });
}


- (void) onApplySDK:(NSString*)sdkname Method:(NSString*)methodname Cancel:(NSString*)result
{
    dispatch_async(dispatch_get_main_queue(), ^{
        MySDKCallback* callback = MySDKCallback::getCallback(_handler);
        std::string cSDKName = NSString2CString(sdkname, "");
        std::string cMethodName = NSString2CString(methodname, "");
        std::string cResult = NSString2CString(result, "");
        callback->onCancel(cSDKName, cMethodName, cResult);
        MySDKCallback::cleanCallback(_handler);
    });

}


- (void) onApplySDK:(NSString*)sdkname Method:(NSString*)methodname Fail:(int)errorcode WithError:(NSString*)error AndResult:(NSString*)result
{
    dispatch_async(dispatch_get_main_queue(), ^{
        MySDKCallback* callback = MySDKCallback::getCallback(_handler);
        std::string cSDKName = NSString2CString(sdkname, "");
        std::string cMethodName = NSString2CString(methodname, "");
        std::string cResult = NSString2CString(result, "");
        std::string cError = NSString2CString(error, "");
        callback->onFail(cSDKName, cMethodName, errorcode, cError, cResult);
        MySDKCallback::cleanCallback(_handler);
    });

}


- (void) onApplySDK:(NSString*)sdkname Pay:(NSString*)productid Order:(NSString*)orderid Fail:(int)errorcode WithError:(NSString*)error AndResult:(NSString*)result
{
    dispatch_async(dispatch_get_main_queue(), ^{
        MySDKCallback* callback = MySDKCallback::getCallback(_handler);
        std::string cSDKName = NSString2CString(sdkname, "");
        std::string cProductID = NSString2CString(productid, "");
        std::string cOrderID = NSString2CString(orderid, "");
        std::string cError = NSString2CString(error, "");
        std::string cResult = NSString2CString(result, "");
        callback->onPayResult(true, errorcode, cError, cSDKName, cProductID, cOrderID, cResult);
        MySDKCallback::cleanCallback(_handler);
    });
}


- (void) onApplySDK:(NSString*)sdkname Pay:(NSString*)productid Order:(NSString*)orderid Success:(NSString*)result
{
    dispatch_async(dispatch_get_main_queue(), ^{
        MySDKCallback* callback = MySDKCallback::getCallback(_handler);
        std::string cSDKName = NSString2CString(sdkname, "");
        std::string cProductID = NSString2CString(productid, "");
        std::string cOrderID = NSString2CString(orderid, "");
        std::string cResult = NSString2CString(result, "");
        callback->onPayResult(false, 0, "", cSDKName, cProductID, cOrderID, cResult);
        MySDKCallback::cleanCallback(_handler);
    });
}

@end
