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
		int btnID = btn.getId();
		switch (btnID) {
		case R.id.btnApplySDKMethodAndReturnInt:
			ret += "btnApplySDKMethodAndReturnInt\n";
			int intRet = MySDK.applySDKMethodAndReturnInt(SDK_NAME, "add", "1");
			ret += "return: "+String.valueOf(intRet)+"\n";
			break;
		case R.id.btnApplySDKMethodAndReturnLong:
			ret += "btnApplySDKMethodAndReturnLong\n";
			long longRet = MySDK.applySDKMehtodAndReturnLong(SDK_NAME, "add", "2");
			ret += "return: "+String.valueOf(longRet)+"\n";
			break;
		case R.id.btnApplySDKMethodAndReturnFloat:
			ret += "btnApplySDKMethodAndReturnFloat\n";
			float floatRet = MySDK.applySDKMethodAndReturnFloat(SDK_NAME, "add", "3");
			ret += "return: "+String.valueOf(floatRet)+"\n";
			break;
		case R.id.btnApplySDKMethodAndReturnDouble:
			ret += "btnApplySDKMethodAndReturnDouble\n";
			double doubleRet = MySDK.applySDKMethodAndReturnDouble(SDK_NAME, "add", "4");
			ret += "return: "+String.valueOf(doubleRet)+"\n";
			break;
		case R.id.btnApplySDKMethodAndReturnBoolean:
			ret += "btnApplySDKMethodAndReturnBoolean\n";
			boolean booleanRet = MySDK.applySDKMethodAndReturnBoolean(SDK_NAME, "!", "true");
			ret += (booleanRet?"return: true\n":"return: false\n");
			break;
		case R.id.btnApplySDKMethodAndReturnString:
			ret += "btnApplySDKMethodAndReturnString\n";
			String stringRet = MySDK.applySDKMethodAndReturnString(SDK_NAME, "hello-world", "Hello");
			ret += "return: "+stringRet+"\n";
			break;
		case R.id.btnApplySDKMethodWithCallback:
			ret += "btnApplySDKMethodWithCallback\n";
			MySDK.applySDKMethodWithCallback(SDK_NAME, "test", "", new IMySDKCallback(){

				@Override
				public void onCancel(String arg0, String arg1, String arg2) {
					// TODO Auto-generated method stub
					TextView tv = (TextView)MySDKAPPExampleActivity.this.findViewById(R.id.textViewResult);
					tv.setText(tv.getText()+"callback: onCancel(" + arg2 + ")\n");
				}

				@Override
				public void onFail(String arg0, String arg1, int arg2, String arg3, String arg4) {
					// TODO Auto-generated method stub
					TextView tv = (TextView)MySDKAPPExampleActivity.this.findViewById(R.id.textViewResult);
					tv.setText(tv.getText()+"callback: onFail(" + arg3 + ")\n");
				}

				@Override
				public void onPayResult(boolean arg0, int arg1, String arg2, String arg3, String arg4, String arg5,
						String arg6) {
					// TODO Auto-generated method stub
					TextView tv = (TextView)MySDKAPPExampleActivity.this.findViewById(R.id.textViewResult);
					tv.setText(tv.getText()+"callback: onPayResult\n");
				}

				@Override
				public void onSuccess(String arg0, String arg1, String arg2) {
					// TODO Auto-generated method stub
					TextView tv = (TextView)MySDKAPPExampleActivity.this.findViewById(R.id.textViewResult);
					tv.setText(tv.getText()+"callback: onSuccess(" + arg2 + ")\n");
				}});
			break;
		case R.id.btnApplySDKPay:
			ret += "btnApplySDKPay\n";
			MySDK.applySDKPay(SDK_NAME, "productID", "orderID", "", new IMySDKCallback(){

				@Override
				public void onCancel(String arg0, String arg1, String arg2) {
					// TODO Auto-generated method stub
					TextView tv = (TextView)MySDKAPPExampleActivity.this.findViewById(R.id.textViewResult);
					tv.setText(tv.getText()+"callback: onCancel(" + arg2 + ")\n");
				}

				@Override
				public void onFail(String arg0, String arg1, int arg2, String arg3, String arg4) {
					// TODO Auto-generated method stub
					TextView tv = (TextView)MySDKAPPExampleActivity.this.findViewById(R.id.textViewResult);
					tv.setText(tv.getText()+"callback: onFail(" + arg3 + ")\n");
				}

				@Override
				public void onPayResult(boolean arg0, int arg1, String arg2, String arg3, String arg4, String arg5,
						String arg6) {
					// TODO Auto-generated method stub
					TextView tv = (TextView)MySDKAPPExampleActivity.this.findViewById(R.id.textViewResult);
					tv.setText(tv.getText()+"callback: onPayResult("+arg6+")\n");
				}

				@Override
				public void onSuccess(String arg0, String arg1, String arg2) {
					// TODO Auto-generated method stub
					TextView tv = (TextView)MySDKAPPExampleActivity.this.findViewById(R.id.textViewResult);
					tv.setText(tv.getText()+"callback: onSuccess(" + arg2 + ")\n");
				}});
			break;
		default :
			break;
		}
		TextView result = (TextView)this.findViewById(R.id.textViewResult);
		result.setText(ret);
		} catch (MySDKDoNotImplementMethod e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
}
