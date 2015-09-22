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

#import "MySDKKit.h"

@implementation MySDKKit

static id _instance = nil;

+ (void)initialize
{
    if (self == [MySDKKit class]) {
        _instance = [[self alloc] init];
    }
}


+ (id)getInstance
{
    return _instance;
}

- (id) init {
    self = [super init];
    _sdkMap = [[NSMutableDictionary alloc] init];
    return self;
}


- (UIViewController*)getController
{
    return _controller;
}


- (void)setController:(UIViewController *)controller
{
    _controller = controller;
}


- (BOOL) hasSDK:(NSString*)sdkname
{
    if (_sdkMap[sdkname]) {
        return YES;
    }
    return NO;
}

#define MYSDK_APPLY_SDK_METHOD_BEGIN(sdkname, methodname)\
    do {\
        id<MySDKDelegate> sdk = _sdkMap[sdkname];\
        NSAssert(sdk != nil, @"SDK %@ is nil", sdkname);\
        NSAssert(([sdk respondsToSelector:@selector(methodname)]), @"SDK %@ do not implement method %@", sdkname, @#methodname);

#define MYSDK_APPLY_SDK_METHOD_END\
    } while(0);

- (int) applySDK:(NSString*)sdkname Method:(NSString*)methodname AndReturnInt:(NSString*)params
{
    MYSDK_APPLY_SDK_METHOD_BEGIN(sdkname, applySDKMethod:AndReturnInt:)
    return [sdk applySDKMethod:methodname AndReturnInt:params];
    MYSDK_APPLY_SDK_METHOD_END
}


- (long) applySDK:(NSString*)sdkname Method:(NSString*)methodname AndReturnLong:(NSString*)params
{
    MYSDK_APPLY_SDK_METHOD_BEGIN(sdkname, applySDKMethod:AndReturnLong:)
    return [sdk applySDKMethod:methodname AndReturnLong:params];
    MYSDK_APPLY_SDK_METHOD_END
}


- (float) applySDK:(NSString*)sdkname Method:(NSString*)methodname AndReturnFloat:(NSString*)params
{
    MYSDK_APPLY_SDK_METHOD_BEGIN(sdkname, applySDKMethod:AndReturnFloat:)
    return [sdk applySDKMethod:methodname AndReturnFloat:params];
    MYSDK_APPLY_SDK_METHOD_END
}


- (double) applySDK:(NSString*)sdkname Method:(NSString*)methodname AndReturnDouble:(NSString*)params
{
    MYSDK_APPLY_SDK_METHOD_BEGIN(sdkname, applySDKMethod:AndReturnDouble:)
    return [sdk applySDKMethod:sdkname AndReturnDouble:params];
    MYSDK_APPLY_SDK_METHOD_END
}


- (BOOL) applySDK:(NSString*)sdkname Method:(NSString*)methodname AndReturnBoolean:(NSString*)params
{
    MYSDK_APPLY_SDK_METHOD_BEGIN(sdkname, applySDKMethod:AndReturnBoolean:)
    return [sdk applySDKMethod:methodname AndReturnBoolean:params];
    MYSDK_APPLY_SDK_METHOD_END
}


- (NSString*) applySDK:(NSString*)sdkname Method:(NSString*)methodname AndReturnString:(NSString*)params;
{
    MYSDK_APPLY_SDK_METHOD_BEGIN(sdkname, applySDKMethod:AndReturnString:)
    return [sdk applySDKMethod:methodname AndReturnString:params];
    MYSDK_APPLY_SDK_METHOD_END
}

@end
