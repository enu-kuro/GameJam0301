//
//  GameScene.cpp
//  GameJame
//
//  Created by Kurose Nobuhito on 2014/03/01.
//
//

#include "GameScene.h"

#define WINDOW_SIZE CCDirector::sharedDirector()->getWinSize()

#define MOVE_SPEED 15
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
    mainChara->setPosition(ccp(WINDOW_SIZE.width/2,200));
    addChild(mainChara);
    tickCount=0;
    targetMovePointX=WINDOW_SIZE.width/2;
    //game start
    scheduleUpdate();
    
    return true;
}


void GameScene::update(float dt) {
    
    tickCount++;
    
    if (abs(mainChara->getPosition().x-targetMovePointX)<10) {
        mainChara->setPosition(ccp(targetMovePointX,mainChara->getPosition().y));
        return;
    }

    float moveValue = MOVE_SPEED;
    if (mainChara->getPosition().x>targetMovePointX) {
        moveValue=moveValue*-1;
    }
    
    mainChara->setPosition(ccpAdd(mainChara->getPosition(),ccp(moveValue,0)));
    
//    if (tickCount%6==0) {
//        this->updateTimer();
//    }
//    
//    if (tickCount%400 ==0) {
//        this->unschedule(schedule_selector(GameScene::updateTimer));
//        
//        GameScene::handleGameOver();
//        
//    }
    
}

bool GameScene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
    targetMovePointX = this->convertTouchToNodeSpace(pTouch).x;
    
    CCPoint touchPoint = this->convertTouchToNodeSpace(pTouch);
    
    //charaMove(touchPoint);
    return true;
}

void GameScene::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{

    
    CCPoint currentPosition = this->convertTouchToNodeSpace(pTouch);

    if (abs(targetMovePointX-currentPosition.x)>20){
        targetMovePointX=currentPosition.x;
    }
    
}

void GameScene::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
    
}


//void GameScene::charaMove(CCPoint point){
//
//    CCMoveTo *move = CCMoveTo::create(1, ccp(point.x, mainChara->getPosition().y));
//    mainChara->runAction(move);
//    
//}

