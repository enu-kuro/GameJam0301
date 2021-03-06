//
//  GameScene.cpp
//  GameJame
//
//  Created by Kurose Nobuhito on 2014/03/01.
//
//

#include "GameScene.h"
#include "SimpleAudioEngine.h"
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
    isEnableMoving=false;
    
    
    CCSprite* background = CCSprite::create("Gamebackground.png");
    background->setPosition(ccp(WINDOW_SIZE.width / 2, WINDOW_SIZE.height / 2));
    
    addChild(background);
    
    scoreLabel = CCLabelTTF::create("0", "arial", 100);
    scoreLabel->setColor(ccWHITE);
    scoreLabel->setPosition(ccp(WINDOW_SIZE.width/2+200, WINDOW_SIZE.height-100));
    this->addChild(scoreLabel);
    
    
    gameOverLabel = CCLabelTTF::create("Game Over!!!", "arial", 100);
    gameOverLabel->setColor(ccWHITE);
    gameOverLabel->setPosition(ccp(WINDOW_SIZE.width/2, WINDOW_SIZE.height-200));
    this->addChild(gameOverLabel);
    
    gameOverLabel->setVisible(false);
    
    mainChara = CCSprite::create("charlclle.png");
    mainChara->setPosition(ccp(WINDOW_SIZE.width/2,300));
    addChild(mainChara);
    
    pantsArray = CCArray::create();
    pantsArray->retain();
    

    //スペルミス
    CCSprite* pSelectedSprite = CCSprite::create("StartBrn.png");
    restart= CCMenuItemSprite::create(pSelectedSprite, pSelectedSprite, this, menu_selector(GameScene::restartGame));
    
    //restart =CCMenuItemLabel::create(CCLabelTTF::create("touch to start!", "Thonburi", 100), this,menu_selector(GameScene::restartGame));
    
    CCMenu* pMenu = CCMenu::create(restart, NULL);
    
    pMenu->setPosition(ccp(WINDOW_SIZE.width/2, WINDOW_SIZE.height/2));
    
    this->addChild(pMenu);
    
    
    
    return true;
}

void GameScene::restartGame(){
        scoreLabel->setString("0");
    isEnableMoving=false;
    tickCount=0;
    score=0;
    targetMovePointX=WINDOW_SIZE.width/2;
    scheduleUpdate();
    gameOverLabel->setVisible(false);
    restart->setVisible(false);
    
    mainChara->setTexture(CCTextureCache::sharedTextureCache()->addImage("charGet.png"));
    
                  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hentai.wav");
}

void GameScene::update(float dt) {
    
    tickCount++;
    if (isEnableMoving) {
        
        
        if (abs(mainChara->getPosition().x-targetMovePointX)<10) {
            mainChara->setPosition(ccp(targetMovePointX,mainChara->getPosition().y));
            
        }else{
            
            float moveValue = MOVE_SPEED;
            if (mainChara->getPosition().x>targetMovePointX) {
                moveValue=moveValue*-1;
            }
            
            mainChara->setPosition(ccpAdd(mainChara->getPosition(),ccp(moveValue,0)));
        }
    }
    
    collisionDetection();
    //    int hoge=tickCount%60;
    
    if (tickCount%40==0){
        
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
    
    
    
    int spawnPositionX = (arc4random()%(int)WINDOW_SIZE.width-20)+40;
    //FallObject *pants = FallObject::createFallObject("Icon-57.png");
    CCSprite *pants;
    int hoge = arc4random()%3;
    if (hoge==0) {
    pants = CCSprite::create("pointObj01.png");
    
    }else if(hoge==1) {
    pants = CCSprite::create("pointObj02.png");
    }else if(hoge==2) {
        pants = CCSprite::create("pointObj03.png");
    }
    
    
    //CCSprite *pants = CCSprite::create("pointObj03.png");
    pants->setPosition(ccp(spawnPositionX,WINDOW_SIZE.height+100));
    addChild(pants);
    
    pantsArray->addObject(pants);
    
    fallDownPants(pants);
    
}

void GameScene::fallDownPants(CCSprite *pants){
    
    
    CCMoveTo *move = CCMoveTo::create(3.5,ccp(pants->getPosition().x, -100));
    
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
            
              CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hentai.wav");
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
    
    
    mainChara->setTexture(CCTextureCache::sharedTextureCache()->addImage("charlclle.png"));
    

    
    CCObject *obj;
    CCARRAY_FOREACH_REVERSE(pantsArray, obj){
        CCSprite *pants = (CCSprite*)obj;
        pantsArray->removeObject(pants);
        pants->removeFromParentAndCleanup(true);
        
    }
    
    
}

bool GameScene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
    isEnableMoving=true;
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
    isEnableMoving=false;
}


//void GameScene::charaMove(CCPoint point){
//
//    CCMoveTo *move = CCMoveTo::create(1, ccp(point.x, mainChara->getPosition().y));
//    mainChara->runAction(move);
//    
//}

