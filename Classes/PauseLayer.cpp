//
//  PauseLayer.cpp
//  popStar
//
//  Created by huangwen on 16/3/18.
//
//

#include "PauseLayer.hpp"
#include "AudioController.hpp"
#include "Appconfig.hpp"
#include "GameController.hpp"
#include "ScoreManager.hpp"
#include "DataManager.hpp"

PauseLayer* PauseLayer::create(std::string filename) {
    PauseLayer* layer = new PauseLayer();
    if(layer && layer->init(filename)){
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool PauseLayer::init(std::string filename) {
    if(Layer::init())
    {
        auto widget = GUIReader::getInstance()->widgetFromJsonFile(filename.c_str());
        addChild(widget);
        
        
        Button* menuBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(widget, "menu"));
        menuBtn->addTouchEventListener(CC_CALLBACK_2(PauseLayer::dialogClick, this));
        
        Button* resetBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(widget, "reset"));
        resetBtn->addTouchEventListener(CC_CALLBACK_2(PauseLayer::dialogClick, this));
        resetBtn->setVisible(false);
        
        Button* playBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(widget, "play"));
        playBtn->addTouchEventListener(CC_CALLBACK_2(PauseLayer::dialogClick, this));
        
        
        return true;
    }
    return false;
}

void PauseLayer::dialogClick(Ref* obj, ui::Widget::TouchEventType type) {
    if(type != ui::Widget::TouchEventType::ENDED) return;
    auto target = (Widget*)obj;
    auto name = target->getName();
    
    if(name.compare("reset") == 0){
        xScor->resetPreScoreAndLevel();
        xData->removeRecord();
        xGam->enterGameScene();
    }
    else if(name.compare("menu") == 0)
    {
        if(m_menuClick){
            m_menuClick();
            xGam->enterLoadinglayer();
        }
    }
    else
    {
        this->removeFromParent();
    }
    
    Audio->playEffect("Click.mp3");
}
