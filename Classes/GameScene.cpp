//
//  GameScene.cpp
//  popStar
//
//  Created by huangwen on 16/2/23.
//
//
#define   BACK_GROUND_PNG   "bg_main.png"


#include "GameScene.hpp"
#include "Appconfig.hpp"

GameScene::GameScene()
:m_starArr(NULL)
,m_width(0)
{}

GameScene::~GameScene(){
    free(m_starArr);
}


Scene* GameScene::scene() {
    Scene* pScene = Scene::create();
    pScene->addChild(GameScene::create());
    return pScene;
}

bool GameScene::init() {
    if (!Layer::init()) {
        return false;
    }
    log("GameScene");
    
    m_width = NUMX;
    m_height = NUMY;
    int arrSize = sizeof(StartSprite*) * m_width * m_height;
    m_starArr = (StartSprite**)malloc(arrSize);
    memset((void*)m_starArr, 0, arrSize);
    
    
    
    initBackGround();
    initStar();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan =  CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved =  CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded =  CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchCancelled =  CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void GameScene::initBackGround() {
    auto size = Director::getInstance()->getWinSize();
    
    auto bg = Sprite::create(BACK_GROUND_PNG);
    addChild(bg,kzOrderBackground);
    STsetPostion(bg,size/2);
    
}

void GameScene::initStar() {
    for (int row = 0; row < NUMX; row++) {
        for (int col= 0; col < NUMY; col++) {
            auto star = StartSprite::create(row, col);
            m_starArr[row * m_width + col] = star;
            addChild(star,kzOrderContent);
        }
    }
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event) {
    auto point = touch->getLocation();
    for (int row = 0; row < NUMX; row ++) {
        for (int col = 0; col <NUMY; col ++) {
            auto target = m_starArr[row * m_width + col];
            if (target->getBoundingBox().containsPoint(point)) {
                auto touchAction = Sequence::create(ScaleTo::create(0.1, 1.2), DelayTime::create(0.15), ScaleTo::create(0.1, 1.0),NULL);
                target->runAction(touchAction);
                return true;
            }
        }
    }
    
    
    return false;
}
void GameScene::onTouchMoved(Touch *touch, Event *unused_event) {
    log("----touchMove----");
}
void GameScene::onTouchEnded(Touch *touch, Event *unused_event) {

}
void GameScene::onTouchCancelled(Touch *touch, Event *unused_event) {
    
}

