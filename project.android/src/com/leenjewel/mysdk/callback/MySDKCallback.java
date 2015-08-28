package com.leenjewel.mysdk.callback;

import android.app.Activity;

import com.leenjewel.mysdk.sdk.MySDK;

public class MySDKCallback implements IMySDKCallback {
	
	private int _handle = 0;
	
	public MySDKCallback(int handle) {
		_handle = handle;
	}

	@Override
	public void onSuccess(final String sdkName, final String methodName, final String result) {
		// TODO Auto-generated method stub
		Activity activity = MySDK.getActivity();
		if (null == activity) {
			MySDK.logDebug("MySDKCallback without activity onSuccess : " + String.valueOf(_handle));
			onSuccessByHandle(_handle, sdkName, methodName, result);
		} else {
			activity.runOnUiThread(new Runnable(){

				@Override
				public void run() {
					// TODO Auto-generated method stub
					MySDK.logDebug("MySDKCallback onSuccess : " + String.valueOf(_handle));
					onSuccessByHandle(_handle, sdkName, methodName, result);
				}});
		}
	}

	@Override
	public void onFail(final String sdkName, final String methodName,  final int errorCode, final String errorMessage, final String result) {
		// TODO Auto-generated method stub
		Activity activity = MySDK.getActivity();
		if (null == activity) {
			MySDK.logDebug("MySDKCallback without activity onFail : " + String.valueOf(_handle));
			onFailByHandle(_handle, sdkName, methodName, errorCode, errorMessage, result);
		} else {
			activity.runOnUiThread(new Runnable(){

				@Override
				public void run() {
					// TODO Auto-generated method stub
					MySDK.logDebug("MySDKCallback onFail : " + String.valueOf(_handle));
					onFailByHandle(_handle, sdkName, methodName, errorCode, errorMessage, result);
				}});
		}
	}

	@Override
	public void onCancel(final String sdkName, final String methodName, final String result) {
		// TODO Auto-generated method stub
		Activity activity = MySDK.getActivity();
		if (null == activity) {
			MySDK.logDebug("MySDKCallback without activity onCancel : " + String.valueOf(_handle));
			onCancelByHandle(_handle, sdkName, methodName, result);
		} else {
			activity.runOnUiThread(new Runnable(){

				@Override
				public void run() {
					// TODO Auto-generated method stub
					MySDK.logDebug("MySDKCallback onCancel : " + String.valueOf(_handle));
					onCancelByHandle(_handle, sdkName, methodName, result);
				}});
		}
	}
	
	@Override
	public void onPayResult(final boolean isError, final int errorCode, final String errorMessage,
			final String sdkName, final String productID, final String orderID, final String result) {
		// TODO Auto-generated method stub
		Activity activity = MySDK.getActivity();
		if (null == activity) {
			MySDK.logDebug("MySDKCallback without activity onPayResult : " + String.valueOf(_handle));
			onPayResultByHandle(_handle, isError, errorCode, errorMessage, sdkName, productID, orderID, result);
		} else {
			activity.runOnUiThread(new Runnable(){

				@Override
				public void run() {
					// TODO Auto-generated method stub
					MySDK.logDebug("MySDKCallback onPayResult : " + String.valueOf(_handle));
					onPayResultByHandle(_handle, isError, errorCode, errorMessage, sdkName, productID, orderID, result);
				}});
		}
	}
	
	static public native int onSuccessByHandle(int handle, String sdkName, String methodName, String result);
	static public native int onFailByHandle(int handle, String sdkName, String methodName, int errorCode, String errorMessage, String result);
	static public native int onCancelByHandle(int handle, String sdkName, String methodName, String result);
	static public native int onPayResultByHandle(int handle, boolean isError, int errorCode, String errorMessage, String sdkName, String productID, String orderID, String result);

}
