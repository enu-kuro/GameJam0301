//
//  GameScene.cpp
//  GameJame
//
//  Created by Kurose Nobuhito on 2014/03/01.
//
//

#include "GameScene.h"

#define WINDOW_SIZE CCDirector::sharedDirector()->getWinSize()

CCScene* GameScene::scene() {
    CCScene *scene = CCScene::create();
    GameScene *layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init() {
    if (!CCLayer::init()) {
        return false;
    }
    
    setTouchMode(kCCTouchesOneByOne);
    setTouchEnabled(true);
    
    mainChara = CCSprite::create("Icon-114.png");
    mainChara->setPosition(ccp(WINDOW_SIZE.width/2,100));
    addChild(mainChara);
    
    return true;
}


bool GameScene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
    
    CCPoint touchPoint = this->convertTouchToNodeSpace(pTouch);
    
    charaMove(touchPoint);
    return true;
}

void GameScene::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{}

void GameScene::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
    
}


void GameScene::charaMove(CCPoint point){

    CCMoveTo *move = CCMoveTo::create(1, point);
    mainChara->runAction(move);
    
}

