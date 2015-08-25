package com.leenjewel.mysdk.exception;

public class MySDKDoNotImplementMethod extends Exception {

	/**
	 * 
	 */
	private static final long serialVersionUID = 2982971160282313395L;
	
	private String _sdkName = null;
	private String _methodName = null;
	
	public MySDKDoNotImplementMethod(String sdkName, String methodName) {
		_sdkName = sdkName;
		_methodName = methodName;
	}
	
	public void setSDKName(String sdkName) {
		_sdkName = sdkName;
	}
	
	public void setSDKMethodName(String methodName) {
		_methodName = methodName;
	}
	
	public String getMessage() {
		return _sdkName + " do not implement method : " + _methodName;
	}
	
	public String getLocalizedMessage() {
		return getMessage();
	}

}
