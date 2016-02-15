//
//  CocosAds.h
//  CocosAds
//
//  Created by Jacky on 16/2/15.
//
//

#ifndef CocosAds_h
#define CocosAds_h

class CocosAds
{
public:
    
    //插屏广告关闭模式
    const static int CLOSE_MODE_CLOSE = 1;
    const static int CLOSE_MODE_COUNTDOWN = 2;
    const static int CLOSE_MODE_COUNTDOWN_WITH_CLOSE = 3;
    
    //获取CocosAds单例
    static CocosAds* getInstance();
    
    //初始化 CocosAds SDK
    void init(const char* publisherID);
    
    //Banner 广告
    void showBanner(const char* placementID = "");
    
    void hideBanner();
    
    
    //插屏广告
    void setInterstitialCloseMode(int closeMode);
    
    void setInterstitialDisplayTime(int seconds);
    
    void showInterstitial(const char* placementID = "");
    
    void hideInterstitial();
        
private:
    
    CocosAds();
    
    static CocosAds* _instance;
};


#endif /* CocosAds_h */
