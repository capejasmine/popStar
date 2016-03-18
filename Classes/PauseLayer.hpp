//
//  PauseLayer.hpp
//  popStar
//
//  Created by huangwen on 16/3/18.
//
//

#ifndef PauseLayer_hpp
#define PauseLayer_hpp

#include "cocos2d.h"
#include "ui/CocosGui.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCSGUIReader.h"
#include <functional>

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

class PauseLayer : public Layer {
public:
    
    static PauseLayer* create(std::string filename);
    
    virtual bool init(std::string filename);
    
    
    void dialogClick(Ref* obj, ui::Widget::TouchEventType type);
    
    void setMenuClickCall(std::function<void()> s){
        m_menuClick = s;
    }
    
private:
    
    Label* m_label;
    
    std::function<void()>  m_menuClick;
};

#endif /* PauseLayer_hpp */
