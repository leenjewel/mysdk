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

#import "ViewController.h"
#import "MySDKKit.h"
#include "MySDKListener.h"

using namespace mysdk;

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UIButton *btnApplySDKMethodAndReturnInt;
@property (weak, nonatomic) IBOutlet UIButton *btnApplySDKMethodAndReturnLong;
@property (weak, nonatomic) IBOutlet UIButton *btnApplySDKMethodAndReturnFloat;
@property (weak, nonatomic) IBOutlet UIButton *btnApplySDKMethodAndReturnDouble;
@property (weak, nonatomic) IBOutlet UIButton *btnApplySDKMethodAndReturnBoolean;
@property (weak, nonatomic) IBOutlet UIButton *btnApplySDKMethodAndReturnString;
@property (weak, nonatomic) IBOutlet UIButton *btnApplySDKMethodWithCallback;
@property (weak, nonatomic) IBOutlet UIButton *btnApplySDKPayWithCallback;
@property (weak, nonatomic) IBOutlet UITextView *textViewTestResult;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#define SDKID    @"mysdksdkexample"

- (IBAction)onBtnApplySDKMethodAndReturnInt:(id)sender {
    int ret = [[MySDKKit getInstance] applySDK:SDKID Method:@"test" AndReturnInt:@""];
    [[self textViewTestResult] setText:[NSString stringWithFormat:@"%@ applySDKMethodAndReturnInt return %d", SDKID, ret]];
}

- (IBAction)onBtnApplySDKMethodAndReturnLong:(id)sender {
    long ret = [[MySDKKit getInstance] applySDK:SDKID Method:@"test" AndReturnLong:@""];
    [[self textViewTestResult] setText:[NSString stringWithFormat:@"%@ applySDKMethodAndReturnLong return %ld", SDKID, ret]];
}
- (IBAction)onBtnApplySDKMethodAndReturnFloat:(id)sender {
    float ret = [[MySDKKit getInstance] applySDK:SDKID Method:@"test" AndReturnFloat:@""];
    [[self textViewTestResult] setText:[NSString stringWithFormat:@"%@ applySDKMethodAndReturnFloat return %f", SDKID, ret]];
}
- (IBAction)onBtnApplySDKMethodAndReturnDouble:(id)sender {
    double ret = [[MySDKKit getInstance] applySDK:SDKID Method:@"test" AndReturnDouble:@""];
    [[self textViewTestResult] setText:[NSString stringWithFormat:@"%@ applySDKMethodAndReturnDouble return %lf", SDKID, ret]];
}
- (IBAction)onBtnApplySDKMethodAndReturnBoolean:(id)sender {
    BOOL ret = [[MySDKKit getInstance] applySDK:SDKID Method:@"test" AndReturnBoolean:@""];
    [[self textViewTestResult] setText:[NSString stringWithFormat:@"%@ applySDKMethodAndReturnBoolean return %s", SDKID, (ret?"TRUE":"FALSE")]];
}
- (IBAction)onBtnApplySDKMethodAndReturnString:(id)sender {
    NSString* ret = [[MySDKKit getInstance] applySDK:SDKID Method:@"test" AndReturnString:@""];
    [[self textViewTestResult] setText:[NSString stringWithFormat:@"%@ applySDKMethodAndReturnString return %@", SDKID, ret]];
}
- (IBAction)onBtnApplySDKMethodWithCallback:(id)sender {
    MySDKiOSListener* listener = [[MySDKiOSListener alloc] init];
    [listener onSuccess:^(NSString *sdkname, NSString *methodname, NSString *result) {
        [[self textViewTestResult] setText:[NSString stringWithFormat:@"%@ applySDKMethodWithCallback callback SUCCESS %@", SDKID, result]];
    }];
    [listener onCancel:^(NSString *sdkname, NSString *methodname, NSString *result) {
        [[self textViewTestResult] setText:[NSString stringWithFormat:@"%@ applySDKMethodWithCallback callback CANCEL %@", SDKID, result]];
    }];
    [listener onFail:^(NSString *sdkname, NSString *methodname, int errorcode, NSString* error, NSString *result) {
        [[self textViewTestResult] setText:[NSString stringWithFormat:@"%@ applySDKMethodWithCallback callback FAIL %d %@ %@", SDKID, errorcode, error, result]];
    }];
    [[MySDKKit getInstance] applySDK:SDKID Method:@"test" WithParams:@"" AndCallback:listener];
}
- (IBAction)onBtnApplySDKPay:(id)sender {
    MySDKiOSListener* listener = [[MySDKiOSListener alloc] init];
    [listener onPayResult:^(BOOL iserror, int errorcode, NSString *error, NSString *sdkname, NSString *productid, NSString *orderid, NSString *result) {
        [[self textViewTestResult] setText:[NSString stringWithFormat:@"%@ applySDKPay callback %@ %d %@ %@ %@ %@", SDKID, (iserror?@"ERROR":@"SUCCESS"), errorcode, error, productid, orderid, result]];
    }];
    [[MySDKKit getInstance] applySDK:SDKID Pay:@"testPorductID" Order:@"testOrderID" WithParams:@"" AndCallback:listener];
}

@end
