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

Scene* StartScene::scene() {
    Scene* pScene = Scene::create();
    pScene->addChild(StartScene::create());
    return pScene;
}

bool StartScene::init() {
    if (!Layer::init()) {
        return false;
    }
    
    log("StartScene");
    initBackGround();
    
    return true;
}

void StartScene::initBackGround() {
    auto size = Director::getInstance()->getWinSize();
    
    auto bg = Sprite::create(BACK_GROUND_PNG);
    addChild(bg,kzOrderBackground);
    STsetPostion(bg,size/2);
    
    auto start = cocos2d::ui::Button::create(START_PNG);
    addChild(start,kzOrderUI);
    STsetPostion(start, size/2);
    start->addTouchEventListener(CC_CALLBACK_2(StartScene::touchDown, this));
}

void StartScene::touchDown(Ref* pSender,ui::Widget::TouchEventType type) {
    if (ui::Widget::TouchEventType::ENDED != type) return;
    
    Audio->playEffect("click.mp3");
    GameController::getInstace()->enterGameScene();
}


