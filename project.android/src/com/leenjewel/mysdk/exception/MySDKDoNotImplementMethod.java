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

package com.leenjewel.mysdk.exception;

public class MySDKDoNotImplementMethod extends Exception {

	/**
	 * 
	 */
	private static final long serialVersionUID = 2982971160282313395L;
	
	private String _sdkName = null;
	private String _methodName = null;
	
	public MySDKDoNotImplementMethod(String sdkName, String methodName) {
		_sdkName = sdkName;
		_methodName = methodName;
	}
	
	public void setSDKName(String sdkName) {
		_sdkName = sdkName;
	}
	
	public void setSDKMethodName(String methodName) {
		_methodName = methodName;
	}
	
	public String getMessage() {
		return _sdkName + " do not implement method : " + _methodName;
	}
	
	public String getLocalizedMessage() {
		return getMessage();
	}

}
