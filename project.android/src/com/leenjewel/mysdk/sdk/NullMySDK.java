package com.leenjewel.mysdk.sdk;

import android.app.Activity;
import android.app.Application;
import android.content.Intent;
import android.os.Bundle;

public class NullMySDK implements IMySDK {
	
	static private NullMySDK _instance = null;
	
	private NullMySDK() {
		
	}
	
	static public NullMySDK getNullMySDK() {
		if (null == _instance) {
			_instance = new NullMySDK();
		}
		return _instance;
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
	public void activityOnActivityResult(Activity activity, int requestCode,
			int resultCode, Intent data) {
		// TODO Auto-generated method stub
		
	}
}
