package com.leenjewel.mysdk.sdk;

import com.leenjewel.mysdk.callback.IMySDKCallback;
import com.leenjewel.mysdk.exception.MySDKDoNotImplementMethod;

import android.app.Activity;
import android.app.Application;
import android.content.Intent;
import android.os.Bundle;

public interface IMySDK {
	
	public void applicationOnCreate(Application application);
	
	public void activityOnCreate(Activity activity, Bundle savedInstanceState);
	public void activityOnStart(Activity activity);
	public void activityOnRestart(Activity activity);
	public void activityOnResume(Activity activity);
	public void activityOnPause(Activity activity);
	public void activityOnStop(Activity activity);
	public void activityOnDestroy(Activity activity);
	
	public void activityOnSaveInstanceState(Activity activity, Bundle outState);
	public void activityOnNewIntent(Activity activity, Intent intent);
	public void activityOnActivityResult(Activity activity, int requestCode, int resultCode, Intent data);

	public int applySDKMethodAndReturnInt(String methodName, String params) throws MySDKDoNotImplementMethod;
	public long applySDKMethodAndReturnLong(String methodName, String params) throws MySDKDoNotImplementMethod;
	public float applySDKMethodAndReturnFloat(String methodName, String params) throws MySDKDoNotImplementMethod;
	public double applySDKMethodAndReturnDouble(String methodName, String params) throws MySDKDoNotImplementMethod;
	public boolean applySDKMethodAndReturnBoolean(String methodName, String params) throws MySDKDoNotImplementMethod;
	public String applySDKMethodAndReturnString(String methodName, String params) throws MySDKDoNotImplementMethod;
	
	public void applySDKMethodWithCallback(String methodName, String params, IMySDKCallback callback);
	public void applySDKPay(String productID, String orderID, String params, IMySDKCallback callback);
}
