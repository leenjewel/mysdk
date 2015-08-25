package com.leenjewel.mysdk.callback;

public interface IMySDKCallback {
	
	public void onSuccess(String sdkName, String methodName, String result);
	
	public void onFail(String sdkName, String methodName, int errorCode, String errorMessage, String result);
	
	public void onCancel(String sdkName, String methodName, String result);
	
	public void onPayResult(boolean isError, int errorCode, String errorMessage, String sdkName, String productID, String orderID, String result);

}
