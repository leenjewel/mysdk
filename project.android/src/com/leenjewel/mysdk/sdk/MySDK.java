package com.leenjewel.mysdk.sdk;

import java.util.HashMap;

import com.leenjewel.mysdk.callback.IMySDKCallback;
import com.leenjewel.mysdk.callback.MySDKCallback;

import android.app.Activity;
import android.app.Application;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Bundle;

public class MySDK {
	
	final static public String MY_SDK_TAG = "MySDK";
	
	static private boolean _isDebugMode = false;
	static private HashMap<String, IMySDK> _sdkMap = new HashMap<String, IMySDK>();
	static private String[] _sdkNameList = null;
	static private Activity _activity = null;
	
	static public Activity getActivity() {
		return _activity;
	}

	static public void setDebugMode(boolean isDebugMode) {
		_isDebugMode = isDebugMode;
	}
	
	static private void logWaring(String log) {
		android.util.Log.w(MY_SDK_TAG, log);
	}
	
	static private void logDebug(String log) {
		if (_isDebugMode) {
			android.util.Log.d(MY_SDK_TAG, log);
		}
	}
	
	static private void logError(String log) {
		android.util.Log.e(MY_SDK_TAG, log);
	}
	
	static public IMySDK getSDK(String sdkName) {
		IMySDK sdk = _sdkMap.get(sdkName);
		if (null == sdk) {
			String sn = sdkName.toLowerCase();
			StringBuilder sb = new StringBuilder(); 
	        sb.append(Character.toUpperCase(sn.charAt(0))); 
	        sb.append(sn.substring(1)); 
	        String classPrefix = sb.toString();
	        String className = MySDK.class.getPackage().getName()+"."+classPrefix+"MySDK";
	        ClassLoader classLoader = MySDK.class.getClassLoader();
	        try {
				Class sdkClass = classLoader.loadClass(className);
				sdk = (IMySDK)sdkClass.newInstance();
				logDebug(className=" newInstance");
			} catch (ClassNotFoundException e) {
				// TODO Auto-generated catch block
				logDebug(className+" not found.");
				sdk = NullMySDK.getNullMySDK();
			} catch (InstantiationException e) {
				// TODO Auto-generated catch block
				logDebug(className+" not found.");
				sdk = NullMySDK.getNullMySDK();
			} catch (IllegalAccessException e) {
				// TODO Auto-generated catch block
				logDebug(className+" not found.");
				sdk = NullMySDK.getNullMySDK();
			} finally {
				_sdkMap.put(sdkName, sdk);
			}
		}
		return sdk;
	}
	
	static private String[] getSDKNameList(Application application) {
		if (null == _sdkNameList) {
			try {
				ApplicationInfo ai = application.getPackageManager().getApplicationInfo(application.getPackageName(), PackageManager.GET_META_DATA);
				String mySDKNameList = ai.metaData.getString("MY_SDK_NAME_LIST");
				if (null == mySDKNameList) {
					logWaring("MY_SDK_NAME_LIST is null.");
					return null;
				}
				_sdkNameList = mySDKNameList.split(",");
			} catch (NameNotFoundException e) {
				// TODO Auto-generated catch block
				logWaring("MY_SDK_NAME_LIST is null.");
				return null;
			}
		}
		return _sdkNameList;
	}
	
	static private String[] getSDKNameList(Activity activity) {
		if (null == _sdkNameList) {
			try {
				ApplicationInfo ai = activity.getPackageManager().getApplicationInfo(activity.getPackageName(), PackageManager.GET_META_DATA);
				String mySDKNameList = ai.metaData.getString("MY_SDK_NAME_LIST");
				if (null == mySDKNameList) {
					logWaring("MY_SDK_NAME_LIST is null.");
					return null;
				}
				_sdkNameList = mySDKNameList.split(",");
			} catch (NameNotFoundException e) {
				// TODO Auto-generated catch block
				logWaring("MY_SDK_NAME_LIST is null.");
				return null;
			}
		}
		return _sdkNameList;
	}
	
	static public void onCreate(Application application) {
		String[] sdkNameList = getSDKNameList(application);
		if (null == sdkNameList) {
			return;
		}
		for (String sdkName : sdkNameList) {
			IMySDK sdk = getSDK(sdkName);
			sdk.applicationOnCreate(application);
			logDebug(sdkName+" applicationOnCreate");
		}
	}
	
	static public void onCreate(Activity activity, Bundle savedInstanceState) {
		_activity = activity;
		String[] sdkNameList = getSDKNameList(activity);
		if (null == sdkNameList) {
			return;
		}
		for (String sdkName : sdkNameList) {
			IMySDK sdk = getSDK(sdkName);
			sdk.activityOnCreate(activity, savedInstanceState);
			logDebug(sdkName+" activityOnCreate");
		}
	}
	
	static public void onStart(Activity activity) {
		String[] sdkNameList = getSDKNameList(activity);
		if (null == sdkNameList) {
			return;
		}
		for (String sdkName : sdkNameList) {
			IMySDK sdk = getSDK(sdkName);
			sdk.activityOnStart(activity);
			logDebug(sdkName+" activityOnStart");
		}
	}
	
