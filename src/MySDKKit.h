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

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol MySDKDelegate <UIApplicationDelegate>

@optional
- (int) applySDKMethod:(NSString*)methodname AndReturnInt:(NSString*)params;

- (long) applySDKMethod:(NSString*)methodname AndReturnLong:(NSString*)params;

- (float) applySDKMethod:(NSString*)methodname AndReturnFloat:(NSString*)params;

- (double) applySDKMethod:(NSString*)methodname AndReturnDouble:(NSString*)params;

- (BOOL) applySDKMethod:(NSString*)methodname AndReturnBoolean:(NSString*)params;

- (NSString*) applySDKMethod:(NSString*)methodname AndReturnString:(NSString*)params;

@end

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

@end

#endif /* MySDKKit_h */
