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

CocosAds* CocosAds::_instance = nullptr;

Banner* _banner = nullptr;

CocosAds::CocosAds()
{
}

CocosAds* CocosAds::getInstance()
{
    if(_instance == nullptr)
    {
        _instance = new CocosAds();
    }
    return _instance;
}

#pragma mark - CocosAds

void CocosAds::init(const char* publisherID)
{
    [CocosAdsManager init: [[NSString alloc] initWithUTF8String: publisherID]];
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
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS