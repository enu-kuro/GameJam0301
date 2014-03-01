//
//  FallObject.h
//  GameJame
//
//  Created by 王純 on 2014/03/01.
//
//

#ifndef __GameJame__FallObject__
#define __GameJame__FallObject__

#include "cocos2d.h"

using namespace cocos2d;

enum FallActionList
{
    action01,
    action02,
    action03,
    action04,
    action05,
};

class FallObject : public CCSprite {
public:
	virtual ~FallObject();
    
	FallObject();
    
    static FallObject *createFallObject(const char* filename);
    
    void createFallAction(int actionIndex,CCPoint bottomPoint,int time);
    
    CCPoint outPutCurrentPostion();
private:
    bool checkCrash(CCRect getObjectRect);
    void removeFromLayer(bool flag);
    
};

#endif /* defined(__GameJame__FallObject__) */
