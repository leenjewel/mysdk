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
        NSAssert(([sdk respondsToSelector:@selector(methodname)]),\
            @"SDK %@ do not implement method %@", sdkname, \
            NSStringFromSelector(@selector(methodname)));

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


- (void) applySDK:(NSString*)sdkname Method:(NSString*)methodname WithParams:(NSString*)params AndCallback:(MySDKiOSCallback*)callback
{
    MYSDK_APPLY_SDK_METHOD_BEGIN(sdkname, applySDK:Method:WithParams:AndCallback:)
    dispatch_async(dispatch_get_main_queue(), ^{
        [sdk applySDKMethod:methodname WithParams:params AndCallback:callback];
    });
    MYSDK_APPLY_SDK_METHOD_END
}


- (void) applySDK:(NSString*)sdkname Pay:(NSString*)productid Order:(NSString*)orderid WithParams:(NSString*)params AndCallback:(MySDKiOSCallback*)callback
{
    MYSDK_APPLY_SDK_METHOD_BEGIN(sdkname, applySDKPay:Order:WithParams:AndCallback:)
    dispatch_async(dispatch_get_main_queue(), ^{
        [sdk applySDKPay:productid Order:orderid WithParams:params AndCallback:callback];
    });
    MYSDK_APPLY_SDK_METHOD_END
}


#define MYSDK_ALL_SDK_CALL_BEGIN(methodname)\
    for (id<MySDKDelegate>sdk in [_sdkMap allValues]) {\
        if ([sdk respondsToSelector:@selector(methodname)]) {

#define MYSDK_ALL_SDK_CALL_END    }}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(nullable NSDictionary *)launchOptions
{
    MYSDK_ALL_SDK_CALL_BEGIN(application:didFinishLaunchingWithOptions:)
    [sdk application:application didFinishLaunchingWithOptions:launchOptions];
    MYSDK_ALL_SDK_CALL_END
    return YES;
}


- (void)applicationDidBecomeActive:(UIApplication *)application
{
    MYSDK_ALL_SDK_CALL_BEGIN(applicationDidBecomeActive:)
    [sdk applicationDidBecomeActive:application];
    MYSDK_ALL_SDK_CALL_END
}


- (void)applicationWillResignActive:(UIApplication *)application
{
    MYSDK_ALL_SDK_CALL_BEGIN(applicationWillResignActive:)
    [sdk applicationWillResignActive:application];
    MYSDK_ALL_SDK_CALL_END
}


- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url
{
    MYSDK_ALL_SDK_CALL_BEGIN(application:handleOpenURL:)
    [sdk application:application handleOpenURL:url];
    MYSDK_ALL_SDK_CALL_END
    return YES;
}


- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(nullable NSString *)sourceApplication annotation:(id)annotation
{
    MYSDK_ALL_SDK_CALL_BEGIN(application:openURL:sourceApplication:annotation:)
    [sdk application:application openURL:url sourceApplication:sourceApplication annotation:annotation];
    MYSDK_ALL_SDK_CALL_END
    return YES;
}


- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<NSString*, id> *)options
{
    MYSDK_ALL_SDK_CALL_BEGIN(application:openURL:options:)
    [sdk application:app openURL:url options:options];
    MYSDK_ALL_SDK_CALL_END
    return YES;
}


- (void)application:(UIApplication *)application didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings
{
    MYSDK_ALL_SDK_CALL_BEGIN(application:didRegisterUserNotificationSettings:)
    [sdk application:application didRegisterUserNotificationSettings:notificationSettings];
    MYSDK_ALL_SDK_CALL_END
}


- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
    MYSDK_ALL_SDK_CALL_BEGIN(application:didRegisterForRemoteNotificationsWithDeviceToken:)
    [sdk application:application didRegisterForRemoteNotificationsWithDeviceToken:deviceToken];
    MYSDK_ALL_SDK_CALL_END
}


- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error
{
    MYSDK_ALL_SDK_CALL_BEGIN(application:didFailToRegisterForRemoteNotificationsWithError:)
    [sdk application:application didFailToRegisterForRemoteNotificationsWithError:error];
    MYSDK_ALL_SDK_CALL_END
}


- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
{
    MYSDK_ALL_SDK_CALL_BEGIN(application:didReceiveRemoteNotification:)
    [sdk application:application didReceiveRemoteNotification:userInfo];
    MYSDK_ALL_SDK_CALL_END
}


- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification
{
    MYSDK_ALL_SDK_CALL_BEGIN(application:didReceiveLocalNotification:)
    [sdk application:application didReceiveLocalNotification:notification];
    MYSDK_ALL_SDK_CALL_END
}


- (void)application:(UIApplication *)application handleActionWithIdentifier:(nullable NSString *)identifier forLocalNotification:(UILocalNotification *)notification completionHandler:(void(^)())completionHandler
{
    MYSDK_ALL_SDK_CALL_BEGIN(application:handleActionWithIdentifier:forLocalNotification:completionHandler:)
    [sdk application:application handleActionWithIdentifier:identifier forLocalNotification:notification completionHandler:completionHandler];
    MYSDK_ALL_SDK_CALL_END
}


