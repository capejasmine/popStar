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
    setCurrentTouchStar(nullptr);
    
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
                // 判断 是否是第一次点击star
                if (getCurrentTouchStar() == target) {
                    // 第二次点击  消除 star 队列
                    this->removeSameColorStar();
                    
                    // 当前点击star 设置为空
                    setCurrentTouchStar(nullptr);
                }
                else
                {
                    //第一次点击  判断  四周相同颜色star 加入队列
                    setCurrentTouchStar(target);
                    this->cheakSameColorStar(target);
                    
                }
                setCurrentTouchStar(target);
                
                auto touchAction = Sequence::create(ScaleTo::create(0.1, 1.2), DelayTime::create(0.15), ScaleTo::create(0.1, 1.0),NULL);
                target->runAction(touchAction);
                return true;
            }
        }
    }
    
    
    return false;
}

void GameScene::cheakSameColorStar(StartSprite* star)  {
    // 判断四周(上下左右) 相同颜色的star
    
    
    cheakedColorList.push_back(star);
    
    // 4. 颜色不一样 return
    
    //top
    
    cheakFourSide(m_starArr[(star->getData().row + 1)* m_width + star->getData().col], kSideTag::kTop);
    
    //down
    
    cheakFourSide(m_starArr[(star->getData().row - 1)* m_width + star->getData().col], kSideTag::kDown);
    
    //left
    
    cheakFourSide(m_starArr[star->getData().row * m_width + star->getData().col - 1], kSideTag::kLeft);
    
    //right
    
    cheakFourSide(m_starArr[star->getData().row * m_width + star->getData().col + 1], kSideTag::kRight);
}

StartSprite* GameScene::cheakFourSide(StartSprite* star, kSideTag side) {
    // 1. 如果为空 return
    if (star == nullptr)
    {
        return nullptr;
    }
    
    // 2. 超过边界  return
        starData data = star->getData();
    if(data.row > 9 || data.row < 0 || data.col > 9 || data.col < 0)
    {
        return nullptr;
    }
    
    // 3. 已经检查过了 return
    for (auto s : cheakedColorList) {
        if (s == star) {
            return nullptr;
        }
    }
    
    cheakedColorList.push_back(star);
    
    if (star->getName().compare(getCurrentTouchStar()->getName()) == 0) {
        sameColorList.push_back(star);
        
        switch (side) {
            case kSideTag::kTop:
                return cheakFourSide(m_starArr[(star->getData().row + 1)* m_width + star->getData().col], kSideTag::kTop);
                break;
            case kSideTag::kDown:
                return cheakFourSide(m_starArr[(star->getData().row - 1)* m_width + star->getData().col], kSideTag::kTop);
                break;
            case kSideTag::kLeft:
                return cheakFourSide(m_starArr[star->getData().row * m_width + star->getData().col - 1], kSideTag::kTop);
                break;
            case kSideTag::kRight:
                return cheakFourSide(m_starArr[star->getData().row * m_width + star->getData().col + 1], kSideTag::kTop);
                break;
            default:
                break;
        }
    }
    else
    {
        return nullptr;
    }
    
}


void GameScene::removeSameColorStar() {
    
}



void GameScene::onTouchMoved(Touch *touch, Event *unused_event) {
    log("----touchMove----");
}
void GameScene::onTouchEnded(Touch *touch, Event *unused_event) {

}
void GameScene::onTouchCancelled(Touch *touch, Event *unused_event) {
    
}

