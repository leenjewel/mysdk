package com.leenjewel.mysdk.sdk;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.leenjewel.mysdk.callback.IMySDKCallback;
import com.leenjewel.mysdk.callback.MySDKCallback;
import com.leenjewel.mysdk.exception.MySDKDoNotImplementMethod;

import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.content.Intent;
import android.content.res.AssetManager;
import android.os.Bundle;

public class MySDK {
	
	final static public String MY_SDK_TAG = "MySDK";
	final static private String MY_SDK_CONFIG = "mysdk.conf";
	final static private String MYSDK_CONF_SDK_LIST = "sdk_list";
	final static private String MYSDK_CONF_SDK_CONFIG = "sdk_config";
	final static private String MYSDK_CONF_SDK_CLASS_PATH = "class_path";
	
	static private boolean _isDebugMode = false;
	static private HashMap<String, IMySDK> _sdkMap = new HashMap<String, IMySDK>();
	static private String[] _sdkNameList = null;
	static private Activity _activity = null;
	static private JSONObject _sdkConfig = null;
	
	static public Activity getActivity() {
		return _activity;
	}

	static public void setDebugMode(boolean isDebugMode) {
		_isDebugMode = isDebugMode;
	}
	
	static public void logWaring(String log) {
		android.util.Log.w(MY_SDK_TAG, log);
	}
	
	static public void logDebug(String log) {
		if (_isDebugMode) {
			android.util.Log.d(MY_SDK_TAG, log);
		}
	}
	
	static public void logError(String log) {
		android.util.Log.e(MY_SDK_TAG, log);
	}
	
	static public IMySDK getSDK(String sdkName) {
		IMySDK sdk = _sdkMap.get(sdkName);
		if (null == sdk) {
			String className = null;
			try {
				if (null != _sdkConfig && _sdkConfig.has(sdkName)) {
					JSONObject sdkConfig = _sdkConfig.getJSONObject(sdkName);
					if (sdkConfig.has(MYSDK_CONF_SDK_CLASS_PATH)) {
						className = sdkConfig.getString(MYSDK_CONF_SDK_CLASS_PATH);
					}
				}
			} catch (JSONException e) {
				e.printStackTrace();
			}
			if (null == className) {
				String sn = sdkName.toLowerCase();
				StringBuilder sb = new StringBuilder(); 
				sb.append(Character.toUpperCase(sn.charAt(0))); 
				sb.append(sn.substring(1)); 
				String classPrefix = sb.toString();
				className = MySDK.class.getPackage().getName()+"."+classPrefix+"MySDK";
			}
	        ClassLoader classLoader = MySDK.class.getClassLoader();
	        try {
				Class sdkClass = classLoader.loadClass(className);
				sdk = (IMySDK)sdkClass.newInstance();
				logDebug(className=" newInstance");
			} catch (ClassNotFoundException e) {
				// TODO Auto-generated catch block
				logDebug(className+" not found.");
				sdk = NullMySDK.getNullMySDK(sdkName);
			} catch (InstantiationException e) {
				// TODO Auto-generated catch block
				logDebug(className+" not found.");
				sdk = NullMySDK.getNullMySDK(sdkName);
			} catch (IllegalAccessException e) {
				// TODO Auto-generated catch block
				logDebug(className+" not found.");
				sdk = NullMySDK.getNullMySDK(sdkName);
			} finally {
				_sdkMap.put(sdkName, sdk);
			}
		}
		return sdk;
	}
	
