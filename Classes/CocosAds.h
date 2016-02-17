//
//  CocosAds.h
//  CocosAds
//
//  Created by Jacky on 16/2/15.
//
//

#ifndef CocosAds_h
#define CocosAds_h

#include <functional>

class CocosAdsImpl;

class CocosAds
{
public:
    
    //插屏广告关闭模式
    const static int CLOSE_MODE_CLOSE = 0;
    const static int CLOSE_MODE_COUNTDOWN = 1;
    const static int CLOSE_MODE_COUNTDOWN_WITH_CLOSE = 2;
    
    //获取CocosAds单例
    static CocosAds* getInstance();
    
    //初始化 CocosAds SDK
    void init(const char* publisherID);
    
    //Banner 广告
    void showBanner(const char* placementID = "");
    
    void hideBanner();
    
    void setBannerOnReceiveAdSuccess(const std::function<void()> &callback);
    void setBannerOnReceiveAdFailed(const std::function<void(const std::string& errMsg)> &callback);
    void setBannerOnPresentScreen(const std::function<void()> &callback);
    void setBannerOnDismissScreen(const std::function<void()> &callback);
    
    //插屏广告
    void setInterstitialCloseMode(int closeMode);
    
    void setInterstitialDisplayTime(int seconds);
    
    void showInterstitial(const char* placementID = "");
    
    void hideInterstitial();
    
    void setInterstitialOnReceiveAdSuccess(const std::function<void()> &callback);
    void setInterstitialOnReceiveAdFailed(const std::function<void(const std::string& errMsg)> &callback);
    void setInterstitialOnPresentScreen(const std::function<void()> &callback);
    void setInterstitialOnDismissScreen(const std::function<void()> &callback);
    
private:
    
    CocosAds();
    
    static CocosAds* _instance;
    
    CocosAdsImpl* _impl;
    
    //Banner callback
    std::function<void()> _bannerOnReceiveAdSuccess;
    std::function<void(const std::string& errMsg)> _bannerReceiveAdFailed;
    std::function<void()> _bannerOnPresentScreen;
    std::function<void()> _bannerOnDismissScreen;
    
    //Interstitial callback
    std::function<void()> _interstitialOnReceiveAdSuccess;
    std::function<void(const std::string& errMsg)> _interstitialReceiveAdFailed;
    std::function<void()> _interstitialOnPresentScreen;
    std::function<void()> _interstitialOnDismissScreen;
    
    friend class CocosAdsImpl;
};

class CocosAdsImpl
{
public:
    CocosAdsImpl(CocosAds* cocosads);
    
    static void bannerReceiveAdSuccess();
    static void bannerReceiveAdFailed(const std::string errMsg);
    static void bannerPresentScreen();
    static void bannerDismissScreen();
    
    static void interstitialReceiveAdSuccess();
    static void interstitialReceiveAdFailed(const std::string errMsg);
    static void interstitialPresentScreen();
    static void interstitialDismissScreen();
    
private:
    static CocosAds* _cocosads;
};


#endif /* CocosAds_h */
