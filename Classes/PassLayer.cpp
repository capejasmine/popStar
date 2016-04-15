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
#include "DataManager.hpp"

PassLayer* PassLayer::create(std::string filename,int count, bool pass) {
    PassLayer* layer = new PassLayer();
    layer->setpassSign(pass);
    if(layer && layer->init(filename, count)){
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool PassLayer::init(std::string filename, int count) {
    if(Layer::init())
    {
        m_widget = GUIReader::getInstance()->widgetFromJsonFile(filename.c_str());
        addChild(m_widget);
        
        Button* menuBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(m_widget, "menu"));
        menuBtn->addTouchEventListener(CC_CALLBACK_2(PassLayer::dialogClick, this));
        
        Button* resetBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(m_widget, "reset"));
        resetBtn->addTouchEventListener(CC_CALLBACK_2(PassLayer::dialogClick, this));
        
        Button* nextBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(m_widget, "next"));
        nextBtn->addTouchEventListener(CC_CALLBACK_2(PassLayer::dialogClick, this));
        
        Text*  score = dynamic_cast<Text*>(Helper::seekWidgetByName(m_widget, "text1"));
        score->setString(std::to_string(xScor->getScore()));
        score->setColor(cocos2d::Color3B::BLACK);
        
        Text*  best = dynamic_cast<Text*>(Helper::seekWidgetByName(m_widget, "text2"));
        best->setString(std::to_string(xScor->getBestScore()));
        best->setColor(cocos2d::Color3B::BLACK);
        
        if(!getpassSign())
        {
            nextBtn->setVisible(false);
            resetBtn->setPosition(nextBtn->getPosition());
        }
        else
        {
            resetBtn->setVisible(false);
        }
        
        m_delay = 1.0;
        starAniamtion(count);
        
        return true;
    }
    return false;
}

void PassLayer::dialogClick(Ref* obj, ui::Widget::TouchEventType type) {
    if(type != ui::Widget::TouchEventType::ENDED) return;
    auto target = (Widget*)obj;
    auto name = target->getName();
    
    if(name.compare("next") == 0){
//        xData->removeRecord();
//        xScor->saveScore();
//        xScor->addLevel();
        xGam->enterGameScene();
    }
    else if(name.compare("menu") == 0)
    {
        if(!getpassSign())
        {
            xScor->resetLevel();
            xScor->resetScore();
            xData->removeRecord();
            xGam->enterLoadinglayer();
        }
        else
        {
            xData->setPassRecord(true);
            xScor->saveScore();
            //xScor->addLevel();
            xGam->enterLoadinglayer();
        }
    }
    else
    {
        xScor->resetPreScoreAndLevel();
        xGam->enterGameScene();
    }

    Audio->playEffect("Click.mp3");
}

void PassLayer::starAniamtion(int count) {
    
    for(int i = 1; i <= count; i++){
        auto star = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_widget, "star" + std::to_string(i)));
        auto action = Sequence::create(DelayTime::create(m_delay), CallFunc::create([=](){
            star->setVisible(true);
        }),NULL);
        star->runAction(action);
        m_delay += 0.5;
    }
    
}