- (void)application:(UIApplication *)application handleActionWithIdentifier:(nullable NSString *)identifier forRemoteNotification:(NSDictionary *)userInfo withResponseInfo:(NSDictionary *)responseInfo completionHandler:(void(^)())completionHandler
{
    MYSDK_ALL_SDK_CALL_BEGIN(application:handleActionWithIdentifier:forRemoteNotification:withResponseInfo:completionHandler:)
    [sdk application:application handleActionWithIdentifier:identifier forRemoteNotification:userInfo withResponseInfo:responseInfo completionHandler:completionHandler];
    MYSDK_ALL_SDK_CALL_END
}


- (void)application:(UIApplication *)application handleActionWithIdentifier:(nullable NSString *)identifier forRemoteNotification:(NSDictionary *)userInfo completionHandler:(void(^)())completionHandler NS_AVAILABLE_IOS(8_0)
{
    MYSDK_ALL_SDK_CALL_BEGIN(application:handleActionWithIdentifier:forRemoteNotification:completionHandler:)
    [sdk application:application handleActionWithIdentifier:identifier forRemoteNotification:userInfo completionHandler:completionHandler];
    MYSDK_ALL_SDK_CALL_END
}


- (void)application:(UIApplication *)application handleActionWithIdentifier:(nullable NSString *)identifier forLocalNotification:(UILocalNotification *)notification withResponseInfo:(NSDictionary *)responseInfo completionHandler:(void(^)())completionHandler
{
    MYSDK_ALL_SDK_CALL_BEGIN(application:handleActionWithIdentifier:forLocalNotification:withResponseInfo:completionHandler:)
    [sdk application:application handleActionWithIdentifier:identifier forLocalNotification:notification withResponseInfo:responseInfo completionHandler:completionHandler];
    MYSDK_ALL_SDK_CALL_END
}


- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler
{
    MYSDK_ALL_SDK_CALL_BEGIN(application:didReceiveRemoteNotification:fetchCompletionHandler:)
    [sdk application:application didReceiveRemoteNotification:userInfo fetchCompletionHandler:completionHandler];
    MYSDK_ALL_SDK_CALL_END
}


- (void)application:(UIApplication *)application performFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler
{
    MYSDK_ALL_SDK_CALL_BEGIN(application:performFetchWithCompletionHandler:)
    [sdk application:application performFetchWithCompletionHandler:completionHandler];
    MYSDK_ALL_SDK_CALL_END
}


- (void)application:(UIApplication *)application performActionForShortcutItem:(UIApplicationShortcutItem *)shortcutItem completionHandler:(void(^)(BOOL succeeded))completionHandler
{
    MYSDK_ALL_SDK_CALL_BEGIN(application:performActionForShortcutItem:completionHandler:)
    [sdk application:application performActionForShortcutItem:shortcutItem completionHandler:completionHandler];
    MYSDK_ALL_SDK_CALL_END
}


- (void)application:(UIApplication *)application handleEventsForBackgroundURLSession:(NSString *)identifier completionHandler:(void (^)())completionHandler
{
    MYSDK_ALL_SDK_CALL_BEGIN(application:handleEventsForBackgroundURLSession:completionHandler:)
    [sdk application:application handleEventsForBackgroundURLSession:identifier completionHandler:completionHandler];
    MYSDK_ALL_SDK_CALL_END
}


- (void)application:(UIApplication *)application handleWatchKitExtensionRequest:(nullable NSDictionary *)userInfo reply:(void(^)(NSDictionary * __nullable replyInfo))reply
{
    MYSDK_ALL_SDK_CALL_BEGIN(application:handleWatchKitExtensionRequest:reply:)
    [sdk application:application handleWatchKitExtensionRequest:userInfo reply:reply];
    MYSDK_ALL_SDK_CALL_END
}



- (void)applicationShouldRequestHealthAuthorization:(UIApplication *)application
{
    MYSDK_ALL_SDK_CALL_BEGIN(applicationShouldRequestHealthAuthorization:)
    [sdk applicationShouldRequestHealthAuthorization:application];
    MYSDK_ALL_SDK_CALL_END
}



- (void)applicationDidEnterBackground:(UIApplication *)application
{
    MYSDK_ALL_SDK_CALL_BEGIN(applicationDidEnterBackground:)
    [sdk applicationDidEnterBackground:application];
    MYSDK_ALL_SDK_CALL_END
}


- (void)applicationWillEnterForeground:(UIApplication *)application
{
    MYSDK_ALL_SDK_CALL_BEGIN(applicationWillEnterForeground:)
    [sdk applicationWillEnterForeground:application];
    MYSDK_ALL_SDK_CALL_END
}



- (void)applicationProtectedDataWillBecomeUnavailable:(UIApplication *)application
{
    MYSDK_ALL_SDK_CALL_BEGIN(applicationProtectedDataWillBecomeUnavailable:)
    [sdk applicationProtectedDataWillBecomeUnavailable:application];
    MYSDK_ALL_SDK_CALL_END
}


- (void)applicationProtectedDataDidBecomeAvailable:(UIApplication *)application
{
    MYSDK_ALL_SDK_CALL_BEGIN(applicationProtectedDataDidBecomeAvailable:)
    [sdk applicationProtectedDataDidBecomeAvailable:application];
    MYSDK_ALL_SDK_CALL_END
}

@end
