//
//  CocosAds-ios.mm
//  CocosAds
//
//  Created by Jacky on 16/2/16.
//
//

#include "CocosAds.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import <Foundation/Foundation.h>
#include <string>

#include "CocosAdsManager.h"
#include "Banner.h"
#include "InterstitialManager.h"

#include "cocos2d.h"
#include "platform/ios/CCEAGLView-ios.h"

using namespace cocos2d;
using namespace std;

@interface BannerDelegateImpl: NSObject<BannerDelegate>
@end

@interface InterstitialManagerDelegateImpl : NSObject<InterstitialManagerDelegate>
@end

#pragma mark - CocosAds

CocosAds* CocosAds::_instance = nullptr;

Banner* _banner = nullptr;

BannerDelegateImpl* _bannerDelegateImpl = nullptr;

InterstitialManagerDelegateImpl* _interstitialManagerDelegateImpl = nullptr;

CocosAds::CocosAds()
{
    _impl = new CocosAdsImpl(this);
}

CocosAds* CocosAds::getInstance()
{
    if(_instance == nullptr)
    {
        _instance = new CocosAds();
    }
    return _instance;
}

void CocosAds::init(const char* publisherID)
{
    [CocosAdsManager init: [[NSString alloc] initWithUTF8String: publisherID]];
    _bannerDelegateImpl = [[BannerDelegateImpl alloc] init];
    _interstitialManagerDelegateImpl = [[InterstitialManagerDelegateImpl alloc] init];
}

#pragma mark - Banner

void CocosAds::showBanner(const char* placementID /*= ""*/)
{
    if(!_banner)
    {
        _banner = [[Banner alloc] init];
    }
    else
    {
        UIView* parent = [_banner superview];
        if(parent)
        {
            [_banner removeFromSuperview];
        }
    }
    
    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    auto eaglview = (CCEAGLView *) view->getEAGLView();
    [eaglview addSubview: _banner];
    _banner.center = CGPointMake(eaglview.bounds.size.width/2, _banner.bounds.size.height/2);
    
    [_banner loadAd];
    
    if(_bannerDelegateImpl)
    {
        [_banner setDelegate: _bannerDelegateImpl];
    }
    
    [_banner release];
}

void CocosAds::hideBanner()
{
    if(_banner)
    {
        UIView* parent = [_banner superview];
        if(parent)
        {
            [_banner removeFromSuperview];
        }
        [_banner destroy];
        _banner = nullptr;
    }
}

void CocosAds::addBannerAdListener(const std::function<void (CocosAdsResultCode, std::string)> &callback)
{
    _bannerAdsResultCallback = callback;
}

void CocosAds::removeBannerAdListener()
{
    _bannerAdsResultCallback = nullptr;
}

#pragma mark - Interstitial

void CocosAds::showInterstitial(const char* placementID /*= ""*/)
{
    [InterstitialManager setPlacementID:[[NSString alloc] initWithUTF8String: placementID]];
    if(_interstitialManagerDelegateImpl)
    {
        [InterstitialManager setDelegate: _interstitialManagerDelegateImpl];
    }
    [InterstitialManager show];
}

void CocosAds::setInterstitialCloseMode(int closeMode)
{
    [InterstitialManager setCloseMode: closeMode];
}

void CocosAds::setInterstitialDisplayTime(int seconds)
{
    [InterstitialManager setDisplayTime: seconds];
}

void CocosAds::hideInterstitial()
{
    [InterstitialManager destroy];    
}

void CocosAds::addInterstitialAdListener(const std::function<void (CocosAdsResultCode, std::string)> &callback)
{
    _interstitialAdsResultCallback = callback;
}

void CocosAds::removeInterstitialAdListener()
{
    _interstitialAdsResultCallback = nullptr;
}

#pragma mark - CocosAdsImpl

CocosAds* CocosAdsImpl::_cocosads = nullptr;

CocosAdsImpl::CocosAdsImpl(CocosAds* cocosads)
{
    _cocosads = cocosads;
}

void CocosAdsImpl::bannerAdsResult(CocosAdsResultCode code, std::string result)
{
    if(_cocosads->_bannerAdsResultCallback)
    {
        _cocosads->_bannerAdsResultCallback(code, result);
    }
}

void CocosAdsImpl::interstitialAdsResult(CocosAdsResultCode code, std::string result)
{
    if (_cocosads->_interstitialAdsResultCallback)
    {
        _cocosads->_interstitialAdsResultCallback(code, result);
        if (code == kAdsDismissScreen)
        {
            _cocosads->hideInterstitial();
        }
    }
}


#pragma mark - BannerDelegate

@implementation BannerDelegateImpl

- (void)csBannerViewWillPresentScreen:(Banner *)csBannerView
{
    CocosAdsImpl::bannerAdsResult(kAdsReceiveSuccess, "接收Banner广告成功");
    CocosAdsImpl::bannerAdsResult(kAdsPresentScreen, "显示Banner广告");
}

- (void)csBannerView:(Banner *)csBannerView
         showAdError:(RequestError *)requestError
{
    CocosAdsImpl::bannerAdsResult(kAdsReceiveFailed, [requestError.localizedDescription UTF8String]);
}

- (void)csBannerViewDidDismissScreen:(Banner *)csBannerView
{
    CocosAdsImpl::bannerAdsResult(kAdsDismissScreen, "移除Banner广告");
}

@end

#pragma mark - InterstitialDelegate

@implementation InterstitialManagerDelegateImpl

- (void)csInterstitialDidLoadAd:(InterstitialManager *)csInterstitial
{
    CocosAdsImpl::interstitialAdsResult(kAdsReceiveSuccess, "接收插屏广告成功");
}

- (void)csInterstitial:(InterstitialManager *)csInterstitial
loadAdFailureWithError:(RequestError *)requestError
{
    CocosAdsImpl::interstitialAdsResult(kAdsReceiveFailed, [requestError.localizedDescription UTF8String]);
}

- (void)csInterstitialDidPresentScreen:(InterstitialManager *)csInterstitial
{
    CocosAdsImpl::interstitialAdsResult(kAdsPresentScreen, "显示插屏广告");
}

- (void)csInterstitialDidDismissScreen:(InterstitialManager *)csInterstitial
{
    CocosAdsImpl::interstitialAdsResult(kAdsDismissScreen, "移除插屏广告");
}

@end


#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS