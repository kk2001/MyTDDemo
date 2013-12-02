//
//  GameWorldScene.h
//  MyTDDemo
//
//  Created by cesc on 13-12-2.
//
//

#ifndef __MyTDDemo__GameWorldScene__
#define __MyTDDemo__GameWorldScene__

#include "cocos2d.h"
USING_NS_CC;


class GameWorldScene: public CCLayer {
    
    
public:
    
    GameWorldScene();
    
    ~GameWorldScene();
    
    virtual bool init();
    
    CREATE_FUNC( GameWorldScene );
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void onEnter();
    virtual void onExit();
    
    static CCScene* scene();
    
    void loadTowersBase();
    
public:
    CCArray* towerBasesArray;
    
};

#endif /* defined(__MyTDDemo__GameWorldScene__) */
