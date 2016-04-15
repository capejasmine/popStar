//
//  Loading.cpp
//  popStar
//
//  Created by huangwen on 16/4/14.
//
//

#include "Loading.hpp"
#include "GameController.hpp"

Scene* Loading::scene(){
    Scene* pScene = Scene::create();
    pScene->addChild(Loading::create());
    return pScene;
}

bool Loading::init() {
    if (!Layer::init()) {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    
    auto bg = Sprite::create("loading/LogoKakao_Portrait_RETINA.png");
    bg->setPosition(winSize/2);
    addChild(bg);
    bg->setScale(0);
    
    
    bg->runAction(ScaleTo::create(0.5f, 1.0));
    
    this->scheduleOnce(schedule_selector(Loading::changeScene), 3.0);
    
    return true;
}

void Loading::changeScene(float dt) {
    xGam->enterLoadinglayer();
}
