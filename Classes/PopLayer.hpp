//
//  PopLayer.hpp
//  popStar
//
//  Created by huangwen on 16/2/23.
//
//

#ifndef PopLayer_hpp
#define PopLayer_hpp

#include "cocos2d.h"
#include "ui/CocosGui.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCSGUIReader.h"
#include <functional>

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

class PopLayer : public Layer {
public:
    
    static PopLayer* create(std::string filename);
    
    virtual bool init(std::string filename);
    
    void setClickCall(std::function<void()> yes, std::function<void()> no){
        m_yesClick = yes;
        m_noClick = no;
    }
    
    void dialogYesClick(Ref* obj, ui::Widget::TouchEventType type);
    
    void dialogNoClick(Ref* obj, ui::Widget::TouchEventType type);
    
    void setText(std::string text);
    
private:
    std::function<void()> m_yesClick;
    std::function<void()> m_noClick;
    
    Text* m_text;
};

#endif /* PopLayer_hpp */
