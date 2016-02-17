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
#include "CocosAdsManager.h"
#include "Banner.h"
#include "InterstitialManager.h"

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
    
    _bannerOnReceiveAdSuccess = nullptr;
    _bannerReceiveAdFailed = nullptr;
    _bannerOnPresentScreen = nullptr;
    _bannerOnDismissScreen = nullptr;
}

void CocosAds::setBannerOnReceiveAdSuccess(const std::function<void()> &callback)
{
    _bannerOnReceiveAdSuccess = callback;
}

void CocosAds::setBannerOnReceiveAdFailed(const std::function<void(const std::string& errMsg)> &callback)
{
    _bannerReceiveAdFailed = callback;
}

void CocosAds::setBannerOnPresentScreen(const std::function<void()> &callback)
{
    _bannerOnPresentScreen = callback;
}

void CocosAds::setBannerOnDismissScreen(const std::function<void()> &callback)
{
    _bannerOnDismissScreen = callback;
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
    
    _interstitialOnReceiveAdSuccess = nullptr;
    _interstitialReceiveAdFailed = nullptr;
    _interstitialOnPresentScreen = nullptr;
    _interstitialOnDismissScreen = nullptr;
}

void CocosAds::setInterstitialOnReceiveAdSuccess(const std::function<void()> &callback)
{
    _interstitialOnReceiveAdSuccess = callback;
}

void CocosAds::setInterstitialOnReceiveAdFailed(const std::function<void(const std::string& errMsg)> &callback)
{
    _interstitialReceiveAdFailed = callback;
}

void CocosAds::setInterstitialOnPresentScreen(const std::function<void()> &callback)
{
    _interstitialOnPresentScreen = callback;
}

void CocosAds::setInterstitialOnDismissScreen(const std::function<void()> &callback)
{
    _interstitialOnDismissScreen = callback;
}

#pragma mark - CocosAdsImpl

CocosAds* CocosAdsImpl::_cocosads = nullptr;

CocosAdsImpl::CocosAdsImpl(CocosAds* cocosads)
{
    _cocosads = cocosads;
}

void CocosAdsImpl::bannerReceiveAdSuccess()
{
    if (_cocosads->_bannerOnReceiveAdSuccess)
    {
        _cocosads->_bannerOnReceiveAdSuccess();
    }
}

void CocosAdsImpl::bannerReceiveAdFailed(const std::string errMsg)
{
    if(_cocosads->_bannerReceiveAdFailed)
    {
        _cocosads->_bannerReceiveAdFailed(errMsg);
    }
}
void CocosAdsImpl::bannerPresentScreen()
{
    if(_cocosads->_bannerOnPresentScreen)
    {
        _cocosads->_bannerOnPresentScreen();
    }
}

void CocosAdsImpl::bannerDismissScreen()
{
    if(_cocosads->_bannerOnDismissScreen)
    {
        _cocosads->_bannerOnDismissScreen();
    }
}

void CocosAdsImpl::interstitialReceiveAdSuccess()
{
    if (_cocosads->_interstitialOnReceiveAdSuccess)
    {
        _cocosads->_interstitialOnReceiveAdSuccess();
    }
}

void CocosAdsImpl::interstitialReceiveAdFailed(const std::string errMsg)
{
    if(_cocosads->_interstitialReceiveAdFailed)
    {
        _cocosads->_interstitialReceiveAdFailed(errMsg);
    }
}
void CocosAdsImpl::interstitialPresentScreen()
{
    if(_cocosads->_interstitialOnPresentScreen)
    {
        _cocosads->_interstitialOnPresentScreen();
    }
}

void CocosAdsImpl::interstitialDismissScreen()
{
    if(_cocosads->_interstitialOnDismissScreen)
    {
        _cocosads->_interstitialOnDismissScreen();
    }
}


#pragma mark - BannerDelegate

@implementation BannerDelegateImpl

// Banner广告发出请求
- (void)csBannerViewRequestAD:(Banner *)csBannerView
{
    CocosAdsImpl::bannerReceiveAdSuccess();
}

// Banner广告展现失败
- (void)csBannerView:(Banner *)csBannerView
         showAdError:(RequestError *)requestError
{
    CocosAdsImpl::bannerReceiveAdFailed([requestError.localizedDescription UTF8String]);
}

// 将要展示Banner广告
- (void)csBannerViewWillPresentScreen:(Banner *)csBannerView
{
    CocosAdsImpl::bannerPresentScreen();
}

// 移除Banner广告
- (void)csBannerViewDidDismissScreen:(Banner *)csBannerView
{
    CocosAdsImpl::bannerDismissScreen();
}

@end

#pragma mark - InterstitialDelegate

@implementation InterstitialManagerDelegateImpl

// 弹出广告加载完成
- (void)csInterstitialDidLoadAd:(InterstitialManager *)csInterstitial
{
    CocosAdsImpl::interstitialReceiveAdSuccess();
}

// 弹出广告加载错误
- (void)csInterstitial:(InterstitialManager *)csInterstitial
loadAdFailureWithError:(RequestError *)requestError
{
    CocosAdsImpl::interstitialReceiveAdFailed([requestError.localizedDescription UTF8String]);
}

// 弹出广告打开完成
- (void)csInterstitialDidPresentScreen:(InterstitialManager *)csInterstitial
{
    CocosAdsImpl::interstitialPresentScreen();
}

// 弹出广告关闭完成
- (void)csInterstitialDidDismissScreen:(InterstitialManager *)csInterstitial
{
    CocosAdsImpl::interstitialDismissScreen();
}

@end


#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS