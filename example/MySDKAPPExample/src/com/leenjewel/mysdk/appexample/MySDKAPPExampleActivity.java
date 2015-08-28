package com.leenjewel.mysdk.appexample;

import com.leenjewel.mysdk.callback.IMySDKCallback;
import com.leenjewel.mysdk.exception.MySDKDoNotImplementMethod;
import com.leenjewel.mysdk.sdk.MySDK;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.RadioButton;
import android.widget.TextView;

public class MySDKAPPExampleActivity extends Activity implements OnClickListener {
	
	final static private String SDK_NAME = "aexamplesdk";

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		MySDK.setDebugMode(true);
		MySDK.onCreate(this, savedInstanceState);
		setContentView(R.layout.activity_mysdk_app_example);
		
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
	public void onClick(View btn) {
		// TODO Auto-generated method stub
		try {
		String ret = "Result:\n";
		final TextView tv = (TextView)this.findViewById(R.id.textViewResult);
		RadioButton rb = (RadioButton)this.findViewById(R.id.radioButtonIsTestCPP);
		boolean isTestCPP = rb.isChecked();
		int btnID = btn.getId();
		switch (btnID) {
		case R.id.btnApplySDKMethodAndReturnInt:
			ret += "btnApplySDKMethodAndReturnInt\n";
			int intRet = 0;
			if (isTestCPP) {
				intRet = applySDKMethodAndReturnInt(SDK_NAME, "add", "10");
				ret += "[CPP Test]return: "+String.valueOf(intRet)+"\n";
			} else {
				intRet = MySDK.applySDKMethodAndReturnInt(SDK_NAME, "add", "1");
				ret += "return: "+String.valueOf(intRet)+"\n";
			}
			break;
		case R.id.btnApplySDKMethodAndReturnLong:
			ret += "btnApplySDKMethodAndReturnLong\n";
			long longRet = 0;
			if (isTestCPP) {
				longRet = applySDKMethodAndReturnLong(SDK_NAME, "add", "20");
				ret += "[CPP Test]return: "+String.valueOf(longRet)+"\n";
			} else {
				longRet = MySDK.applySDKMehtodAndReturnLong(SDK_NAME, "add", "2");
				ret += "return: "+String.valueOf(longRet)+"\n";
			}
			break;
		case R.id.btnApplySDKMethodAndReturnFloat:
			ret += "btnApplySDKMethodAndReturnFloat\n";
			float floatRet = 0;
			if (isTestCPP) {
				floatRet = applySDKMethodAndReturnFloat(SDK_NAME, "add", "30");
				ret += "[CPP Test]return: "+String.valueOf(floatRet)+"\n";
			} else {
				floatRet = MySDK.applySDKMethodAndReturnFloat(SDK_NAME, "add", "3");
				ret += "return: "+String.valueOf(floatRet)+"\n";
			}
			break;
		case R.id.btnApplySDKMethodAndReturnDouble:
			ret += "btnApplySDKMethodAndReturnDouble\n";
			double doubleRet = 0;
			if (isTestCPP) {
				doubleRet = applySDKMethodAndReturnDouble(SDK_NAME, "add", "40");
				ret += "[CPP Test]return: "+String.valueOf(doubleRet)+"\n";
			} else {
				doubleRet = MySDK.applySDKMethodAndReturnDouble(SDK_NAME, "add", "4");
				ret += "return: "+String.valueOf(doubleRet)+"\n";
			}
			break;
		case R.id.btnApplySDKMethodAndReturnBoolean:
			ret += "btnApplySDKMethodAndReturnBoolean\n";
			boolean booleanRet = false;
			if (isTestCPP) {
				booleanRet = applySDKMethodAndReturnBoolean(SDK_NAME, "!", "false");
				ret += (booleanRet?"[CPP Test]return: true\n":"return: false\n");
			} else {
				booleanRet = MySDK.applySDKMethodAndReturnBoolean(SDK_NAME, "!", "true");
				ret += (booleanRet?"return: true\n":"return: false\n");
			}
			break;
		case R.id.btnApplySDKMethodAndReturnString:
			ret += "btnApplySDKMethodAndReturnString\n";
			String stringRet = "null";
			if (isTestCPP) {
				stringRet = applySDKMethodAndReturnString(SDK_NAME, "hello-world", "Hello");
				ret += "[CPP Test]return: "+stringRet+"\n";
			} else {
				stringRet = MySDK.applySDKMethodAndReturnString(SDK_NAME, "hello-world", "Hello");
				ret += "return: "+stringRet+"\n";
			}
			break;
		case R.id.btnApplySDKMethodWithCallback:
			ret += "btnApplySDKMethodWithCallback\n";
			tv.setText(ret);
			if (isTestCPP) {
				applySDKMethodWithCallback(SDK_NAME, "test", "");
			} else {
			MySDK.applySDKMethodWithCallback(SDK_NAME, "test", "", new IMySDKCallback(){

				@Override
				public void onCancel(String arg0, String arg1, String arg2) {
					// TODO Auto-generated method stub
					tv.setText(tv.getText()+"callback: onCancel(" + arg2 + ")\n");
				}

				@Override
				public void onFail(String arg0, String arg1, int arg2, String arg3, String arg4) {
					// TODO Auto-generated method stub
					tv.setText(tv.getText()+"callback: onFail(" + arg3 + ")\n");
				}

				@Override
				public void onPayResult(boolean arg0, int arg1, String arg2, String arg3, String arg4, String arg5,
						String arg6) {
					// TODO Auto-generated method stub
					tv.setText(tv.getText()+"callback: onPayResult\n");
				}

				@Override
				public void onSuccess(String arg0, String arg1, String arg2) {
					// TODO Auto-generated method stub
					tv.setText(tv.getText()+"callback: onSuccess(" + arg2 + ")\n");
				}});
			}
			return;
		case R.id.btnApplySDKPay:
			ret += "btnApplySDKPay\n";
			tv.setText(ret);
			if (isTestCPP) {
				applySDKPay(SDK_NAME, "productID", "orderID", "");
			} else {
			MySDK.applySDKPay(SDK_NAME, "productID", "orderID", "", new IMySDKCallback(){

				@Override
				public void onCancel(String arg0, String arg1, String arg2) {
					// TODO Auto-generated method stub
					tv.setText(tv.getText()+"callback: onCancel(" + arg2 + ")\n");
				}

				@Override
				public void onFail(String arg0, String arg1, int arg2, String arg3, String arg4) {
					// TODO Auto-generated method stub
					tv.setText(tv.getText()+"callback: onFail(" + arg3 + ")\n");
				}

				@Override
				public void onPayResult(boolean arg0, int arg1, String arg2, String arg3, String arg4, String arg5,
						String arg6) {
					// TODO Auto-generated method stub
					tv.setText(tv.getText()+"callback: onPayResult("+arg6+")\n");
				}

				@Override
				public void onSuccess(String arg0, String arg1, String arg2) {
					// TODO Auto-generated method stub
					tv.setText(tv.getText()+"callback: onSuccess(" + arg2 + ")\n");
				}});
			}
			return;
		default :
			break;
		}
		tv.setText(ret);
		} catch (MySDKDoNotImplementMethod e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	static public void setTestResult(final String ret) {
		final Activity activity = MySDK.getActivity();
		activity.runOnUiThread(new Runnable(){

			@Override
			public void run() {
				// TODO Auto-generated method stub
				TextView tv = (TextView)activity.findViewById(R.id.textViewResult);
				tv.setText(ret);
			}});
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
