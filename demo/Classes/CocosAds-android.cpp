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

#pragma mark - CocosAds

CocosAds* CocosAds::_instance = nullptr;

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

void CocosAds::addInterstitialAdListener(const std::function<void (CocosAdsResultCode, std::string)> &callback)
{
    _interstitialAdsResultCallback = callback;
}

void CocosAds::removeInterstitialAdListener()
{
    _interstitialAdsResultCallback = nullptr;
}

#pragma mark - JNI

extern "C" {
    JNIEXPORT void JNICALL Java_com_cocos_ads_helper_CocosAdsHelper_bannerAdsResult(JNIEnv *env, jclass, jobject jcode, jstring jresult) {
        
        //获取enum:code
        jclass enumclass= env->GetObjectClass(jcode);
        jmethodID getVal = env->GetMethodID(enumclass, "name", "()Ljava/lang/String;");
        jstring value = (jstring)env->CallObjectMethod(jcode, getVal);
        const char * valueNative = env->GetStringUTFChars(value, 0);
        CocosAdsResultCode code;
        if (strcmp(valueNative, "kAdsReceiveSuccess") == 0) {
            code = kAdsReceiveSuccess;
        }else if( strcmp(valueNative, "kAdsReceiveFailed") == 0) {
            code = kAdsReceiveFailed;
        }else if(strcmp(valueNative, "kAdsPresentScreen") == 0) {
            code = kAdsPresentScreen;
        }else if(strcmp(valueNative, "kAdsDismissScreen") == 0) {
            code = kAdsDismissScreen;
        }
        
        //获取std::string result
        auto charResult = env->GetStringUTFChars(jresult, nullptr);
        std::string result = charResult;
        env->ReleaseStringUTFChars(jresult, charResult);
        
        return CocosAdsImpl::bannerAdsResult(code, result);
    }
    
    JNIEXPORT void JNICALL Java_com_cocos_ads_helper_CocosAdsHelper_interstitialAdsResult(JNIEnv *env, jclass, jobject jcode, jstring jresult) {

        //获取enum:code
        jclass enumclass= env->GetObjectClass(jcode);
        jmethodID getVal = env->GetMethodID(enumclass, "name", "()Ljava/lang/String;");
        jstring value = (jstring)env->CallObjectMethod(jcode, getVal);
        const char * valueNative = env->GetStringUTFChars(value, 0);
        CocosAdsResultCode code;
        if (strcmp(valueNative, "kAdsReceiveSuccess") == 0) {
            code = kAdsReceiveSuccess;
        }else if( strcmp(valueNative, "kAdsReceiveFailed") == 0) {
            code = kAdsReceiveFailed;
        }else if(strcmp(valueNative, "kAdsPresentScreen") == 0) {
            code = kAdsPresentScreen;
        }else if(strcmp(valueNative, "kAdsDismissScreen") == 0) {
            code = kAdsDismissScreen;
        }
        
        //获取std::string result
        auto charResult = env->GetStringUTFChars(jresult, nullptr);
        std::string result = charResult;
        env->ReleaseStringUTFChars(jresult, charResult);
        
        return CocosAdsImpl::interstitialAdsResult(code, result);
    }
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

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID