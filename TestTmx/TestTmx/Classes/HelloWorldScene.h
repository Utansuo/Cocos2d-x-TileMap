#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "vector3.h"
using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{
public:


    HelloWorld();
    ~HelloWorld();
    cocos2d::CCTMXTiledMap* map;
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    // preprocessor macro for "static create()" constructor ( node() deprecated )
   virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    //virtual void registerWithTouchDispatcher();
    CCPoint dic;
private:

    CCPoint beginLocation;
    CCPoint startPoint;
    CCSprite *sprite;
   virtual void update(float dt);
    void GetBound();
    void moveMap(float x,float y );
    void movePlayer(float x,float y);
    CCPoint GetDic(CCPoint start,CCPoint end);
     float cx=0,cy=0,cz=0,ex=0,ey=0,ez=0;
    enum SpriteState
    {
        Run,
        Stop
    };
    SpriteState spState;
    bool touchFlag;
    CCPoint bound;
    long curTime;
    long takeTime;
};

#endif // __HELLOWORLD_SCENE_H__
