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

enum CocosAdsResultCode{
    kAdsReceiveSuccess,
    kAdsReceiveFailed,
    kAdsPresentScreen,
    kAdsDismissScreen
};

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
    
    void addBannerAdListener(const std::function<void(CocosAdsResultCode code, std::string result)> &callback);

    void removeBannerAdListener();
    
    //插屏广告
    void setInterstitialCloseMode(int closeMode);
    
    void setInterstitialDisplayTime(int seconds);
    
    void showInterstitial(const char* placementID = "");
    
    void hideInterstitial();
    
    void addInterstitialAdListener(const std::function<void(CocosAdsResultCode code, std::string result)> &callback);
    
    void removeInterstitialAdListener();
    
private:
    
    CocosAds();
    
    static CocosAds* _instance;
    
    CocosAdsImpl* _impl;
    
    //Banner callback
    std::function<void(CocosAdsResultCode code, std::string result)> _bannerAdsResultCallback;
    
    //Interstitial callback
    std::function<void(CocosAdsResultCode code, std::string result)> _interstitialAdsResultCallback;
    
    friend class CocosAdsImpl;
};

class CocosAdsImpl
{
public:
    CocosAdsImpl(CocosAds* cocosads);
    
    static void bannerAdsResult(CocosAdsResultCode code, std::string result);
    static void interstitialAdsResult(CocosAdsResultCode code, std::string result);
    
private:
    static CocosAds* _cocosads;
};


#endif /* CocosAds_h */
