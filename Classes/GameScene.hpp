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

enum kSideTag{
    kTop = 567,
    kDown,
    kLeft,
    kRight
};

class GameScene : public Layer{
public:
    GameScene();
    
    ~GameScene();
    
    CC_SYNTHESIZE(StartSprite*, curentStar, CurrentTouchStar);
    CC_SYNTHESIZE(bool, touch, touchTag);
    
    CREATE_FUNC(GameScene);
    
    static Scene* scene();
    
    virtual bool init();
    
    void initBackGround();
    
    void initStar();
    
    void cheakSameColorStar(StartSprite* star);
    
    void removeSameColorStar();
    
    void playBrokenEffect();
    
    void cheakFourSide(StartSprite* star, kSideTag side);
    
    bool inSameColorList(StartSprite* star);
    
    void cheakAndFallStar();
    
    void cheakAndCombineStar();
    
    //touch event
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    
private:
    
    StartSprite** m_starArr;
    
    std::list<StartSprite*> sameColorList;
    
    std::list<StartSprite*> cheakedColorList;
    
    int m_width;
    
    int m_height;
};

#endif /* GameScene_hpp */
