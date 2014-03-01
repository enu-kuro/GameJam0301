//
//  TitleScene.cpp
//  GameJame
//
//  Created by Kurose Nobuhito on 2014/03/01.
//
//

#include "TitleScene.h"


//
//  TitleScene.cpp
//
//
//  Created by Kurose Nobuhito on 2014/01/12.
//
//
#include "TitleScene.h"
#include "GameScene.h"


CCScene* TitleScene::scene() {
    CCScene *scene = CCScene::create();
    TitleScene *layer = TitleScene::create();
    scene->addChild(layer);
    return scene;
}

bool TitleScene::init() {
    if (!CCLayer::init()) {
        return false;
    }
	
	CCSize screenSize = CCEGLView::sharedOpenGLView()->getDesignResolutionSize();

    CCSprite* splash = CCSprite::create("titleSceneimg.png");
    splash->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));

    this->addChild(splash, 1);
    
    CCFiniteTimeAction *seq1 = CCSequence::create(CCDelayTime::create(0.6),
                                                  CCCallFunc::create(this,
                                                                     callfunc_selector(TitleScene::finishTitleScene)), NULL);
    CCLOG("titlescene");
    this->runAction(seq1);
    
    return true;
}

void TitleScene::finishTitleScene(){
    
    CCScene *scene = GameScene::scene();
    
    CCTransitionCrossFade *crossFade = CCTransitionCrossFade::create(0.2f, scene);
    CCDirector::sharedDirector()->replaceScene(crossFade);
}