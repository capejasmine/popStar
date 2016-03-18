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
    
    static PassLayer* create(std::string filename,int count);
    
    virtual bool init(std::string filename,int count);
    
    
    void dialogClick(Ref* obj, ui::Widget::TouchEventType type);
    
    void starAniamtion(int count);
    
private:
    Widget* m_widget;
    
    float m_delay;
    
};

#endif /* PassLayer_hpp */
