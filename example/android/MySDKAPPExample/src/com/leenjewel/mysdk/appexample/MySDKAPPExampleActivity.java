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

package com.leenjewel.mysdk.appexample;

import com.leenjewel.mysdk.callback.IMySDKCallback;
import com.leenjewel.mysdk.exception.MySDKDoNotImplementMethod;
import com.leenjewel.mysdk.sdk.MySDK;

import android.app.Activity;
import android.app.AlertDialog.Builder;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.Spinner;

public class MySDKAPPExampleActivity extends Activity implements OnClickListener {
	
	final static private String SDK_NAME = "aexamplesdk";

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		MySDK.setDebugMode(true);
		MySDK.onCreate(this, savedInstanceState);
		setContentView(R.layout.activity_mysdk_app_example);
		
		initSpinner();
		
		this.findViewById(R.id.btnApplySDKMethodAndReturnInt)
			.setOnClickListener(this);
		this.findViewById(R.id.btnApplySDKMethodAndReturnLong)
		.setOnClickListener(this);
		this.findViewById(R.id.btnApplySDKMethodAndReturnFloat)
		.setOnClickListener(this);
		this.findViewById(R.id.btnApplySDKMethodAndReturnDouble)
		.setOnClickListener(this);
		this.findViewById(R.id.btnApplySDKMethodAndReturnBoolean)
		.setOnClickListener(this);
		this.findViewById(R.id.btnApplySDKMethodAndReturnString)
		.setOnClickListener(this);
		this.findViewById(R.id.btnApplySDKMethodWithCallback)
		.setOnClickListener(this);
		this.findViewById(R.id.btnApplySDKPay)
		.setOnClickListener(this);
	}
	
	@Override
	protected void onResume() {
		super.onResume();
		MySDK.onResume(this);
	}
	
	@Override
	protected void onPause() {
		super.onPause();
		MySDK.onPause(this);
	}
	
	@Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		MySDK.onActivityResult(this, requestCode, resultCode, data);
	}
	
	static public void showResult(final String title, final String content) {
		final Activity activity = MySDK.getActivity();
		android.util.Log.d("MySDK", "[ "+title+" ] : "+content);
		activity.runOnUiThread(new Runnable(){

			@Override
			public void run() {
				// TODO Auto-generated method stub
				(new Builder(activity))
					.setMessage(content)
					.setTitle(title)
					.setPositiveButton("OK", null)
					.show();
			}});
	}
	static public void showResult(String content) {
		showResult("MySDK", content);
	}
	
	private void initSpinner() {
		Spinner sdkSpinner = (Spinner)this.findViewById(R.id.spinner1);
		String[] sdkNames = MySDK.getSDKNameList(this);
		if (null != sdkNames) {
			ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, sdkNames);  
	        //设置下拉列表风格  
	        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);  
	        //将适配器添加到spinner中去  
	        sdkSpinner.setAdapter(adapter);  
	        sdkSpinner.setVisibility(View.VISIBLE);//设置默认显示  
		}
	}

	@Override
	public void onClick(View btn) {
		// TODO Auto-generated method stub
		try {
		String ret = "Result:\n";
		
		CheckBox rb = (CheckBox)this.findViewById(R.id.checkBoxIsTestCPP);
		boolean isTestCPP = rb.isChecked();
		
		EditText methodText = (EditText)this.findViewById(R.id.editText1);
		String method = methodText.getText().toString();
		
		Spinner sdkSpinner = (Spinner)this.findViewById(R.id.spinner1);
		String sdkName = sdkSpinner.getSelectedItem().toString();
		if (null == sdkName || sdkName.length() == 0) {
			sdkName = SDK_NAME;
		}
		
		int btnID = btn.getId();
		
		switch (btnID) {
		case R.id.btnApplySDKMethodAndReturnInt:
			ret += "btnApplySDKMethodAndReturnInt\n";
			int intRet = 0;
			if (isTestCPP) {
				intRet = applySDKMethodAndReturnInt(sdkName, method, "10");
				ret += "[CPP Test]return: "+String.valueOf(intRet)+"\n";
			} else {
				intRet = MySDK.applySDKMethodAndReturnInt(sdkName, method, "1");
				ret += "return: "+String.valueOf(intRet)+"\n";
			}
			break;
		case R.id.btnApplySDKMethodAndReturnLong:
			ret += "btnApplySDKMethodAndReturnLong\n";
			long longRet = 0;
			if (isTestCPP) {
				longRet = applySDKMethodAndReturnLong(sdkName, method, "20");
				ret += "[CPP Test]return: "+String.valueOf(longRet)+"\n";
			} else {
				longRet = MySDK.applySDKMethodAndReturnLong(sdkName, method, "2");
				ret += "return: "+String.valueOf(longRet)+"\n";
			}
			break;
		case R.id.btnApplySDKMethodAndReturnFloat:
			ret += "btnApplySDKMethodAndReturnFloat\n";
			float floatRet = 0;
			if (isTestCPP) {
				floatRet = applySDKMethodAndReturnFloat(sdkName, method, "30");
				ret += "[CPP Test]return: "+String.valueOf(floatRet)+"\n";
			} else {
				floatRet = MySDK.applySDKMethodAndReturnFloat(sdkName, method, "3");
				ret += "return: "+String.valueOf(floatRet)+"\n";
			}
			break;
		case R.id.btnApplySDKMethodAndReturnDouble:
			ret += "btnApplySDKMethodAndReturnDouble\n";
			double doubleRet = 0;
			if (isTestCPP) {
				doubleRet = applySDKMethodAndReturnDouble(sdkName, method, "40");
				ret += "[CPP Test]return: "+String.valueOf(doubleRet)+"\n";
			} else {
				doubleRet = MySDK.applySDKMethodAndReturnDouble(sdkName, method, "4");
				ret += "return: "+String.valueOf(doubleRet)+"\n";
			}
			break;
		case R.id.btnApplySDKMethodAndReturnBoolean:
			ret += "btnApplySDKMethodAndReturnBoolean\n";
			boolean booleanRet = false;
			if (isTestCPP) {
				booleanRet = applySDKMethodAndReturnBoolean(sdkName, method, "false");
				ret += (booleanRet?"[CPP Test]return: true\n":"return: false\n");
			} else {
				booleanRet = MySDK.applySDKMethodAndReturnBoolean(sdkName, method, "true");
				ret += (booleanRet?"return: true\n":"return: false\n");
			}
			break;
		case R.id.btnApplySDKMethodAndReturnString:
			ret += "btnApplySDKMethodAndReturnString\n";
			String stringRet = "null";
			if (isTestCPP) {
				stringRet = applySDKMethodAndReturnString(sdkName, method, "Hello");
				ret += "[CPP Test]return: "+stringRet+"\n";
			} else {
				stringRet = MySDK.applySDKMethodAndReturnString(sdkName, method, "Hello");
				ret += "return: "+stringRet+"\n";
			}
			break;
		case R.id.btnApplySDKMethodWithCallback:
			ret += "btnApplySDKMethodWithCallback\n";
			if (isTestCPP) {
				applySDKMethodWithCallback(sdkName, method, "");
			} else {
			MySDK.applySDKMethodWithCallback(sdkName, method, "", new IMySDKCallback(){

				@Override
				public void onCancel(String arg0, String arg1, String arg2) {
					// TODO Auto-generated method stub
					showResult("callback: onCancel(" + arg2 + ")\n");
				}

				@Override
				public void onFail(String arg0, String arg1, int arg2, String arg3, String arg4) {
					// TODO Auto-generated method stub
					showResult("callback: onFail(" + arg3 + ")\n");
				}

				@Override
				public void onPayResult(boolean arg0, int arg1, String arg2, String arg3, String arg4, String arg5,
						String arg6) {
					// TODO Auto-generated method stub
					showResult("callback: onPayResult\n");
				}

				@Override
				public void onSuccess(String arg0, String arg1, String arg2) {
					// TODO Auto-generated method stub
					showResult("callback: onSuccess(" + arg2 + ")\n");
				}});
			}
			return;
		case R.id.btnApplySDKPay:
			ret += "btnApplySDKPay\n";
			showResult(ret);
			if (isTestCPP) {
				applySDKPay(sdkName, "productID", "orderID", "");
			} else {
			MySDK.applySDKPay(sdkName, "productID", "orderID", "", new IMySDKCallback(){

				@Override
				public void onCancel(String arg0, String arg1, String arg2) {
					// TODO Auto-generated method stub
					showResult("callback: onCancel(" + arg2 + ")\n");
				}

				@Override
				public void onFail(String arg0, String arg1, int arg2, String arg3, String arg4) {
					// TODO Auto-generated method stub
					showResult("callback: onFail(" + arg3 + ")\n");
				}

				@Override
				public void onPayResult(boolean arg0, int arg1, String arg2, String arg3, String arg4, String arg5,
						String arg6) {
					// TODO Auto-generated method stub
					showResult("callback: onPayResult("+arg6+")\n");
				}

				@Override
				public void onSuccess(String arg0, String arg1, String arg2) {
					// TODO Auto-generated method stub
					showResult("callback: onSuccess(" + arg2 + ")\n");
				}});
			}
			return;
		default :
			break;
		}
		showResult(ret);
		} catch (MySDKDoNotImplementMethod e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	static public void setTestResult(final String ret) {
		showResult(ret);
	}
	static public native int applySDKMethodAndReturnInt(String sdkName, String methodName, String params);
	static public native long applySDKMethodAndReturnLong(String sdkName, String methodName, String params);
	static public native float applySDKMethodAndReturnFloat(String sdkName, String methodName, String params);
	static public native double applySDKMethodAndReturnDouble(String sdkName, String methodName, String params);
	static public native boolean applySDKMethodAndReturnBoolean(String sdkName, String methodName, String params);
	static public native String applySDKMethodAndReturnString(String sdkName, String methodName, String params);
	static public native void applySDKMethodWithCallback(String sdkName, String methodName, String params);
	static public native void applySDKPay(String sdkName, String productID, String orderID, String params);
	
}
