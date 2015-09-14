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

package com.leenjewel.mysdk.callback;

public interface IMySDKCallback {
	
	public void onSuccess(String sdkName, String methodName, String result);
	
	public void onFail(String sdkName, String methodName, int errorCode, String errorMessage, String result);
	
	public void onCancel(String sdkName, String methodName, String result);
	
	public void onPayResult(boolean isError, int errorCode, String errorMessage, String sdkName, String productID, String orderID, String result);

}
