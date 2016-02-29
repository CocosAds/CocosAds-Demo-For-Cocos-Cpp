rm -rf sdk/Classes
mkdir sdk/Classes
cp demo/Classes/CocosAds.h demo/Classes/CocosAds-android.cpp demo/Classes/CocosAds-ios.mm sdk/Classes/

rm -rf sdk/com
mkdir sdk/com
mkdir sdk/com/cocos
mkdir sdk/com/cocos/ads
mkdir sdk/com/cocos/ads/helper
cp demo/proj.android/src/com/cocos/ads/helper/CocosAdsHelper.java sdk/com/cocos/ads/helper/
