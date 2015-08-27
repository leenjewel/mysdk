package com.leenjewel.mysdk.appexample;

import com.leenjewel.mysdk.sdk.MySDK;

import android.app.Application;

public class MySDKAPPExampleApplication extends Application {

	@Override
	public void onCreate() {
		super.onCreate();
		MySDK.onCreate(this);
	}
	
}
