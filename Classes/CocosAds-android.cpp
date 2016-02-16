//
//  CocosAds-android.cpp
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
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "init", "(Ljava/lang/String;)V"))
    {
        jstring stringArg1 = t.env->NewStringUTF(publisherID);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
    }
}

#pragma mark - Banner

void CocosAds::showBanner(const char* placementID /*= ""*/)
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showBanner", "(Ljava/lang/String;)V"))
    {
        jstring stringArg1 = t.env->NewStringUTF(placementID);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
    }
}

void CocosAds::hideBanner()
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "hideBanner", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

#pragma mark - Interstitial

void CocosAds::showInterstitial(const char* placementID /*= ""*/)
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showInterstitial", "(Ljava/lang/String;)V"))
    {
        jstring stringArg1 = t.env->NewStringUTF(placementID);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
    }
}

void CocosAds::setInterstitialCloseMode(int closeMode)
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setInterstitialCloseMode", "(I)V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, closeMode);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CocosAds::setInterstitialDisplayTime(int seconds)
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setInterstitialDisplayTime", "(I)V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, seconds);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CocosAds::hideInterstitial()
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "hideInterstitial", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID