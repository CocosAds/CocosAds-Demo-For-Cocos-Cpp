#include "HelloWorldScene.h"
#include "BannerScene.h"
#include "InterstitialScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto labelItemBanner = MenuItemFont::create("Banner广告", [](Ref*){
        Director::getInstance()->replaceScene(Banner::createScene());
    });
    labelItemBanner->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - 50));
    
    auto labelItemInterstitial = MenuItemFont::create("插屏广告", [](Ref*){
        Director::getInstance()->replaceScene(Interstitial::createScene());
    });
    labelItemInterstitial->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - 100));
    
    auto menu = Menu::create(labelItemBanner, labelItemInterstitial, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    return true;
}
