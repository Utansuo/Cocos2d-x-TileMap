#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;



HelloWorld::HelloWorld()
{
    map=CCTMXTiledMap::create("battleCity.tmx");
    setTouchEnabled(true);
    this->addChild(map,1);
    sprite=CCSprite::create("grossini_dance_05.png");
    //CCSize size=CCDirector::sharedDirector()->getWinSize();
   
    map->addChild(sprite);
   
    this->scheduleUpdate();
    GetBound();
    map->setPosition(0,bound.y);
    sprite->setPosition(ccp(0,map->getTileSize().height*map->getMapSize().height));
    startPoint.x=sprite->getPositionX();
    startPoint.y=sprite->getPositionY();
//    cx=0,cy=0,cz=0,ex=0,ey=0,ez=0;
//    this->getCamera()->setEyeXYZ(0,0,0.1);
//    this->getCamera()->setCenterXYZ(0,0,0);
//    this->getCamera()->setUpXYZ(0,1,0);
     CCLog("%f , %f ", map->getPositionX(),map->getPositionY());
   
}
HelloWorld::~HelloWorld()
{

}

void HelloWorld::update(float dt)
{
   
    
    switch (spState)
    {
          
        case Run:
        {
            float dis=ccpDistance(sprite->getPosition(),startPoint);
            struct cc_timeval now;
            CCTime::gettimeofdayCocos2d(&now, NULL);
            long tempTime=(now.tv_sec * 1000 + now.tv_usec / 1000.0);
             //CCLog("tempTime= %u,curTime=%u",tempTime,curTime);
            float timeOffSet=(tempTime-curTime)/1000.0;
          
            //CCLog("timeOffSet= %f,takeTime=%f",timeOffSet,takeTime);
            if(takeTime<=0)
            {
                spState=Stop;
            }
            else
            {
                movePlayer(dic.x*timeOffSet*100,dic.y*timeOffSet*100);
//                CCPoint temp;
//                temp.x=sprite->getPositionX()-dic.x*2;
//                temp.y=sprite->getPositionY()-dic.y*2;
//                sprite->setPosition(temp);
            }
              takeTime-=timeOffSet*1000;
            curTime=tempTime;
        }break;
            
        case Stop:
        {
            return;
        }break;
            
        default:break;

    }
}




void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

 CCPoint HelloWorld::GetDic(CCPoint start,CCPoint end)
{
    CCPoint tempDic=ccpSub(start,end);
    takeTime=ccpLength(tempDic)/100.0*1000;
 
    tempDic=ccpNormalize(tempDic);
    
    return tempDic;
}
void HelloWorld::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{

    touchFlag=false;
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    
    beginLocation = touch->getLocation();            // Get the touch position
    beginLocation = this->convertToNodeSpace(beginLocation);  // Convert to the node space of this class
   

}
void HelloWorld::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    touchFlag=true;
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
        
    CCPoint touchLocation = touch->getLocation();
                   // Get the touch position
    touchLocation = this->convertToNodeSpace(touchLocation);  // Convert to the node space of this class
    float offsetX=touchLocation.x-beginLocation.x;
    float offsetY=touchLocation.y-beginLocation.y;
    moveMap(offsetX,offsetY);
    beginLocation=touchLocation;
}

void HelloWorld::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    if(touchFlag)
    {
        touchFlag=false;
    }
    else
    {
               
        startPoint.x=beginLocation.x-map->getPositionX();
        startPoint.y=beginLocation.y-map->getPositionY();
        CCLog("%f ,%f",startPoint.x,startPoint.y);
        struct cc_timeval now;
        CCTime::gettimeofdayCocos2d(&now, NULL);
        curTime=(now.tv_sec * 1000 + now.tv_usec / 1000.0);
         dic=GetDic(sprite->getPosition(),startPoint);
        spState=Run;
        
    }
}

void HelloWorld::moveMap(float x, float y)
{

        float posX=map->getPositionX()+x;
        float posY=map->getPositionY()+y;
      CCLog("%f ,map= %f, %f", posX,map->getPositionX(),x);
        if(posX>0)
        {
            posX=0;
        }
        if(posX<bound.x)
        {
            posX=bound.x;
        }
        if(posY>0)
        {
          posY=0;
        }
        if(posY<bound.y)
        {
            posY=bound.y;
        }
    CCLog("%f , posY=%f ", posX,posY);
        map->setPosition(posX,posY);
}

void HelloWorld::GetBound()
{

    float mapWidth=map->getTileSize().width*map->getMapSize().width;
    float mapHeight=map->getTileSize().height*map->getMapSize().height;
    float screenWidth=CCDirector::sharedDirector()->getWinSize().width;
    float screenHeight=CCDirector::sharedDirector()->getWinSize().height;
    bound.x=screenWidth-mapWidth;
    bound.y=screenHeight-mapHeight;
}
void HelloWorld::movePlayer(float x, float y)
{
    CCPoint temp;
    temp.x=sprite->getPositionX()-x;
    temp.y=sprite->getPositionY()-y;
     //CCLog("%f, screenWidth=%f",(temp.y+map->getPositionY()),(CCDirector::sharedDirector()->getWinSize().height/2));
    if((temp.y+map->getPositionY())<(CCDirector::sharedDirector()->getWinSize().height/2))
    {
        //	print("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
        if(map->getPositionY()==0)
        {
            
        }
        else
        {
            moveMap(0,y);
        }
        
    }
    else
    {
        //print("#######################################");
        if(map->getPositionY()<bound.y)
        {
            map->setPositionY(bound.y);
        }
        if(map->getPositionY()==bound.y)
        {
            
        }
        else
        {
            moveMap(0,y);
        }
    }
   
    
    if((temp.x+map->getPositionX())<(CCDirector::sharedDirector()->getWinSize().width/2))
    {
        //print("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
        
        if(map->getPositionX()==0)
        {
            
        }
        else
        {
            moveMap(x,0);
        }
    }
    else
    {
        //print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        if(map->getPositionX()<bound.x)
        {
           map->setPositionX(bound.x) ;
        }
        if(map->getPositionX()==bound.x)
        {
            
        }
        else
        {
            moveMap(x,0);
        }
    }

    sprite->cocos2d::CCNode::setPosition(temp);
}





