//
//  GameScene.hpp
//  popStar
//
//  Created by huangwen on 16/2/23.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "cocos2d.h"
#include "StartSprite.hpp"

USING_NS_CC;

class GameScene : public Layer{
public:
    GameScene();
    
    ~GameScene();
    
    CREATE_FUNC(GameScene);
    
    static Scene* scene();
    
    virtual bool init();
    
    void initBackGround();
    
    void initStar();
    //touch event
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    
private:
    
    StartSprite** m_starArr;
    
    int m_width;
    
    int m_height;
};

#endif /* GameScene_hpp */
