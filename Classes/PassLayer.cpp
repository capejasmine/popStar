//
//  PassLayer.cpp
//  popStar
//
//  Created by huangwen on 16/3/17.
//
//

#include "PassLayer.hpp"
#include "AudioController.hpp"
#include "Appconfig.hpp"
#include "GameController.hpp"
#include "ScoreManager.hpp"

PassLayer* PassLayer::create(std::string filename) {
    PassLayer* layer = new PassLayer();
    if(layer && layer->init(filename)){
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool PassLayer::init(std::string filename) {
    if(Layer::init())
    {
        auto widget = GUIReader::getInstance()->widgetFromJsonFile(filename.c_str());
        addChild(widget);
        
        Button* menuBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(widget, "menu"));
        menuBtn->addTouchEventListener(CC_CALLBACK_2(PassLayer::dialogClick, this));
        
        Button* resetBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(widget, "reset"));
        resetBtn->addTouchEventListener(CC_CALLBACK_2(PassLayer::dialogClick, this));
        
        Button* nextBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(widget, "next"));
        nextBtn->addTouchEventListener(CC_CALLBACK_2(PassLayer::dialogClick, this));
        
        //m_text = dynamic_cast<Text*>(Helper::seekWidgetByName(widget, "text"));
        m_label = Label::createWithBMFont("Marker Felt.ttf", "");
        widget->addChild(m_label);
        m_label->setPosition(getParent()->getContentSize()/2);
        
        
        return true;
    }
    return false;
}

void PassLayer::dialogClick(Ref* obj, ui::Widget::TouchEventType type) {
    if(type != ui::Widget::TouchEventType::ENDED) return;
    auto target = (Widget*)obj;
    auto name = target->getName();
    
    if(name.compare("next") == 0){
        xGam->enterGameScene();
    }
    else if(name.compare("menu") == 0)
    {
        xGam->enterStartScene();
    }
    else
    {
        xScor->resetPreScoreAndLevel();
        xGam->enterGameScene();
    }

    Audio->playEffect("Click.mp3");
}


void PassLayer::setText(std::string text) {
    
    m_label->setString(text);
}