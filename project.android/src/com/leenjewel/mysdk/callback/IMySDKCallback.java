package com.leenjewel.mysdk.callback;

public interface IMySDKCallback {
	
	public void onSuccess(String sdkName, String result);
	
	public void onFail(String sdkName, String error, String result);
	
	public void onCancel(String sdkName, String result);
	
	public void onPayResult(boolean isError, String errorMessage, String sdkName, String productID, String orderID, String result);

}
