//
//  PopLayer.cpp
//  popStar
//
//  Created by huangwen on 16/2/23.
//
//

#include "PopLayer.hpp"

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
        
        Button* yesBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(widget, "yes_btn"));
        yesBtn->addTouchEventListener(CC_CALLBACK_2(PopLayer::dialogYesClick, this));
        
        Button* noBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(widget, "no_btn"));
        noBtn->addTouchEventListener(CC_CALLBACK_2(PopLayer::dialogNoClick, this));
        
        m_text = dynamic_cast<Text*>(Helper::seekWidgetByName(widget, "text"));
        
        return true;
    }
    return false;
}

void PopLayer::dialogYesClick(Ref* obj, ui::Widget::TouchEventType type) {
    if(type != ui::Widget::TouchEventType::ENDED) return;
    if(m_yesClick)
    {
        m_yesClick();
    }
}

void PopLayer::dialogNoClick(Ref* obj, ui::Widget::TouchEventType type) {
    if(type != ui::Widget::TouchEventType::ENDED) return;
    if(m_noClick)
    {
        m_noClick();
    }
}


void PopLayer::setText(std::string text) {
    m_text->setString(text);
}