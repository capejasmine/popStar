//
//  StartScene.cpp
//  popStar
//
//  Created by huangwen on 16/2/23.
//
//
#define   BACK_GROUND_PNG   "bg_main.png"
#define   START_PNG         "newgame.png"
#define   RESUME_PNG        "resume.png"
#define   RATE_PNG          "rate.png"
#define   POP_PNG           "pop.png"
#define   STAR_PNG          "star.png"

#include "StartScene.hpp"
#include "Appconfig.hpp"
#include "GameController.hpp"
#include "AudioController.hpp"
#include "ScoreManager.hpp"
#include "DataManager.hpp"
#include "GameController.hpp"
#include "UITools.h"
#include "MessageLayer.hpp";



Scene* StartScene::scene() {
    Scene* pScene = Scene::create();
    pScene->addChild(StartScene::create());
    return pScene;
}

bool StartScene::init() {
    if (!Layer::init()) {
        return false;
    }
    
    m_root = GUIReader::getInstance()->widgetFromJsonFile("start.json");
    addChild(m_root);
    
    log("StartScene");
    initBackGround();
    
    xGam->setFallMode(quickRandom(0, 2));
    
    
    
    
    return true;
}

void StartScene::initBackGround() {
    
    auto new_game = (Button*)(Helper::seekWidgetByName(m_root, "new_game"));
    new_game->addTouchEventListener(CC_CALLBACK_2(StartScene::touchDown, this));
    
//    auto rate = (Button*)(Helper::seekWidgetByName(m_root, "rate"));
//    rate->addTouchEventListener(CC_CALLBACK_2(StartScene::touchDown, this));
    
    auto resume = (Button*)(Helper::seekWidgetByName(m_root, "resume"));
    resume->addTouchEventListener(CC_CALLBACK_2(StartScene::touchDown, this));
    
    auto about = (Button*)(Helper::seekWidgetByName(m_root, "about"));
    about->addTouchEventListener(CC_CALLBACK_2(StartScene::touchDown, this));
    
    auto music = (Button*)(Helper::seekWidgetByName(m_root, "music"));
    music->addTouchEventListener(CC_CALLBACK_2(StartScene::touchDown, this));
    
}

void StartScene::touchDown(Ref* pSender,ui::Widget::TouchEventType type) {
    if (ui::Widget::TouchEventType::ENDED != type) return;
    
    auto target = (Widget*)pSender;
    std::string name = target->getName();
    
    
    if (name.compare("new_game") == 0) {
//        //  清除历史纪录
//        xData->removeRecord();
//        xScor->resetScore();
//        xScor->resetLevel();
        xGam->enterLoadinglayer();
    }
    else if (name.compare("resume") == 0){
        if(!xData->isExsitRecord() && !xData->getPassRecord())
        {
            log("there is not exist the record");
            auto popup = MessageLaye::create(kEventType::kWorning);
            addChild(popup, kzOrderPopUp);
            
        }
        else
        {
            //  清除历史纪录
            xData->removeRecord();
            xScor->resetScore();
            xScor->resetLevel();
            //GameController::getInstace()->enterGameScene();
            
        }
    }
    else if(name.compare("about") == 0){
        
        auto popup = MessageLaye::create(kEventType::kAbout);
        addChild(popup, kzOrderPopUp);
    }
    else if(name.compare("music") == 0){
        Audio->changeMode();
    }
    else
    {
        
        //updateSocre(quickRandom(50, 200));
    }
     Audio->playEffect("click.mp3");
}

void StartScene::updateSocre(int socre){
//    auto pos = m_node.at(0)->getPosition();
//    m_node.at(0)->runAction(Sequence::create(MoveBy::create(0.2, Vec2(0,540)), CallFunc::create([=](){
//        m_node.at(0)->setPosition(pos);
//    }),NULL));
    m_scroll->addNumber(num);
    num+=30;
}


