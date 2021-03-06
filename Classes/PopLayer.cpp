//
//  PopLayer.cpp
//  popStar
//
//  Created by huangwen on 16/2/23.
//
//

#include "PopLayer.hpp"
#include "AudioController.hpp"

PopLayer* PopLayer::create(std::string filename) {
    PopLayer* layer = new PopLayer();
    if(layer && layer->init(filename)){
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool PopLayer::init(std::string filename) {
    if(Layer::init())
    {
        auto widget = GUIReader::getInstance()->widgetFromJsonFile(filename.c_str());
        addChild(widget);
        
        auto center = Helper::seekWidgetByName(widget, "center");
        center->setScale(0);
        
        center->runAction(ScaleTo::create(0.4, 1));
        
        Button* yesBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(widget, "yes"));
        yesBtn->addTouchEventListener(CC_CALLBACK_2(PopLayer::dialogYesClick, this));
        
        Button* noBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(widget, "no"));
        noBtn->addTouchEventListener(CC_CALLBACK_2(PopLayer::dialogNoClick, this));
        
        //m_text = dynamic_cast<Text*>(Helper::seekWidgetByName(widget, "text"));
        Audio->playEffect("music/TPS_PopUp.caf");
        return true;
    }
    return false;
}

void PopLayer::dialogYesClick(Ref* obj, ui::Widget::TouchEventType type) {
    if(type != ui::Widget::TouchEventType::ENDED) return;
    if(m_yesClick)
    {
        Audio->stopMusic();
        Audio->playEffect("Media/ButtonClick.m4a");
        
        m_yesClick();
    }
}

void PopLayer::dialogNoClick(Ref* obj, ui::Widget::TouchEventType type) {
    if(type != ui::Widget::TouchEventType::ENDED) return;
    if(m_noClick)
    {
        Audio->playEffect("Media/ButtonClick.m4a");
        Audio->playEffect("music/TPS_PopUp.caf");
        m_noClick();
    }
}


void PopLayer::setText(std::string text) {
    
    //m_text->setString(text);
}