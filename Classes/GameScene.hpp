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
#include "cocosGui.h"
#include "PopLayer.hpp"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCSGUIReader.h"

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
    
    void intStarWithRecord();
    
    void cheakSameColorStar(StartSprite* star,bool tag);
    
    void removeSameColorStar();
    
    void playBrokenEffect();
    
    void cheakFourSide(StartSprite* star, kSideTag side, bool tag);
    
    bool inSameColorList(StartSprite* star);
    
    void cheakAndFallStar();
    
    void cheakAndCombineStar();
    
    void cheakAndGameOver();
    
    void yesBtnCall();
    
    void noBtnCall();
    
    void updateAnimation(float dt);
    
    void startAnimationOver(float dt);
    
    //touch event
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    
    void touchDown(Ref* obj, ui::Widget::TouchEventType type);
    
private:
    
    StartSprite** m_starArr;
    
    std::list<StartSprite*> sameColorList;
    
    std::list<StartSprite*> cheakedColorList;
    
    int m_width;
    
    int m_height;
    
    int m_countStar;  // 记录总数 判断是否结束游戏
    
    PopLayer* m_popLayer;
    
    std::string m_data;
    
    ui::Widget* m_root;
    
    Text*  m_score;
    
    int m_pos;
    
    float m_delay = 0;
};

#endif /* GameScene_hpp */