	static public void onRestart(Activity activity) {
		String[] sdkNameList = getSDKNameList(activity);
		if (null == sdkNameList) {
			return;
		}
		for (String sdkName : sdkNameList) {
			IMySDK sdk = getSDK(sdkName);
			sdk.activityOnRestart(activity);
			logDebug(sdkName+" activityOnRestart");
		}
	}

	static public void onResume(Activity activity) {
		String[] sdkNameList = getSDKNameList(activity);
		if (null == sdkNameList) {
			return;
		}
		for (String sdkName : sdkNameList) {
			IMySDK sdk = getSDK(sdkName);
			sdk.activityOnResume(activity);
			logDebug(sdkName+" activityOnResume");
		}
	}

	static public void onPause(Activity activity) {
		String[] sdkNameList = getSDKNameList(activity);
		if (null == sdkNameList) {
			return;
		}
		for (String sdkName : sdkNameList) {
			IMySDK sdk = getSDK(sdkName);
			sdk.activityOnPause(activity);
			logDebug(sdkName + " activityOnPause");
		}
	}

	static public void onStop(Activity activity) {
		String[] sdkNameList = getSDKNameList(activity);
		if (null == sdkNameList) {
			return;
		}
		for (String sdkName : sdkNameList) {
			IMySDK sdk = getSDK(sdkName);
			sdk.activityOnStop(activity);
			logDebug(sdkName + " activityOnStop");
		}
	}

	static public void onDestroy(Activity activity) {
		String[] sdkNameList = getSDKNameList(activity);
		if (null == sdkNameList) {
			return;
		}
		for (String sdkName : sdkNameList) {
			IMySDK sdk = getSDK(sdkName);
			sdk.activityOnDestroy(activity);
			logDebug(sdkName + " activityOnDestory");
		}
	}

	
	static public void onSaveInstanceState(Activity activity, Bundle outState) {
		String[] sdkNameList = getSDKNameList(activity);
		if (null == sdkNameList) {
			return;
		}
		for (String sdkName : sdkNameList) {
			IMySDK sdk = getSDK(sdkName);
			sdk.activityOnSaveInstanceState(activity, outState);
			logDebug(sdkName + " activityOnSaveInstanceState");
		}
	}

	static public void onNewIntent(Activity activity, Intent intent) {
		String[] sdkNameList = getSDKNameList(activity);
		if (null == sdkNameList) {
			return;
		}
		for (String sdkName : sdkNameList) {
			IMySDK sdk = getSDK(sdkName);
			sdk.activityOnNewIntent(activity, intent);
			logDebug(sdkName + " activityOnNewIntent");
		}
	}

	static public void onActivityResult(Activity activity, int requestCode, int resultCode, Intent data) {
		String[] sdkNameList = getSDKNameList(activity);
		if (null == sdkNameList) {
			return;
		}
		for (String sdkName : sdkNameList) {
			IMySDK sdk = getSDK(sdkName);
			sdk.activityOnActivityResult(activity, requestCode, resultCode, data);
			logDebug(sdkName + " activityOnActivityResult");
		}
	}
	
	static public int applySDKMethodAndReturnInt(String sdkName, String params) {
		IMySDK sdk = getSDK(sdkName);
		return sdk.applySDKMethodAndReturnInt(params);
	}
	
	static public float applySDKMethodAndReturnFloat(String sdkName, String params) {
		IMySDK sdk = getSDK(sdkName);
		return sdk.applySDKMethodAndReturnFloat(params);
	}

	static public double applySDKMethodAndReturnDouble(String sdkName, String params) {
		IMySDK sdk = getSDK(sdkName);
		return sdk.applySDKMethodAndReturnDouble(params);
	}

	static public boolean applySDKMethodAndReturnBoolean(String sdkName, String params) {
		IMySDK sdk = getSDK(sdkName);
		return sdk.applySDKMethodAndReturnBoolean(params);
	}

	static public String applySDKMethodAndReturnString(String sdkName, String params) {
		IMySDK sdk = getSDK(sdkName);
		return sdk.applySDKMethodAndReturnString(params);
	}

	static public void applySDKMethodWithCallback(final String sdkName, final String params, final IMySDKCallback callback) {
		final IMySDK sdk = getSDK(sdkName);
		Activity activity = getActivity();
		if (null == activity) {
			sdk.applySDKMethodWithCallback(params, callback);
		} else {
			activity.runOnUiThread(new Runnable(){

				@Override
				public void run() {
					// TODO Auto-generated method stub
					sdk.applySDKMethodWithCallback(params, callback);
				}});
		}
	}

	
	static public void applySDKPay(final String sdkName, final String productID, final String orderID, final String params, final IMySDKCallback callback) {
		final IMySDK sdk = getSDK(sdkName);
		Activity activity = getActivity();
		if (null == activity) {
			sdk.applySDKPay(productID, orderID, params, callback);
		} else {
			activity.runOnUiThread(new Runnable(){

				@Override
				public void run() {
					// TODO Auto-generated method stub
					sdk.applySDKPay(productID, orderID, params, callback);
				}
				
			});
		}
	}

	static public void applySDKMethodWithCallback(String sdkName, String params, int handle) {
		applySDKMethodWithCallback(sdkName, params, new MySDKCallback(handle));
	}
	
	static public void applySDKPay(String sdkName, String productID, String orderID, String params, int handle) {
		applySDKPay(sdkName, productID, orderID, params, new MySDKCallback(handle));
	}


}
