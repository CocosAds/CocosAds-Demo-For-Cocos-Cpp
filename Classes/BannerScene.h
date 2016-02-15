//
//  Banner.h
//  CocosDemo
//
//  Created by Jacky on 16/2/15.
//
//

#ifndef Banner_h
#define Banner_h

#include "cocos2d.h"

class Banner : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Banner);
};

#endif /* Banner_h */
