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

#pragma mark - CocosAds

CocosAds* CocosAds::_instance = nullptr;

Banner* _banner = nullptr;

BannerDelegateImpl* _bannerDelegateImpl = nullptr;

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
    
    [_banner setDelegate: _bannerDelegateImpl];
    
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


#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS