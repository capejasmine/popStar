//
//  StartScene.hpp
//  popStar
//
//  Created by huangwen on 16/2/23.
//
//

#ifndef StartScene_hpp
#define StartScene_hpp

#include "cocos2d.h"
#include "cocosgui.h"

USING_NS_CC;

class StartScene : public Layer{
public:
    
    CREATE_FUNC(StartScene);
    
    static Scene* scene();
    
    virtual bool init();
    
    void initBackGround();
    
    void touchDown(Ref* pSender,ui::Widget::TouchEventType type);
private:
    
};

#endif /* StartScene_hpp */
