package com.leenjewel.mysdk.sdk;

import com.leenjewel.mysdk.callback.IMySDKCallback;

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

	public int applySDKMethodAndReturnInt(String params);
	public float applySDKMethodAndReturnFloat(String params);
	public double applySDKMethodAndReturnDouble(String params);
	public boolean applySDKMethodAndReturnBoolean(String params);
	public String applySDKMethodAndReturnString(String params);
	public void applySDKMethodWithCallback(String params, IMySDKCallback callback);
	
	public void applySDKPay(String productID, String orderID, String params, IMySDKCallback callback);
}
