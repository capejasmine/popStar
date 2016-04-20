//
//  LoadingLaeyr.cpp
//  popStar
//
//  Created by huangwen on 16/2/23.
//
//

#include "LoadingLaeyr.hpp"
#include "GameController.hpp"
#include "cocostudio/CocoStudio.h"
#include "Appconfig.hpp"
#include "AudioController.hpp"

bool LoadingLaeyr::firstPlay = false;

Scene* LoadingLaeyr::scene(){
    Scene* pScene = Scene::create();
    pScene->addChild(LoadingLaeyr::create());
    return pScene;
}

bool LoadingLaeyr::init() {
    if (!Layer::init()) {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    
    auto bg = Sprite::create("loading/LogoEnfeel_Portrait_RETINA.png");
    bg->setPosition(winSize/2);
    addChild(bg, kzOrderBackground);
    
    this->scheduleOnce(schedule_selector(LoadingLaeyr::changeScene), 3.0);
    this->schedule(schedule_selector(LoadingLaeyr::playEffect), 0.6, 4, 0.3);
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("animation/loading.ExportJson");
    
    auto armature = Armature::create("loading");
    armature->getAnimation()->playWithIndex(0);
    armature->setPosition(winSize/2);
    addChild(armature, kzOrderContent);
    
    
    
    
    return true;
}

void LoadingLaeyr::playEffect(float dt) {
    
    Audio->playEffect("Media/Bird_droped.m4a");
    
}

void LoadingLaeyr::changeScene(float dt) {
    if(!firstPlay)
    {
        xGam->enterStartScene();
    }
    else
    {
        if(xGam->getCurrentSceneType() == KSceneType::kTagStartScene)
        {
            xGam->enterGameScene();
        }
        else
        {
            xGam->enterStartScene();
        }
    }
    firstPlay = true;
}