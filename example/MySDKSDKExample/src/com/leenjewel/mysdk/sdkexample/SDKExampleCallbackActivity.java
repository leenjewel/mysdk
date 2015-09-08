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
