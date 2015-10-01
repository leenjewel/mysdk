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

- (id) init
{
    self = [super init];
    _listener = nil;
    return self;
}

- (id) init:(MySDKiOSListener*)listener
{
    self = [super init];
    _listener = listener;
    return self;
}

- (id) initWithHandler:(int)handler
{
    self = [super init];
    _listener = [[MySDKiOSListener alloc] init];
    [_listener onSuccess:^(NSString *sdkname, NSString *methodname, NSString *result) {
        MySDKCallback* callback = MySDKCallback::getCallback(handler);
        callback->onSuccess(NSString2CString(sdkname, ""), NSString2CString(methodname, ""), NSString2CString(result, ""));
    }];
    [_listener onCancel:^(NSString *sdkname, NSString *methodname, NSString *result) {
        MySDKCallback* callback = MySDKCallback::getCallback(handler);
        callback->onCancel(NSString2CString(sdkname, ""), NSString2CString(methodname, ""), NSString2CString(result, ""));
    }];
    [_listener onFail:^(NSString *sdkname, NSString *methodname, int errorcode, NSString *error, NSString *result) {
        MySDKCallback* callback = MySDKCallback::getCallback(handler);
        callback->onFail(NSString2CString(sdkname, ""), NSString2CString(methodname, ""), errorcode, NSString2CString(error, ""), NSString2CString(result, ""));
    }];
    [_listener onPayResult:^(BOOL iserror, int errorcode, NSString *error, NSString *sdkname, NSString *productid, NSString *orderid, NSString *result) {
        MySDKCallback* callback = MySDKCallback::getCallback(handler);
        callback->onPayResult(iserror, errorcode, NSString2CString(error, ""), NSString2CString(sdkname, ""), NSString2CString(productid, ""), NSString2CString(orderid, ""), NSString2CString(result, ""));
    }];
    return self;
}


- (void) onApplySDK:(NSString*)sdkname Method:(NSString*)methodname Success:(NSString*)result
{
    if (nil == _listener) {
        return;
    }
    MySDKiOSOnSuccessCallback block = [_listener getSuccessBlock];
    if (nil == block) {
        return;
    }
    dispatch_async(dispatch_get_main_queue(), ^{
        block(sdkname, methodname, result);
    });
}


- (void) onApplySDK:(NSString*)sdkname Method:(NSString*)methodname Cancel:(NSString*)result
{
    if (nil == _listener) {
        return;
    }
    MySDKiOSOnCancelCallback block = [_listener getCancelBlock];
    if (nil == block) {
        return;
    }
    dispatch_async(dispatch_get_main_queue(), ^{
        block(sdkname, methodname, result);
    });

}


- (void) onApplySDK:(NSString*)sdkname Method:(NSString*)methodname Fail:(int)errorcode WithError:(NSString*)error AndResult:(NSString*)result
{
    if (nil == _listener) {
        return;
    }
    MySDKiOSOnFailCallback block = [_listener getFailBlock];
    if (nil == block) {
        return;
    }
    dispatch_async(dispatch_get_main_queue(), ^{
        block(sdkname, methodname, errorcode, error, result);
    });

}


- (void) onApplySDK:(NSString*)sdkname Pay:(NSString*)productid Order:(NSString*)orderid Fail:(int)errorcode WithError:(NSString*)error AndResult:(NSString*)result
{
    if (nil == _listener) {
        return;
    }
    MySDKiOSOnPayCallback block = [_listener getPayResultBlock];
    if (nil == block) {
        return;
    }
    dispatch_async(dispatch_get_main_queue(), ^{
        block(YES, errorcode, error, sdkname, productid, orderid, result);
    });
}


- (void) onApplySDK:(NSString*)sdkname Pay:(NSString*)productid Order:(NSString*)orderid Success:(NSString*)result
{
    
    if (nil == _listener) {
        return;
    }
    MySDKiOSOnPayCallback block = [_listener getPayResultBlock];
    if (nil == block) {
        return;
    }
    dispatch_async(dispatch_get_main_queue(), ^{
        block(NO, 0, @"", sdkname, productid, orderid, result);
    });
}

@end
