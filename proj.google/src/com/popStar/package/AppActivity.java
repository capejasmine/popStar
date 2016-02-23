/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.popStar.package;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.common.android.IapResult;
import com.common.android.OnSetupListener;
import com.common.android.PlatformCode;
import com.common.android.jni.MoreGamesActivityForJNI;
import com.common.android.utils.Utils;
import com.diwublog.AnalyticX.AnalyticXBridge;

import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.widget.FrameLayout.LayoutParams;

public class AppActivity extends Cocos2dxActivity {

@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

/*====================Google IAP setting begin====================*/
//Google版没有用到IAP就删除以下代码
//		if (getPlatformCode() == PlatformCode.GOOGLEPLAY) {
//			setPublicKey("Your APP public key");
//		}
//
//		setSetupBillingListener(new OnSetupListener() {
//
//			@Override
//			public void onIabSetupFinished(IapResult result) {
//
//				if (result.isSuccess()) {
//					if (getDebugMode())
//						Log.i("", "=======Billing support======");
//				} else {
//					if (getDebugMode())
//						Log.i("", "=======Billing unsupported======");
//				}
//			}
//		});
//
//		onStartSetupBilling();
/*====================Google IAP setting end====================*/

        //init JNI enviroment
		setupNativeEnvironment();

/*==============最新广告加初始化方式，根据自己用到的广告选择加载。==============*/
//		BannerAdsJni.getInstance(this);
//		InterstitialAdsJni.getInstance(this);
//		CrosspromoAdsJni.getInstance(this);
//		RewardedAdsJni.getInstance(this);
//		RectAdsJni.getInstance(this);
		
		//set more game layout id
		MoreGamesActivityForJNI.ACTIVITY_LAYOUT_ID = R.layout.activity_more_games;
		MoreGamesActivityForJNI.WEBVIEW_ID = R.id.more_game_view;
		MoreGamesActivityForJNI.TITLE_PROGRESS_ID = R.id.title_progress;
	}

	@Override
	public int getPlatformCode() {
		return PlatformCode.GOOGLEPLAY;
	}
	

	@Override
	public boolean getDebugMode() {
		return false;
	}

	@Override
	public boolean enableEvent() {
		return !getDebugMode();
	}
}
