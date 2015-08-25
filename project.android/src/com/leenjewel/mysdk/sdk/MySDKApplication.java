package com.leenjewel.mysdk.sdk;

import android.app.Application;

public class MySDKApplication extends Application {

	@Override
	public void onCreate() {
		super.onCreate();
		MySDK.onCreate(this);
	}

}
