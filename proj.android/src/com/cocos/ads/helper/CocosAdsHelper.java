package com.cocos.ads.helper;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.FrameLayout.LayoutParams;

import com.cocos.ads.ads.Banner;
import com.cocos.ads.exception.PBException;
import com.cocos.ads.listener.AdListener;
import com.cocos.ads.manager.CocosAdsManager;
import com.cocos.ads.manager.InterstitialManager;

public class CocosAdsHelper {

	private enum CocosAdsResultCode{
	    kAdsReceiveSuccess,
	    kAdsReceiveFailed,
	    kAdsPresentScreen,
	    kAdsDismissScreen
	}
	
	private static Cocos2dxActivity sCocos2dxActivity = null;
	private static Banner sBanner = null;

	public static native void bannerAdsResult(CocosAdsResultCode code, String result);
	public static native void interstitialAdsResult(CocosAdsResultCode code, String result);
	
	public static void init(String publisherID) {
		CocosAdsManager.init(publisherID);
		CocosAdsHelper.sCocos2dxActivity = (Cocos2dxActivity) Cocos2dxActivity.getContext();
	}

	public static void showBanner(final String placementID) {
		sCocos2dxActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if(sBanner == null){
					sBanner = new Banner(sCocos2dxActivity, placementID);
				}else{
					ViewGroup parent = (ViewGroup) sBanner.getParent();
					if(parent != null){
						parent.removeView(sBanner);
					}
				}

				FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
				params.gravity = Gravity.CENTER_HORIZONTAL | Gravity.TOP;
				sCocos2dxActivity.addContentView(sBanner, params);
				sBanner.loadAd();
				
				sBanner.setAdListener(new AdListener() {
					
					@Override
					public void onReceiveAd() {
						bannerAdsResult(CocosAdsResultCode.kAdsReceiveSuccess, "接收Banner广告成功");
					}

					@Override
					public void onFailedToReceiveAd(PBException ex) {
						String errMsg = ex.toString();
						bannerAdsResult(CocosAdsResultCode.kAdsReceiveFailed, errMsg);
					}
					
					@Override
					public void onPresentScreen() {
						bannerAdsResult(CocosAdsResultCode.kAdsPresentScreen, "显示Banner广告");
					}
					
					@Override
					public void onDismissScreen() {
						bannerAdsResult(CocosAdsResultCode.kAdsDismissScreen, "移除Banner广告");
					}
				});
			}
		});
	}

	public static void hideBanner() {
		sCocos2dxActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if(sBanner == null){
					return;
				}else{
					ViewGroup parent = (ViewGroup) sBanner.getParent();
					if(parent != null){
						parent.removeView(sBanner);
					}
					sBanner.destroy();
					sBanner = null;
				}
			}
		});
	}

	public static void showInterstitial(final String placementID) {
		sCocos2dxActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				InterstitialManager.setPlacementID(placementID);
				InterstitialManager.show(sCocos2dxActivity);
				InterstitialManager.setAdListener(new AdListener() {
					
					@Override
					public void onReceiveAd() {
						interstitialAdsResult(CocosAdsResultCode.kAdsReceiveSuccess, "接收插屏广告成功");
					}

					@Override
					public void onFailedToReceiveAd(PBException ex) {
						String errMsg = ex.toString();
						interstitialAdsResult(CocosAdsResultCode.kAdsReceiveFailed, errMsg);
					}
					
					@Override
					public void onPresentScreen() {
						interstitialAdsResult(CocosAdsResultCode.kAdsPresentScreen, "显示插屏广告");
					}
					
					@Override
					public void onDismissScreen() {
						interstitialAdsResult(CocosAdsResultCode.kAdsDismissScreen, "移除插屏广告");
					}
				});
			}
		});
	}
	
	public static void setInterstitialCloseMode(int mode) {
		InterstitialManager.setCloseMode(mode);
	}
	
	public static void setInterstitialDisplayTime(int seconds) {
		InterstitialManager.setDisplayTime(seconds);
	}

	public static void hideInterstitial() {
		sCocos2dxActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				InterstitialManager.destroy();
			}
		});
	}
}
