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
#include "ui/CocosGui.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCSGUIReader.h"

USING_NS_CC;

class StartScene : public Layer{
public:
    
    CREATE_FUNC(StartScene);
    
    static Scene* scene();
    
    virtual bool init();
    
    void initBackGround();
    
    void touchDown(Ref* pSender,ui::Widget::TouchEventType type);
private:
    
    cocos2d::ui::Widget* m_root;
};

#endif /* StartScene_hpp */