	static private String[] getSDKNameList(Context context) {
		if (null == _sdkNameList) {
			AssetManager assetMgr = context.getAssets();
			BufferedReader reader = null;
			try {
				reader = new BufferedReader(new InputStreamReader(assetMgr.open(MY_SDK_CONFIG), "UTF-8"));
				String mysdkConfJson = "";
				String line = reader.readLine();
				while (line != null) {
					mysdkConfJson += line;
					line = reader.readLine();
				}
				if (null == mysdkConfJson || mysdkConfJson.length() == 0) {
					logWaring("MySDK conf is null.");
					return null;
				}
				JSONObject mysdkConf = new JSONObject(mysdkConfJson);
				if (mysdkConf.has(MYSDK_CONF_SDK_LIST)) {
					JSONArray sdkList = mysdkConf.getJSONArray(MYSDK_CONF_SDK_LIST);
					if (sdkList.length() > 0) {
						_sdkNameList = new String[sdkList.length()];
						for (int i = 0; i < sdkList.length(); i++) {
							_sdkNameList[i] = sdkList.getString(i);
						}
					}
				}
				if (mysdkConf.has(MYSDK_CONF_SDK_CONFIG)) {
					_sdkConfig = mysdkConf.getJSONObject(MYSDK_CONF_SDK_CONFIG);
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return null;
			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return null;
			} finally {
				if (reader != null) {
					try {
						reader.close();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		}
		return _sdkNameList;
	}
	
	static public boolean hasSDK(String sdkName) {
		if (null == sdkName || sdkName.length() == 0 || null == _sdkNameList) {
			return false;
		}
		for (String skn : _sdkNameList) {
			if (sdkName.equals(skn)) {
				return true;
			}
		}
		return false;
	}
	
	static public void onCreate(Application application) {
		System.loadLibrary("mysdk");
		String[] sdkNameList = getSDKNameList(application);
		if (null == sdkNameList || 0 == sdkNameList.length) {
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
		if (null == sdkNameList || 0 == sdkNameList.length) {
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
	
	static public int applySDKMethodAndReturnInt(String sdkName, String methodName, String params) throws MySDKDoNotImplementMethod {
		IMySDK sdk = getSDK(sdkName);
		return sdk.applySDKMethodAndReturnInt(methodName, params);
	}
	
	static public long applySDKMethodAndReturnLong(String sdkName, String methodName, String params) throws MySDKDoNotImplementMethod {
		IMySDK sdk = getSDK(sdkName);
		return sdk.applySDKMethodAndReturnLong(methodName, params);
	}
	
	static public float applySDKMethodAndReturnFloat(String sdkName, String methodName, String params) throws MySDKDoNotImplementMethod {
		IMySDK sdk = getSDK(sdkName);
		return sdk.applySDKMethodAndReturnFloat(methodName, params);
	}

	static public double applySDKMethodAndReturnDouble(String sdkName, String methodName, String params) throws MySDKDoNotImplementMethod {
		IMySDK sdk = getSDK(sdkName);
		return sdk.applySDKMethodAndReturnDouble(methodName, params);
	}

	static public boolean applySDKMethodAndReturnBoolean(String sdkName, String methodName, String params) throws MySDKDoNotImplementMethod {
		IMySDK sdk = getSDK(sdkName);
		return sdk.applySDKMethodAndReturnBoolean(methodName, params);
	}

	static public String applySDKMethodAndReturnString(String sdkName, String methodName, String params) throws MySDKDoNotImplementMethod {
		IMySDK sdk = getSDK(sdkName);
		return sdk.applySDKMethodAndReturnString(methodName, params);
	}

	static public void applySDKMethodWithCallback(final String sdkName, final String methodName, final String params, final IMySDKCallback callback) {
		final IMySDK sdk = getSDK(sdkName);
		Activity activity = getActivity();
		if (null == activity) {
			sdk.applySDKMethodWithCallback(methodName, params, callback);
		} else {
			activity.runOnUiThread(new Runnable(){

				@Override
				public void run() {
					// TODO Auto-generated method stub
					sdk.applySDKMethodWithCallback(methodName, params, callback);
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

	static public void applySDKMethodWithCallback(String sdkName, String methodName, String params, int handle) {
		applySDKMethodWithCallback(sdkName, methodName, params, new MySDKCallback(handle));
	}
	
	static public void applySDKPay(String sdkName, String productID, String orderID, String params, int handle) {
		applySDKPay(sdkName, productID, orderID, params, new MySDKCallback(handle));
	}


}
