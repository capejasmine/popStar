//
//  GameController.cpp
//  popStar
//
//  Created by huangwen on 16/2/24.
//
//

#include "GameController.hpp"

void GameController::enterStartScene() {
    m_currentType = KSceneType::kTagStartScene;
    
    if (Director::getInstance()->getRunningScene()) {
        Director::getInstance()->replaceScene(StartScene::scene());
    }
    else
    {
        Director::getInstance()->runWithScene(StartScene::scene());
    }
}

void GameController::enterGameScene() {
    m_currentType = KSceneType::kTagGameScene;
    
    if (Director::getInstance()->getRunningScene()) {
        Director::getInstance()->replaceScene(GameScene::scene());
    }
    else
    {
        Director::getInstance()->runWithScene(GameScene::scene());
    }
}

KSceneType GameController::getCurrentSceneType() {
    return m_currentType;
}