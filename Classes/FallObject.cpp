//
//  FallObject.cpp
//  GameJame
//
//  Created by 王純 on 2014/03/01.
//
//

#include "FallObject.h"

FallObject::FallObject()
{
}

FallObject::~FallObject()
{
    
}

FallObject* FallObject::createFallObject(const char *filename)
{
    FallObject *pobSprite = new FallObject();
    if (pobSprite && pobSprite->initWithFile(filename))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void FallObject::createFallAction(int actionIndex,CCPoint bottomPoint,int time)
{
    CCFiniteTimeAction * seq = NULL;
    
    switch (actionIndex) {
        case action01:
        {
            CCActionInterval * move1 = CCMoveTo::create(time, bottomPoint);
            seq = CCEaseSineIn::create(move1);
        }
            break;
        case action02:
        {
            CCActionInterval * move2 = CCMoveTo::create(time, bottomPoint);
            seq = CCEaseSineOut::create(move2);
        }
            break;
        case action03:
        {
            seq = CCMoveTo::create(time, bottomPoint);
        }
            break;
        case action04:
        {
            seq = CCMoveTo::create(time, bottomPoint);
        }
            break;
        case action05:
        {
            seq = CCMoveTo::create(time, bottomPoint);
        }
            break;
        default:
            break;
    }
    
    this->runAction(seq);
}

CCPoint FallObject::outPutCurrentPostion()
{
    CCPoint point = getPosition();
    
    return point;
}

bool FallObject::checkCrash(CCRect getObjectRect)
{
    bool isCrashFlag = false;
    if (this->boundingBox().intersectsRect(getObjectRect)) {
        isCrashFlag = true;
    }
    return isCrashFlag;
}

void FallObject::removeFromLayer(bool flag)
{
    this->removeFromParentAndCleanup(true);
}

