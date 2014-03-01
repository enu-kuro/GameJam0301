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

GameScene::~GameScene()
{
    //CC_SAFE_RELEASE(resultLayer);
 
    CC_SAFE_DELETE_ARRAY(pantsArray);
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
    
    pantsArray = CCArray::create();
    pantsArray->retain();
    
    
    tickCount=0;
    score=0;
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
    
    
    
    collisionDetection();
    
    
    if (tickCount%60==0){
        
        spawnPants();
    }
    
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

void GameScene::spawnPants(){

    CCSprite *pants = CCSprite::create("Icon-57.png");
    pants->setPosition(ccp(WINDOW_SIZE.width/2,WINDOW_SIZE.height+100));
    addChild(pants);
    
    pantsArray->addObject(pants);

}

void GameScene::fallDownPants(CCSprite *pants){


    CCMoveTo *move = CCMoveTo::create(5,ccp(pants->getPosition().x, -100));
    
}

bool GameScene::collisionDetection(){
    
    //TODO:当たり判定
    CCObject *obj;
    CCARRAY_FOREACH_REVERSE(pantsArray, obj){
        CCSprite *pants = (CCSprite*)obj;
        
        if (mainChara->boundingBox().intersectsRect(pants->boundingBox())) {
            //キャッチ！
            pantsArray->removeLastObject(pants);
            pants->removeFromParentAndCleanup(true);
            
            score++;
        }
    }
    
    return true;
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

