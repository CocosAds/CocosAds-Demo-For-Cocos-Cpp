//
//  CocosAds.cpp
//  CocosAds
//
//  Created by Jacky on 16/2/15.
//
//

#include "CocosAds.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <cocos2d.h>
#define CLASS_NAME "com/cocos/ads/helper/CocosAdsHelper"
#endif

using namespace cocos2d;
using namespace std;

CocosAds* CocosAds::_instance = nullptr;

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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "init", "(Ljava/lang/String;)V"))
    {
        jstring stringArg1 = t.env->NewStringUTF(publisherID);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
    }
#endif
}

#pragma mark - Banner

void CocosAds::showBanner(const char* placementID /*= ""*/)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showBanner", "(Ljava/lang/String;)V"))
    {
        jstring stringArg1 = t.env->NewStringUTF(placementID);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
    }
#endif
}

void CocosAds::hideBanner()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "hideBanner", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}

#pragma mark - Interstitial

void CocosAds::showInterstitial(const char* placementID /*= ""*/)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showInterstitial", "(Ljava/lang/String;)V"))
    {
        jstring stringArg1 = t.env->NewStringUTF(placementID);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
    }
#endif
}

void CocosAds::setInterstitialCloseMode(int closeMode)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setInterstitialCloseMode", "(I)V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, closeMode);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}

void CocosAds::setInterstitialDisplayTime(int seconds)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setInterstitialDisplayTime", "(I)V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, seconds);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}

void CocosAds::hideInterstitial()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "hideInterstitial", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}