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

	private static Cocos2dxActivity sCocos2dxActivity = null;
	private static Banner sBanner = null;

	public static native void bannerReceiveAdSuccess();
	public static native void bannerReceiveAdFailed(String errMsg);
	public static native void bannerPresentScreen();
	public static native void bannerDismissScreen();
	
	public static native void interstitialReceiveAdSuccess();
	public static native void interstitialReceiveAdFailed(String errMsg);
	public static native void interstitialPresentScreen();
	public static native void interstitialDismissScreen();
	
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
						bannerReceiveAdSuccess();
					}

					@Override
					public void onFailedToReceiveAd(PBException ex) {
						String errMsg = ex.toString();
						bannerReceiveAdFailed(errMsg);
					}
					
					@Override
					public void onPresentScreen() {
						bannerPresentScreen();
					}
					
					@Override
					public void onDismissScreen() {
						bannerDismissScreen();
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
						interstitialReceiveAdSuccess();
					}

					@Override
					public void onFailedToReceiveAd(PBException ex) {
						String errMsg = ex.toString();
						interstitialReceiveAdFailed(errMsg);
					}
					
					@Override
					public void onPresentScreen() {
						interstitialPresentScreen();
					}
					
					@Override
					public void onDismissScreen() {
						interstitialDismissScreen();
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
