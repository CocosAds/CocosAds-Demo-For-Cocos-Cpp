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
    
    
    //展示广告
    CocosAds::getInstance()->setInterstitialCloseMode(CocosAds::CLOSE_MODE_COUNTDOWN_WITH_CLOSE);
    CocosAds::getInstance()->setInterstitialDisplayTime(7);
    CocosAds::getInstance()->showInterstitial();
    
    return true;
}