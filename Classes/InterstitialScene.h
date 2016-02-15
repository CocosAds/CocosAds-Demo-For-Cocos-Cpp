//
//  InterstitialScene.h
//  CocosDemo
//
//  Created by Jacky on 16/2/15.
//
//

#ifndef InterstitialScene_h
#define InterstitialScene_h

#include "cocos2d.h"

class Interstitial : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Interstitial);
};

#endif /* InterstitialScene_h */
