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
    
    
    
    scoreLabel = CCLabelTTF::create("0", "arial", 100);
    scoreLabel->setColor(ccWHITE);
    scoreLabel->setPosition(ccp(WINDOW_SIZE.width/2+200, WINDOW_SIZE.height-100));
    this->addChild(scoreLabel);
    
    
    gameOverLabel = CCLabelTTF::create("Game Over!!!", "arial", 100);
    gameOverLabel->setColor(ccWHITE);
    gameOverLabel->setPosition(ccp(WINDOW_SIZE.width/2, WINDOW_SIZE.height-200));
    this->addChild(gameOverLabel);
    
    gameOverLabel->setVisible(false);
    
    mainChara = CCSprite::create("Icon-114.png");
    mainChara->setPosition(ccp(WINDOW_SIZE.width/2,200));
    addChild(mainChara);
    
    pantsArray = CCArray::create();
    pantsArray->retain();
    
    restart =CCMenuItemLabel::create(CCLabelTTF::create("touch to start!", "Thonburi", 100), this,menu_selector(GameScene::restartGame));

    CCMenu* pMenu = CCMenu::create(restart, NULL);

    pMenu->setPosition(ccp(WINDOW_SIZE.width/2, WINDOW_SIZE.height/2));
    
    this->addChild(pMenu);
    
    
    
    return true;
}

void GameScene::restartGame(){

    tickCount=0;
    score=0;
        targetMovePointX=WINDOW_SIZE.width/2;
        scheduleUpdate();

    restart->setVisible(false);
}

void GameScene::update(float dt) {
    
    tickCount++;
    
    if (abs(mainChara->getPosition().x-targetMovePointX)<10) {
        mainChara->setPosition(ccp(targetMovePointX,mainChara->getPosition().y));
        
    }else{
        
        float moveValue = MOVE_SPEED;
        if (mainChara->getPosition().x>targetMovePointX) {
            moveValue=moveValue*-1;
        }
        
        mainChara->setPosition(ccpAdd(mainChara->getPosition(),ccp(moveValue,0)));
    }
    
    
    collisionDetection();
    //    int hoge=tickCount%60;

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
    
    
    int spawnPositionX = (arc4random()%(int)WINDOW_SIZE.width-80)+40;
    //FallObject *pants = FallObject::createFallObject("Icon-57.png");
    CCSprite *pants = CCSprite::create("Icon-57.png");
    pants->setPosition(ccp(spawnPositionX,WINDOW_SIZE.height+100));
    addChild(pants);
    
    pantsArray->addObject(pants);
    
    fallDownPants(pants);
    
}

void GameScene::fallDownPants(CCSprite *pants){
    
    
    CCMoveTo *move = CCMoveTo::create(3,ccp(pants->getPosition().x, -100));
    
    CCCallFunc *func = CCCallFunc::create(this, callfunc_selector(GameScene::gameOver));
    CCSequence *seq = CCSequence::create(move,func,NULL);
    
    pants->runAction(seq);
    
}

bool GameScene::collisionDetection(){
    
    //TODO:当たり判定
    CCObject *obj;
    CCARRAY_FOREACH_REVERSE(pantsArray, obj){
        FallObject *pants = (FallObject*)obj;
        
        if (mainChara->boundingBox().intersectsRect(pants->boundingBox())) {
            //キャッチ！
            CCLOG("catch!");
            pantsArray->removeObject(pants);
            pants->removeFromParentAndCleanup(true);
            
            score++;
            
            char scoreStr[10] = {0};
            sprintf(scoreStr, "%d", score);
            scoreLabel->setString(scoreStr);
            
            return true;
        }
    }
    
    return false;
}


void GameScene::gameOver(){
    tickCount=0;
    CCLOG("gameover");

    gameOverLabel->setVisible(true);
    restart->setVisible(true);
    unscheduleUpdate();

    
    
    CCObject *obj;
    CCARRAY_FOREACH_REVERSE(pantsArray, obj){
        CCSprite *pants = (CCSprite*)obj;
        pantsArray->removeObject(pants);
        pants->removeFromParentAndCleanup(true);
        
    }
    

}

bool GameScene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
    targetMovePointX = this->convertTouchToNodeSpace(pTouch).x;
    
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

