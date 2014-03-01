//
//  TitleScene.h
//  GameJame
//
//  Created by Kurose Nobuhito on 2014/03/01.
//
//

#ifndef __GameJame__TitleScene__
#define __GameJame__TitleScene__


#include <iostream>
#include "cocos2d.h"

class TitleScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    void finishTitleScene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(TitleScene);
	
	    //  マルチタッチ時のタッチ開始コールバック
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

private:
	void	onStartBtn();
};
#endif /* defined(__GameJame__TitleScene__) */
