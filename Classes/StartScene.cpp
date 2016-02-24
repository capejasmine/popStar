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
    
    
}


