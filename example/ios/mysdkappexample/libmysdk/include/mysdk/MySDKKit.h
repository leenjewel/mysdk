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

#ifndef MySDKKit_h
#define MySDKKit_h

#import "MySDKiOSDelegate.h"

typedef void(^MySDKiOSOnSuccessCallback)(NSString* sdkname, NSString* methodname, NSString* result);
typedef void(^MySDKiOSOnCancelCallback)(NSString* sdkname, NSString* methodname, NSString* result);
typedef void(^MySDKiOSOnFailCallback)(NSString* sdkname, NSString* methodname, int errorcode, NSString* error, NSString* result);
typedef void(^MySDKiOSOnPayCallback)(BOOL iserror, int errorcode, NSString* error, NSString* sdkname, NSString* productid, NSString* orderid, NSString* result);

@interface MySDKiOSListener : NSObject
{
    MySDKiOSOnSuccessCallback onSuccessBlock;
    MySDKiOSOnFailCallback    onFailBlock;
    MySDKiOSOnCancelCallback  onCancelBlock;
    MySDKiOSOnPayCallback     onPayResultBlock;
}

- (id) init;

- (void) onSuccess:(MySDKiOSOnSuccessCallback)blcok;

- (void) onFail:(MySDKiOSOnFailCallback)block;

- (void) onCancel:(MySDKiOSOnCancelCallback)block;

- (void) onPayResult:(MySDKiOSOnPayCallback)block;

- (MySDKiOSOnSuccessCallback) getSuccessBlock;

- (MySDKiOSOnFailCallback) getFailBlock;

- (MySDKiOSOnCancelCallback) getCancelBlock;

- (MySDKiOSOnPayCallback) getPayResultBlock;

@end

@interface MySDKKit : NSObject<UIApplicationDelegate>
{
    UIViewController* _controller;
    NSMutableDictionary* _sdkMap;
}

+ (id) getInstance;

- (void) setupSDK;

- (void) registerSDK:(id<MySDKiOSDelegate>)sdk ByName:(NSString*)sdkname;

- (UIViewController*) getController;

- (void) setController:(UIViewController*)controller;

- (BOOL) hasSDK:(NSString*)sdkname;

- (int) applySDK:(NSString*)sdkname Method:(NSString*)methodname AndReturnInt:(NSString*)params;

- (long) applySDK:(NSString*)sdkname Method:(NSString*)methodname AndReturnLong:(NSString*)params;

- (float) applySDK:(NSString*)sdkname Method:(NSString*)methodname AndReturnFloat:(NSString*)params;

- (double) applySDK:(NSString*)sdkname Method:(NSString*)methodname AndReturnDouble:(NSString*)params;

- (BOOL) applySDK:(NSString*)sdkname Method:(NSString*)methodname AndReturnBoolean:(NSString*)params;

- (NSString*) applySDK:(NSString*)sdkname Method:(NSString*)methodname AndReturnString:(NSString*)params;


- (void) applySDK:(NSString*)sdkname Method:(NSString*)methodname WithParams:(NSString*)params AndCallback:(MySDKiOSListener*)callback;

- (void) applySDK:(NSString*)sdkname Pay:(NSString*)productid Order:(NSString*)orderid WithParams:(NSString*)params AndCallback:(MySDKiOSListener*)callback;

@end

#endif /* MySDKKit_h */
