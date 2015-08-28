package com.leenjewel.mysdk.sdk;

import com.leenjewel.mysdk.callback.IMySDKCallback;
import com.leenjewel.mysdk.exception.MySDKDoNotImplementMethod;

import android.app.Activity;
import android.app.Application;
import android.content.Intent;
import android.os.Bundle;

public class NullMySDK implements IMySDK {
	
	protected String _sdkName = null;
	
	public NullMySDK(String sdkName) {
		_sdkName = sdkName;
	}
	
	static public NullMySDK getNullMySDK(String sdkName) {
		return new NullMySDK(sdkName);
	}

	@Override
	public void applicationOnCreate(Application application) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void activityOnCreate(Activity activity, Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void activityOnStart(Activity activity) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void activityOnRestart(Activity activity) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void activityOnResume(Activity activity) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void activityOnPause(Activity activity) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void activityOnStop(Activity activity) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void activityOnDestroy(Activity activity) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void activityOnSaveInstanceState(Activity activity, Bundle outState) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void activityOnNewIntent(Activity activity, Intent intent) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void activityOnActivityResult(Activity activity, int requestCode, int resultCode, Intent data) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public int applySDKMethodAndReturnInt(String methodName, String params) throws MySDKDoNotImplementMethod {
		// TODO Auto-generated method stub
		throw new MySDKDoNotImplementMethod(_sdkName, "applySDKMethodAndReturnInt");
	}

	@Override
	public long applySDKMethodAndReturnLong(String methodName, String params) throws MySDKDoNotImplementMethod {
		// TODO Auto-generated method stub
		throw new MySDKDoNotImplementMethod(_sdkName, "applySDKMethßodAndReturnLong");
	}

	@Override
	public float applySDKMethodAndReturnFloat(String methodName, String params) throws MySDKDoNotImplementMethod {
		// TODO Auto-generated method stub
		throw new MySDKDoNotImplementMethod(_sdkName, "applySDKMethodAndReturnFloat");
	}

	@Override
	public double applySDKMethodAndReturnDouble(String methodName, String params) throws MySDKDoNotImplementMethod {
		// TODO Auto-generated method stub
		throw new MySDKDoNotImplementMethod(_sdkName, "applySDKMethodAndReturnDouble");
	}

	@Override
	public boolean applySDKMethodAndReturnBoolean(String methodName, String params) throws MySDKDoNotImplementMethod {
		// TODO Auto-generated method stub
		throw new MySDKDoNotImplementMethod(_sdkName, "applySDKMethodAndReturnBoolean");
	}

	@Override
	public String applySDKMethodAndReturnString(String methodName, String params) throws MySDKDoNotImplementMethod {
		// TODO Auto-generated method stub
		throw new MySDKDoNotImplementMethod(_sdkName, "applySDKMethodAndReturnString");
	}

	@Override
	public void applySDKMethodWithCallback(String methodName, String params, IMySDKCallback callback) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void applySDKPay(String productID, String orderID, String params, IMySDKCallback callback) {
		// TODO Auto-generated method stub
		
	}
}
