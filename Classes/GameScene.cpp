//
//  GameScene.cpp
//  popStar
//
//  Created by huangwen on 16/2/23.
//
//

#include "GameScene.hpp"


Scene* GameScene::scene() {
    Scene* pScene = Scene::create();
    pScene->addChild(GameScene::create());
    return pScene;
}

bool GameScene::init() {
    if (!Scene::init()) {
        return false;
    }
    return true;
}