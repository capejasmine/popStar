//
//  PassLayer.hpp
//  popStar
//
//  Created by huangwen on 16/3/17.
//
//

#ifndef PassLayer_hpp
#define PassLayer_hpp

#include "cocos2d.h"
#include "ui/CocosGui.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCSGUIReader.h"
#include <functional>

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

class PassLayer : public Layer {
public:
    
    static PassLayer* create(std::string filename);
    
    virtual bool init(std::string filename);
    
    
    void dialogClick(Ref* obj, ui::Widget::TouchEventType type);
    
    void setText(std::string text);
    
private:
    
    Text* m_text;
    
    Label* m_label;
};

#endif /* PassLayer_hpp */
