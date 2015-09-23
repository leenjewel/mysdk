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

@interface MySDKKit : NSObject<UIApplicationDelegate>
{
    UIViewController* _controller;
    NSMutableDictionary* _sdkMap;
}

+ (id) getInstance;

- (UIViewController*) getController;

- (void) setController:(UIViewController*)controller;

- (BOOL) hasSDK:(NSString*)sdkname;

- (int) applySDK:(NSString*)sdkname Method:(NSString*)methodname AndReturnInt:(NSString*)params;

- (long) applySDK:(NSString*)sdkname Method:(NSString*)methodname AndReturnLong:(NSString*)params;

- (float) applySDK:(NSString*)sdkname Method:(NSString*)methodname AndReturnFloat:(NSString*)params;

- (double) applySDK:(NSString*)sdkname Method:(NSString*)methodname AndReturnDouble:(NSString*)params;

- (BOOL) applySDK:(NSString*)sdkname Method:(NSString*)methodname AndReturnBoolean:(NSString*)params;

- (NSString*) applySDK:(NSString*)sdkname Method:(NSString*)methodname AndReturnString:(NSString*)params;


- (void) applySDK:(NSString*)sdkname Method:(NSString*)methodname WithParams:(NSString*)params AndCallback:(id<MySDKiOSCallbackDelegate>)callback;

- (void) applySDK:(NSString*)sdkname Pay:(NSString*)productid Order:(NSString*)orderid WithParams:(NSString*)params AndCallback:(id<MySDKiOSCallbackDelegate>)callback;

@end

#endif /* MySDKKit_h */
