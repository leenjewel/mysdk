/**
 * Copyright 2015 leenjewel

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

package com.leenjewel.mysdk.sdkexample;

import com.leenjewel.mysdk.sdk.AexamplesdkMySDK;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;


public class SDKExampleCallbackActivity extends Activity implements OnClickListener {
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		android.util.Log.d("MySDK", "SDKExampleCallbackActivity onCreate");
		this.setContentView(R.layout.mysdk_sdk_example_callback);
		android.util.Log.d("MySDK", "SDKExampleCallbackActivity setContentView "+String.valueOf(R.layout.mysdk_sdk_example_callback));
		
		this.findViewById(R.id.buttonSuccess).setOnClickListener(this);
		this.findViewById(R.id.buttonFail).setOnClickListener(this);
		this.findViewById(R.id.buttonCancel).setOnClickListener(this);
	}

	@Override
	public void onClick(View btn) {
		// TODO Auto-generated method stub
		int vid = btn.getId();
		if (vid == R.id.buttonSuccess) {
			this.setResult(AexamplesdkMySDK.RETURN_SUCCESS);
		} else if (vid == R.id.buttonFail) {
			this.setResult(AexamplesdkMySDK.RETURN_FAIL);
		} else if (vid == R.id.buttonCancel) {
			this.setResult(AexamplesdkMySDK.RETURN_CANCEL);
		} else {
			this.setResult(-1);
		}
		this.finish();
	}

}
