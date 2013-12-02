//
//  GameWorldScene.cpp
//  MyTDDemo
//
//  Created by cesc on 13-12-2.
//
//

#include "GameWorldScene.h"
#define  ZORDER_4_TOWER_BASE  11

GameWorldScene::GameWorldScene(){
    
    towerBasesArray = CCArray::create();
    CC_SAFE_RETAIN( towerBasesArray );
    
    
}

GameWorldScene::~GameWorldScene(){
    
    CC_SAFE_RELEASE_NULL( towerBasesArray );
    
}

CCScene* GameWorldScene::scene(){
    
    CCScene* sc = CCScene::create();
    
    sc->addChild( GameWorldScene::create() );
    
    return sc;
}

bool GameWorldScene::init(){
    
    if ( !CCLayer::init() ) {
        return false;
    }
    
    CCSprite* bg_sprite = CCSprite::create( "res/Bg.png");
    this->addChild( bg_sprite, -1);
    bg_sprite->setAnchorPoint( CCPointZero );
    
    
    loadTowersBase();
    
    setTouchEnabled( true );
    return true;
}

void GameWorldScene::loadTowersBase(){
    
    
    CCArray* arr =  CCArray::createWithContentsOfFile( "res/TowersPosition.plist" );
    
    CCObject* ob = NULL;
    
    
    CCARRAY_FOREACH( arr, ob){
        
        CCDictionary* dic = (CCDictionary*)ob;
        
        CCString* xstr = (CCString*)dic->objectForKey( "x");
        CCString* ystr = (CCString*)dic->objectForKey( "y");
        
        CCPoint p = ccp( xstr->floatValue() , ystr->floatValue() );
        
        CCSprite* base = CCSprite::create( "res/open_spot.png");
        
        this->addChild( base,  ZORDER_4_TOWER_BASE );
        base->setPosition( p );
        
        towerBasesArray->addObject( base );
        
    }
    
    
    
}




bool GameWorldScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    CCObject* o = NULL;
    
    CCARRAY_FOREACH(towerBasesArray, o ){
        
        CCSprite* base = (CCSprite*)o;
        
        CCPoint touchPoint = pTouch->getLocation();
        
        if ( base->boundingBox().containsPoint( touchPoint ) ) {
            
           if ( !base->getUserData() ) {
            
            CCSprite* tower  = CCSprite::create( "res/tower.png");
            tower->setPosition( base->getPosition() );
            
            this->addChild( tower, base->getZOrder() + 1);
            
               base->setUserData( tower );
        
               break;
           }
            
        }
        
        
    }
    
    
    return true;
}


void GameWorldScene::onEnter(){
    CCLayer::onEnter();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate( this, 0,  true );
}

void GameWorldScene::onExit(){
    
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate( this );
    
    CCLayer::onExit();
}