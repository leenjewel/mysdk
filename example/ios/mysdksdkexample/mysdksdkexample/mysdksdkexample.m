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

#import "mysdksdkexample.h"

@implementation mysdksdkexample

- (BOOL) application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    NSLog(@"mysdksdkexample application:didFinishLaunchingWithOptions:");
    return YES;
}


- (int) applySDKMethod:(NSString*)methodname AndReturnInt:(NSString*)params
{
    return 1;
}

- (long) applySDKMethod:(NSString*)methodname AndReturnLong:(NSString*)params
{
    return 2;
}

- (float) applySDKMethod:(NSString*)methodname AndReturnFloat:(NSString*)params
{
    return 3.33f;
}

- (double) applySDKMethod:(NSString*)methodname AndReturnDouble:(NSString*)params
{
    return 4.44;
}

- (BOOL) applySDKMethod:(NSString*)methodname AndReturnBoolean:(NSString*)params
{
    return ((params && [params length] > 0)?YES:false);
}

- (NSString*) applySDKMethod:(NSString*)methodname AndReturnString:(NSString*)params
{
    return @"Hi I am mysdksdkexample";
}



@end
