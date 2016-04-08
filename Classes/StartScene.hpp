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
#include "NumberScroller.hpp"

USING_NS_CC;

class StartScene : public Layer{
public:
    
    CREATE_FUNC(StartScene);
    
    static Scene* scene();
    
    virtual bool init();
    
    void initBackGround();
    
    void touchDown(Ref* pSender,ui::Widget::TouchEventType type);
    
    void updateSocre(int socre);
private:
    
    cocos2d::ui::Widget* m_root;
    
    std::vector<Node*> m_node;
    
    NumberScroller*  m_scroll;
    
    int num = 10;
};

#endif /* StartScene_hpp */
