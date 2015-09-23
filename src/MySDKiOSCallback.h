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

#ifndef MySDKiOSCallback_h
#define MySDKiOSCallback_h

#import <Foundation/Foundation.h>
#import "MySDKiOSDelegate.h"

@interface MySDKiOSCallback : NSObject<MySDKiOSCallbackDelegate>
{
    int _handler;
}

- (id) init:(int)handler;

- (void) onApplySDK:(NSString*)sdkname Method:(NSString*)methodname Success:(NSString*)result;

- (void) onApplySDK:(NSString*)sdkname Method:(NSString*)methodname Cancel:(NSString*)result;

- (void) onApplySDK:(NSString*)sdkname Method:(NSString*)methodname Fail:(int)errorcode WithError:(NSString*)error AndResult:(NSString*)result;

- (void) onApplySDK:(NSString*)sdkname Pay:(NSString*)productid Order:(NSString*)orderid Fail:(int)errorcode WithError:(NSString*)error AndResult:(NSString*)result;

- (void) onApplySDK:(NSString*)sdkname Pay:(NSString*)productid Order:(NSString*)orderid Success:(NSString*)result;

@end

#endif /* MySDKiOSCallback_h */
