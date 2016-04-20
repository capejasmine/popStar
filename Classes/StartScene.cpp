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
    
    Audio->playEffect("music/HERO_FEVER.caf");
    
    Audio->playMuic("music/Title.caf");
    
    
    return true;
}

void StartScene::initBackGround() {
    
    auto new_game = (Button*)(Helper::seekWidgetByName(m_root, "new_game"));
    new_game->addTouchEventListener(CC_CALLBACK_2(StartScene::touchDown, this));
    
    auto bird = (ImageView*)(Helper::seekWidgetByName(m_root, "Image_5"));
    bird->setScale(0);
    bird->runAction(Sequence::create(DelayTime::create(0.5), ScaleTo::create(0.4, 1),NULL));
    
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
        Audio->stopMusic();
        xGam->enterLoadinglayer();
    }
    else if (name.compare("resume") == 0){
        if(!xData->isExsitRecord() && !xData->getPassRecord())
        {
            log("there is not exist the record");
            if(!m_layer){
                m_layer = MessageLaye::create(kEventType::kWorning);
                m_layer->setClickCall(CC_CALLBACK_0(StartScene::clickCall, this));
                addChild(m_layer, kzOrderPopUp);
            }
            
        }
        else
        {
            //  清除历史纪录
            xData->removeRecord();
            xScor->resetScore();
            xScor->resetLevel();
            
            if(!m_layer){
                m_layer = MessageLaye::create(kEventType::kClear);
                m_layer->setClickCall(CC_CALLBACK_0(StartScene::clickCall, this));
                addChild(m_layer, kzOrderPopUp);
            }
            //GameController::getInstace()->enterGameScene();
            
        }
    }
    else if(name.compare("about") == 0){
        if(!m_layer){
            m_layer = MessageLaye::create(kEventType::kAbout);
            m_layer->setClickCall(CC_CALLBACK_0(StartScene::clickCall, this));
            addChild(m_layer, kzOrderPopUp);
        }
    }
    else if(name.compare("music") == 0){
        Audio->changeMode();
    }
    else
    {
        
        //updateSocre(quickRandom(50, 200));
    }
     Audio->playEffect("Media/ButtonClick.m4a");
}

void StartScene::updateSocre(int socre){
//    auto pos = m_node.at(0)->getPosition();
//    m_node.at(0)->runAction(Sequence::create(MoveBy::create(0.2, Vec2(0,540)), CallFunc::create([=](){
//        m_node.at(0)->setPosition(pos);
//    }),NULL));
    m_scroll->addNumber(num);
    num+=30;
}

void StartScene::clickCall() {
    Audio->playEffect("music/TPS_PopUp.caf");
    m_layer = nullptr;
}

