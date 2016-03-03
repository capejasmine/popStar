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
            if(target){
                if (target->getBoundingBox().containsPoint(point)) {
                    // 判断 是否是第一次点击star
                    if (getCurrentTouchStar() == target || inSameColorList(target)) {
                        // 第二次点击  消除 star 队列  (在相同颜色列表中获取点击位置判断)
                        this->removeSameColorStar();
                        
                        // 当前点击star 设置为空
                        setCurrentTouchStar(nullptr);
                    }
                    else
                    {
                        //第一次点击  判断  四周相同颜色star 加入队列
                        
                        // 若不为空
                        if(sameColorList.size() != 0)
                        {
                            auto action = ScaleTo::create(0.2, 1.0f);
                            for (auto cava : sameColorList) {
                                cava->runAction(action);
                            }
                        }
                        sameColorList.clear();
                        cheakedColorList.clear();
                        
                        setCurrentTouchStar(target);
                        this->cheakSameColorStar(target);
                        
                    }
                    setCurrentTouchStar(target);
                    
                    //auto touchAction = Sequence::create(ScaleTo::create(0.1, 1.2), DelayTime::create(0.15), ScaleTo::create(0.1, 1.0),NULL);
                    //target->runAction(touchAction);
                    return true;
                }
            }
        }
    }
    
    
    return false;
}

bool GameScene::inSameColorList(StartSprite* star) {
    for( auto s : sameColorList)
    {
        if (star == s) {
            return true;
        }
    }
    return false;
}

void GameScene::cheakSameColorStar(StartSprite* star)  {
    
    
    
    cheakedColorList.push_back(star);
    sameColorList.push_back(star);
    
    
    // 判断四周(上下左右) 相同颜色的star
    
    //      top
    
    if(star->getData().row + 1 <= 9)
    cheakFourSide(m_starArr[(star->getData().row + 1)* m_width + star->getData().col], kSideTag::kTop);
    
    //      down
    if(star->getData().row - 1 >= 0)
    cheakFourSide(m_starArr[(star->getData().row - 1)* m_width + star->getData().col], kSideTag::kDown);
    
    //      left
    if(star->getData().col - 1 >= 0)
    cheakFourSide(m_starArr[star->getData().row * m_width + star->getData().col - 1], kSideTag::kLeft);
    
    //      right
    if(star->getData().col + 1 <= 9)
    cheakFourSide(m_starArr[star->getData().row * m_width + star->getData().col + 1], kSideTag::kRight);
    
}

void GameScene::cheakFourSide(StartSprite* star, kSideTag side) {
    // 1. 如果为空 return
    if (star == nullptr)
    {
        return;
    }
    
    // 2. 超过边界  return
        starData data = star->getData();
    if(data.row > 9 || data.row < 0 || data.col > 9 || data.col < 0)
    {
        return;
    }
    
    // 3. 已经检查过了 return
    for (auto s : cheakedColorList) {
        if (s == star) {
            return;
        }
    }
    
    //cheakedColorList.push_back(star);
    
    // 4. 颜色不一样 return
    
    log("star = %s curr = %s ", star->getData().name.c_str(),getCurrentTouchStar()->getData().name.c_str());
    if (star->getData().name.compare(getCurrentTouchStar()->getData().name) == 0) {
        
        
        auto scaleAction = ScaleTo::create(0.2, 1.08f);
        star->runAction(scaleAction);
        
        log(".................");
        for (auto s : sameColorList) {
        
            log("row = %d , col = %d ",s->getData().row,s->getData().col);
        }
        
        switch (side) {
            case kSideTag::kTop:{
                if(star->getData().row + 1 <= 9)
                    cheakSameColorStar(star);
                else
                    return;
            }
                break;
            case kSideTag::kDown:{
                if(star->getData().row - 1 >= 0)
                    cheakSameColorStar(star);
                else
                    return;
            }
                break;
            case kSideTag::kLeft:{
                if(star->getData().col - 1 >= 0)
                    cheakSameColorStar(star);
                else
                    return;
            }
                break;
            case kSideTag::kRight:{
                if(star->getData().col + 1 <= 9)
                    cheakSameColorStar(star);
                else
                    return;
            }
                break;
            default:
                break;
        }
    }
    
}


void GameScene::removeSameColorStar() {
    setCurrentTouchStar(nullptr);
    log("--------removeSameColorStar--------");
    for (auto cava : sameColorList) {
        starData data = cava->getData();
        cava->removeFromParent();
        m_starArr[data.row * m_width + data.col] = nullptr;
    }
    
    sameColorList.clear();
    cheakedColorList.clear();
    
    // 消除 后 检查 掉落
    this->cheakAndFallStar();
}

void GameScene::cheakAndFallStar() {
    for (int row = 0; row < m_width; row++) {
        for (int col = 0; col < m_height; col++) {
            auto target = m_starArr[row * m_width + col];
            if (target == nullptr) {
                // 如果 目标 为空 那么 由他上面那个方块掉下补充
                if (row + 1 < m_height) {
                    auto temp = m_starArr[(row + 1) * m_width + col];
                    
                    if(temp != nullptr){
                        target = temp;
                        // action
                        
//                        auto action = MoveBy::create(0.1f, Vec2(0, -72));
//                        temp->runAction(action);
                        
                        temp = nullptr;
                    }
                }
            }
            
            
            
            
        }
    }
}



void GameScene::onTouchMoved(Touch *touch, Event *unused_event) {
    log("----touchMove----");
}
void GameScene::onTouchEnded(Touch *touch, Event *unused_event) {

}
void GameScene::onTouchCancelled(Touch *touch, Event *unused_event) {
    
}

