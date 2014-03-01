//
//  GameScene.cpp
//  GameJame
//
//  Created by Kurose Nobuhito on 2014/03/01.
//
//

#include "GameScene.h"

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
    
    return true;
}


bool GameScene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
    
    CCPoint touchPoint = this->convertTouchToNodeSpace(pTouch);
    return true;
}

void GameScene::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{}

void GameScene::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
    
}