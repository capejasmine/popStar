//
//  GameController.cpp
//  popStar
//
//  Created by huangwen on 16/2/24.
//
//

#include "GameController.hpp"

void GameController::enterLoading() {
    m_currentType = KSceneType::kTagLoading;
    
    if (Director::getInstance()->getRunningScene()) {
        Director::getInstance()->replaceScene(Loading::scene());
    }
    else
    {
        Director::getInstance()->runWithScene(Loading::scene());
    }
}

void GameController::enterLoadinglayer() {
    m_currentType = KSceneType::kTagLoadingLayer;
    
    if (Director::getInstance()->getRunningScene()) {
        Director::getInstance()->replaceScene(TransitionFade::create(0.4, LoadingLaeyr::scene(), cocos2d::Color3B::WHITE));
    }
    else
    {
        Director::getInstance()->runWithScene(TransitionFade::create(0.4, LoadingLaeyr::scene(), cocos2d::Color3B::WHITE));
    }
}

void GameController::enterStartScene() {
    m_currentType = KSceneType::kTagStartScene;
    
    if (Director::getInstance()->getRunningScene()) {
        Director::getInstance()->replaceScene(TransitionFade::create(0.4, StartScene::scene(), cocos2d::Color3B::WHITE));
    }
    else
    {
        Director::getInstance()->runWithScene(TransitionFade::create(0.4, StartScene::scene(), cocos2d::Color3B::WHITE));
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

