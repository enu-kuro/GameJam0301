//
//  GameScene.h
//  GameJame
//
//  Created by Kurose Nobuhito on 2014/03/01.
//
//

#ifndef __GameJame__GameScene__
#define __GameJame__GameScene__

#include <iostream>
#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GameScene : public cocos2d::CCLayer
{
private:
    

public:

    virtual bool init();

    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(GameScene);
    
    
    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
    
    
    CCSprite *mainChara;
};

#endif /* defined(__GameJame__GameScene__) */
