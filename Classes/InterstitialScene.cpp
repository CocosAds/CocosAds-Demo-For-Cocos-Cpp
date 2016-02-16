//
//  InterstitialScene.cpp
//  CocosDemo
//
//  Created by Jacky on 16/2/15.
//
//

#include "InterstitialScene.h"
#include "CocosAds.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* Interstitial::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Interstitial::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool Interstitial::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto labelBack = MenuItemFont::create("返回", [](Ref*){
        //销毁广告
        CocosAds::getInstance()->hideInterstitial();
        
        Director::getInstance()->replaceScene(HelloWorld::createScene());
        
    });
    labelBack->setPosition(Vec2(origin.x + labelBack->getContentSize().width/2, origin.y + visibleSize.height - labelBack->getContentSize().height/2));
    
    auto menu = Menu::create(labelBack, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

    
    const char* placementID = "";
    //展示广告
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    placementID = "855310162o2l2xm";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    placementID = "855595180o2lox4";
#endif
    CocosAds::getInstance()->setInterstitialCloseMode(CocosAds::CLOSE_MODE_COUNTDOWN_WITH_CLOSE);
    CocosAds::getInstance()->setInterstitialDisplayTime(7);
    CocosAds::getInstance()->showInterstitial(placementID);
    
    return true;
}