//
//  StartScene.cpp
//  popStar
//
//  Created by huangwen on 16/2/23.
//
//

#include "StartScene.hpp"

Scene* StartScene::scene() {
    Scene* pScene = Scene::create();
    pScene->addChild(StartScene::create());
    return pScene;
}

bool StartScene::init() {
    if (!Scene::init()) {
        return false;
    }
    
    
    
    
    
    
    
    return true;
}