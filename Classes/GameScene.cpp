//
//  GameScene.cpp
//  popStar
//
//  Created by huangwen on 16/2/23.
//
//

#define   STAR_COUNT        100;
#define  TIMER_WAIT      6  //  6
#define   TIME            60   // 60


#include "GameScene.hpp"
#include "AudioController.hpp"
#include "Appconfig.hpp"
#include "ScoreManager.hpp"
#include "GameController.hpp"
#include "DataManager.hpp"
#include "UITools.h"
#include "PassLayer.hpp"
#include "PauseLayer.hpp"
#include "cocostudio/CocoStudio.h"

#define BACK_GROUND_PNG     "bg_main.png"
#define COMBOM              "combo/MultiplyNumber_"

#define COMBOM_TEXT         "combo/combo_landscape_RETINA.png"
#define TIMER_BG_1          "timer/timer_e_l_landscape_RETINA.png"
#define TIMER_BG_2          "timer/timer_e_r_landscape_RETINA.png"
#define TIMER_CONTENT_1     "timer/timer_f_l_landscape_RETINA.png"
#define TIMER_CONTENT_2     "timer/timer_f_r_landscape_RETINA.png"
#define TIMER_BG            "timer/timer_add_landscape_RETINA.png"

#define GAME_OVER           "public/StageTurnType_RETINA.png"

#define PROGRESS_BAR        "public/next_star_RETINA.png"
#define MESSAGE_BIRD        "public/t_pink_RETINA.png"
#define MESSAGE_TEXT_COMBO  "public/text_combo.png"
#define MESSAGE_TEXT_PASS   "public/text_pass.png"

bool GameScene::passMessage = false;

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
    
    m_root = GUIReader::getInstance()->widgetFromJsonFile("game.json");
    addChild(m_root, kzOrderBackground);
    
    m_width = NUMX;
    m_height = NUMY;
    m_countStar = 0;
    int arrSize = sizeof(StartSprite*) * m_width * m_height;
    m_starArr = (StartSprite**)malloc(arrSize);
    memset((void*)m_starArr, 0, arrSize);
    
    
    xScor->initScore();
    xScor->initLevel();
    xData->initNote();
    initBackGround();
    
    settouchTag(false);   // 动画中不能 点击
    
    if(!xData->isExsitRecord() || xData->getPassRecord()){
        initStar();
        xData->setPassRecord(false);
    }
    else{
        intStarWithRecord();
    }
    m_score->setString(std::to_string(xScor->getScore()));
    
    setCurrentTouchStar(nullptr);
    settouchTag(false);
    
    Audio->playMuic("music/InGameBGM.caf");
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan =  CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved =  CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded =  CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchCancelled =  CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->scheduleOnce(schedule_selector(GameScene::updateAnimation), 5.0);
    this->scheduleOnce(schedule_selector(GameScene::startAnimationOver), 5.0f);
    this->scheduleOnce(schedule_selector(GameScene::playAnimation), 0.1f);
    
    setDbScore(false);
    setBomb(false);
    
    passMessage = false;
    
    showTimer();
    return true;
}

void GameScene::playAnimation(float dt) {
    ArmatureDataManager::getInstance()->addArmatureFileInfo("animation/startAniamtion.ExportJson");
    Size winSize = Director::getInstance()->getWinSize();
    auto armature = Armature::create("startAniamtion");
    armature->getAnimation()->playWithIndex(0);
    addChild(armature, kzOrderPopUp);
    armature->setPosition(winSize/2);
    
    auto sun_light = (ImageView*)(Helper::seekWidgetByName(m_root, "sun_1"));
    auto sun_bg = (ImageView*)(Helper::seekWidgetByName(m_root, "sun_2"));
    auto aciton1 = RepeatForever::create(Sequence::create(MoveBy::create(30, Vec2(-50,20)),MoveBy::create(25, Vec2(50,-20)),NULL));
    auto aciton2 = RepeatForever::create(Sequence::create(MoveBy::create(30, Vec2(-50,20)),MoveBy::create(25, Vec2(50,-20)),NULL));
    sun_bg->runAction(aciton1);
    sun_light->runAction(aciton2);
    
    auto effect = Sequence::create(CallFunc::create([=](){
        Audio->playEffect("music/Number.caf");
    }), DelayTime::create(1.1),NULL);
    
    runAction(Sequence::create(Repeat::create(effect, 5), CallFunc::create([=](){
        Audio->playEffect("Media/Ready.m4a");
    }),NULL));
}

void GameScene::initBackGround() {
    auto size = Director::getInstance()->getWinSize();
    auto pause = (Button*)(Helper::seekWidgetByName(m_root, "pause"));
    pause->addTouchEventListener(CC_CALLBACK_2(GameScene::touchDown, this));
    
    auto quit = (Button*)(Helper::seekWidgetByName(m_root, "Button_17"));
    quit->addTouchEventListener(CC_CALLBACK_2(GameScene::touchDown, this));
    
    m_score = (Text*)(Helper::seekWidgetByName(m_root, "score"));
    m_score->setString("0");
    m_score->setColor(cocos2d::Color3B::BLACK);

    
    auto bg_particle = ParticleSystemQuad::create("bg_environment" + std::to_string(quickRandom(0, 3)) + ".plist");
    addChild(bg_particle,kzOrderPopUp);
    STsetPostion(bg_particle,Vec2(size.width/2,size.height));
    
    auto bar_bg = (Helper::seekWidgetByName(m_root, "bar"));
    
    m_progress = ProgressTimer::create(Sprite::create(PROGRESS_BAR));
    m_progress->setMidpoint(Point(0,0));
    m_progress->setType(cocos2d::ProgressTimer::Type::BAR);
    m_progress->setBarChangeRate(Vec2(0, 1));
    bar_bg->addChild(m_progress);
    m_progress->setPosition(Vec2(bar_bg->getContentSize()/2) - Vec2(0, 4));
    
 
}

void GameScene::initStar() {
    m_delay = 0;
    for (int row = 0; row < NUMX; row++) {
        for (int col= 0; col < NUMY; col++) {
            auto call = Sequence::create(DelayTime::create(m_delay),
                                         CallFunc::create([=](){
                auto star = StartSprite::create(row, col);
                m_starArr[row * m_width + col] = star;
                addChild(star,kzOrderContent);
                m_countStar++;
            }),NULL);
            runAction(call);
            m_delay += 0.05;
        }
    }
}

void GameScene::intStarWithRecord() {
    std::string record = xData->getData();
    m_pos = 0;
    m_delay = 0;
    
    for (int row = 0; row < NUMX; row++) {
        for (int col= 0; col < NUMY; col++) {
            auto call = Sequence::create(DelayTime::create(m_delay),
                                         CallFunc::create([=](){
                int tag = record.at(m_pos++) - 48;  // 获取到到 是字符
                auto star = StartSprite::createWithTag(row, col, tag);
                m_starArr[row * m_width + col] = star;
                if(star){
                    addChild(star,kzOrderContent);
                    m_countStar++;
                }

            }),NULL);
            runAction(call);
            m_delay += 0.05;
            
        }
    }
}

void GameScene::propsAction(std::string type) {
    if (type.compare("Mult") == 0) {
        setDbScore(true);
        this->scheduleOnce(schedule_selector(GameScene::doubleScore), 5.0);
        log("double score time over");
        
    }
    else
    {
        log("boom star!!!!!!!");
        setBomb(true);
        
        auto target = getCurrentTouchStar();
        auto data = target->getData();
        int row = data.row;
        int col = data.col;
        
        for (int i = 0; i < 10; i++) {
            auto target_row = m_starArr[i * m_width + col];
            auto target_col = m_starArr[row * m_width + i];
            if (target_row) {
                if (!inSameColorList(target_row)) {
                    sameColorList.push_back(target_row);
                }
            }
            
            if (target_col) {
                if (!inSameColorList(target_col)) {
                    sameColorList.push_back(target_col);
                }
            }
            
        }
        settouchTag(false);
        
    }
    
    removeSameColorStar();
    // 当前点击star 设置为空
    setCurrentTouchStar(nullptr);
}

void GameScene::doubleScore(float dt){
    setDbScore(false);
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event) {
    if (gettouchTag()) {  // 还没有消除 不能点击
    
    auto point = touch->getLocation();
        for (int row = 0; row < NUMX; row ++) {
            for (int col = 0; col <NUMY; col ++) {
                auto target = m_starArr[row * m_width + col];
                if(target){
                    if (target->getBoundingBox().containsPoint(point)) {
                        Audio->playbirdTouchEffect();
                        
                        // 判断 是否是第一次点击star
                        if (getCurrentTouchStar() == target || inSameColorList(target)) {
                            // 第二次点击  消除 star 队列  (在相同颜色列表中获取点击位置判断)
                            if(sameColorList.size() > 1) //  单个 的不能消除
                            {
                                settouchTag(false);
                                
                                this->playBrokenEffect();
                                this->removeSameColorStar();
                                
                                // 当前点击star 设置为空
                                setCurrentTouchStar(nullptr);
                            }
                            
                            log("%s",target->getName().c_str());
                            
                            if (target->getData().name.compare("Bomb") == 0) {
                                propsAction("Bomb");
                            }else if (target->getData().name.compare("Mult") == 0) {
                                propsAction("Mult");
                            }
                        }
                        else
                        {
                            //第一次点击  判断  四周相同颜色star 加入队列
//                            Audio->playEffect("select.mp3");
                            
                            // 若不为空
                            if(sameColorList.size() != 0)
                            {
                                for (auto cava : sameColorList) {
                                    auto action = ScaleTo::create(0.2, 1.0f);
                                    cava->runAction(action);
                                }
                            }
                            sameColorList.clear();
                            cheakedColorList.clear();
                            
                            setCurrentTouchStar(target);
                            this->cheakSameColorStar(target, true);
                            
                        }
                        //setCurrentTouchStar(target);
                        
                        //auto touchAction = Sequence::create(ScaleTo::create(0.1, 1.2), DelayTime::create(0.15), ScaleTo::create(0.1, 1.0),NULL);
                        //target->runAction(touchAction);
                        return true;
                    }
                }
            }
        }
    }
    
    
    return false;
}

bool GameScene::inSameColorList(StartSprite* star) { //判断 第二次点击是否在 已经检测过的 一样颜色的队列中 也可以消除
    for( auto s : sameColorList)
    {
        if (star == s) {
            return true;
        }
    }
    return false;
}

void GameScene::cheakSameColorStar(StartSprite* star,bool tag)  {
    if(tag) // tag区分 判断 还是 检查
    {
        // 递归调用 检查 star
        auto scaleAction = ScaleTo::create(0.2, 1.08f);
        star->runAction(scaleAction);
    }
    
    cheakedColorList.push_back(star);
    sameColorList.push_back(star);
    
    
    
    // 判断四周(上下左右) 相同颜色的star
    
    //      top
    
    if(star->getData().row + 1 <= 9)
    cheakFourSide(m_starArr[(star->getData().row + 1)* m_width + star->getData().col], kSideTag::kTop, tag);
    
    //      down
    if(star->getData().row - 1 >= 0)
    cheakFourSide(m_starArr[(star->getData().row - 1)* m_width + star->getData().col], kSideTag::kDown, tag);
    
    //      left
    if(star->getData().col - 1 >= 0)
    cheakFourSide(m_starArr[star->getData().row * m_width + star->getData().col - 1], kSideTag::kLeft, tag);
    
    //      right
    if(star->getData().col + 1 <= 9)
    cheakFourSide(m_starArr[star->getData().row * m_width + star->getData().col + 1], kSideTag::kRight, tag);
    
}

void GameScene::cheakFourSide(StartSprite* star, kSideTag side, bool tag) {
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
    
    //log("star = %s curr = %s ", star->getData().name.c_str(),getCurrentTouchStar()->getData().name.c_str());
    if (star->getData().name.compare(getCurrentTouchStar()->getData().name) == 0) {
        
        
        
        //log(".................");
        for (auto s : sameColorList) {
        
            //log("row = %d , col = %d ",s->getData().row,s->getData().col);
        }
        
        cheakSameColorStar(star, tag);  // 最后 简单的让我 恍然大悟
    }
    
}


void GameScene::removeSameColorStar() {
    setCurrentTouchStar(nullptr);
    log("--------removeSameColorStar--------");
//    for (auto cava : sameColorList) {
//        
//        starData data = cava->getData();
//        cava->deadAction();
//        //cava->removeFromParent();
//        m_starArr[data.row * m_width + data.col] = nullptr;
//    }
    // 延时 播放消失动作
    m_countStar -= sameColorList.size();
    
    auto count = sameColorList.size();
    
    showCombo(count);
    
    float time = 0.08;
    if (getBomb()) {
        time = 0;
    }
    
    auto repeat = Repeat::create(Sequence::create(CallFunc::create([=](){
        auto it = sameColorList.back();
        
        if(it)
        {
        sameColorList.pop_back();
        
        starData data = it->getData();
        it->deadAction();
        //cava->removeFromParent();
        m_starArr[data.row * m_width + data.col] = nullptr;
        }
    }), DelayTime::create(time),NULL), count);
    //runAction(repeat);
    
    //particle
    
//    auto particle = ParticleSystemQuad::create("point_star.plist");
//    particle->setPosition(pos);
//    addChild(particle);
    
    
    
    auto delay = CallFunc::create([=](){
        sameColorList.clear();
        cheakedColorList.clear();
        
        // 消除 后 检查 掉落
        this->cheakAndFallStar();
    });
    
    runAction(Sequence::create(repeat, delay,CallFunc::create([=](){
        this->cheakAndGameOver();
    }),NULL));
    
//    xScor->addScore(sameColorList.size());
//    m_score->setString(std::to_string(xScor->getScore()));
    m_last_score = xScor->getScore();
    xScor->addScore(sameColorList.size() * (getDbScore()? 2 : 1));
    this->schedule(schedule_selector(GameScene::updateScore));
    
    if (xScor->getScore() > xScor->getTaskScore() && !passMessage) {
        messageAction(kMessage::kPass);
        passMessage = true;
    }
    
    if (quickRandom(0, 5) == 0 && !comboMessage) {
        messageAction(kMessage::kCombo);
        comboMessage = true;
    }
}

void GameScene::playBrokenEffect() {
    // 延时 播放 star 消失音效
    
    auto count = sameColorList.size();
    auto repeat = Repeat::create(Sequence::create(CallFunc::create([=](){
        Audio->playEffect("music/garden_catch_bubbles_bottle.mp3");
    }), DelayTime::create(0.05),NULL), count);
    runAction(repeat);
}

void GameScene::cheakAndFallStar() {
    for (int row = 0; row < m_width; row++) {
        for (int col = 0; col < m_height; col++) {
            auto target = m_starArr[row * m_width + col];
            
            if (target == nullptr) {
                //log("target = %d %d",row,col);
                // 如果 目标 为空 那么 由他上面那个方块掉下补充
                StartSprite* temp = nullptr;
                int dest = row;
                do{
                    if (++dest < m_width ) {
                        //log("temp = %d %d",dest,col);
                        temp = m_starArr[dest * m_width + col];
                    }
                    else
                    {
                        // 如果超过上边界 还没找到 那么就跳出循环
                        break;
                    }
                    
                }while (temp == nullptr);
                
                if(temp != nullptr) //再次判断， 因为temp 也可能为空
                { // 交换 数据 并执行 动作
                    //log("temp : name = %s row = %d,col = %d",temp->getData().name.c_str(),temp->getData().row,temp->getData().col);
                    temp->runAction(MoveBy::create(0.2, Vec2(0, -(dest - row) * 67)));
                    temp->setData(temp->getData().name, row, col);
                    m_starArr[dest* m_width + col] = nullptr;
                    m_starArr[row* m_width + col] = temp;
                }
            }
            
        }
    }
    // 掉落后 检查是否需要 合并
    this->cheakAndCombineStar();
}


void GameScene::cheakAndCombineStar() {
    for (int col = 0; col < m_height; col++) {   // 因为 首先执行下落 所以底部为空 那么那一列就为空 所以只需 判断底部一行
        if(m_starArr[col] == nullptr)
        {   // 掉落后的 最底部 为空 执行合并
            if (col + 1 < m_height) {  // 判断是否为最后一列
                int temp_col = col;
                StartSprite* temp = nullptr;
                do{
                    if (++temp_col < m_height) {
                        temp = m_starArr[temp_col];  // temp 只是找出 那一列的底部不为空
                    }
                    else
                    {
                        break;
                    }
                }while(temp == nullptr);
                
                if(temp != nullptr){ //再次判断， 因为temp 也可能为空
                    // 开始 合并
                    for (int row = 0; row < m_width; row++) {
                        auto temp_star = m_starArr[row * m_width + temp_col];  // 逐个 移动
                        if(temp_star != nullptr)
                        {
                            temp_star->runAction(MoveBy::create(0.2, Vec2(-67 * (temp_col - col), 0)));
                            temp_star->setData(temp_star->getData().name, row, col);
                            m_starArr[row * m_width + temp_col] = nullptr;
                            m_starArr[row * m_width + col] = temp_star;
                        }
                    }
                }
                
            }
        }
    }
    
    settouchTag(true);
    
}

void GameScene::cheakAndGameOver() {
    for (int row = 0; row < NUMX; row++) {
        for (int col = 0; col < NUMY; col++) {
            auto target = m_starArr[row * m_width + col];
            if (target) {
                setCurrentTouchStar(target);
                cheakSameColorStar(target, false);
            }
        }
    }
    log("cheakAndGameOver()  sameColorList.size =   %ld", sameColorList.size() - m_countStar);
    if(sameColorList.size() - m_countStar < 1)  //  减去 每次遍历 添加的 m_countStar 个本体,  剩下的就是目前游戏中还 可以 消除的 队列数
    {
        log("gameOver");
        settouchTag(false);
        xScor->settlementScore(m_countStar);
        
        if (xScor->getScore() > xScor->getBestScore()) {
            xScor->setBestScore(xScor->getScore());
        }
    
        
        if (xScor->getScore() > xScor->getTaskScore()) {
            // 过关
            Audio->playEffect("music/Pass.caf");
            m_score->setString(std::to_string(xScor->getScore()));
            
            int def = xScor->getScore() - xScor->getTaskScore();
            int count = 0;
            if (def < 100) {
                count = 1;
            }else if (def > 100 && def < 500){
                count = 2;
            }
            else
            {
                count = 3;
            }
            
            xData->removeRecord();
            xScor->saveScore();
            xScor->addLevel();
            
            auto passLayer = PassLayer::create("popup.json", count, true);
            addChild(passLayer,kzOrderPopUp);
        }
        else
        {
            Audio->playEffect("music/TimeOver.caf");
            
            
            auto passLayer = PassLayer::create("popup.json", 0, false);
            addChild(passLayer,kzOrderPopUp);
            
        }
    }
    
    sameColorList.clear();
    cheakedColorList.clear();
    
    this->unschedule(schedule_selector(GameScene::updateAnimation));
    
}

void GameScene::showTimer() {
    auto size = Director::getInstance()->getWinSize();
    
    auto timer_center = Helper::seekWidgetByName(m_root, "timer_center");
    auto timer_bg = Helper::seekWidgetByName(m_root, "timer_bg");
    auto timer_t = Helper::seekWidgetByName(m_root, "timer");
    
    timer_center->setScale(0);
    timer_bg->setScale(0);
    timer_t->setScale(0);
    timer_center->runAction(ScaleTo::create(0.3, 0.5));
    timer_bg->runAction(ScaleTo::create(0.3, 0.5));
    timer_t->runAction(ScaleTo::create(0.3, 0.5));
    
    auto timer = Sprite::create(TIMER_BG);
    timer_center->addChild(timer,kzOrderUI);
    timer->setPosition(timer_center->getContentSize()/2);
    
    auto clipper_l = ClippingNode::create();
    clipper_l->setInverted(true);
    
    clipper_l->setAnchorPoint(Vec2(1, 0.5));
    timer->addChild(clipper_l);
    clipper_l->setPosition(timer->getContentSize()/2);
    
    auto content_l = Sprite::create(TIMER_CONTENT_1);
    content_l->setAnchorPoint(Vec2(1,0.5));
    content_l->setPosition(clipper_l->getContentSize()/2);
    clipper_l->addChild(content_l);
    
    auto stencil_l = Sprite::create(TIMER_BG_2);
    stencil_l->setAnchorPoint(Vec2(0,0.5));
    clipper_l->setStencil(stencil_l);
    
    ///////////////////////////////////////////////////////////////////////////////////////////////
    auto clipper_r = ClippingNode::create();
    clipper_r->setInverted(true);
    
    clipper_r->setAnchorPoint(Vec2(0, 0.5));
    timer->addChild(clipper_r);
    clipper_r->setPosition(timer->getContentSize()/2);
    
    
    auto content_r = Sprite::create(TIMER_CONTENT_2);
    content_r->setAnchorPoint(Vec2(0,0.5));
    content_r->setPosition(clipper_r->getContentSize()/2);
    clipper_r->addChild(content_r);
    
    auto stencil_r = Sprite::create(TIMER_BG_1);
    stencil_r->setAnchorPoint(Vec2(1,0.5));
    clipper_r->setStencil(stencil_r);
    
    
   
    stencil_r->runAction(Sequence::create(DelayTime::create(TIMER_WAIT), RotateBy::create(TIME, 180),NULL));
 
    stencil_l->runAction(Sequence::create(DelayTime::create(TIMER_WAIT + TIME), RotateBy::create(TIME, 180),NULL));
 
    timer_center->runAction(Sequence::create(DelayTime::create(TIMER_WAIT + TIME * 2), ScaleTo::create(0.3, 0),NULL));
    timer_bg->runAction(Sequence::create(DelayTime::create(TIMER_WAIT + TIME * 2), ScaleTo::create(0.3, 0),NULL));
    timer_t->runAction(Sequence::create(DelayTime::create(TIMER_WAIT + TIME * 2), ScaleTo::create(0.3, 0),NULL));

    // game over call
    auto call = CallFunc::create(CC_CALLBACK_0(GameScene::gameoverAction, this));
    
    runAction(Sequence::create(DelayTime::create(TIMER_WAIT + TIME * 2 + 0.01), call, NULL));
    
}

void GameScene::messageAction(kMessage msg) {
    
    
    auto size = Director::getInstance()->getWinSize();
    auto bird = Sprite::create(MESSAGE_BIRD);
    bird->setPosition(Vec2(-size.width/2, size.height/2));
    addChild(bird, kzOrderPopUp);
    
    auto message = Sprite::create();
    if(kMessage::kCombo == msg){
        message->setTexture(MESSAGE_TEXT_COMBO);
    }
    else
    {
        message->setTexture(MESSAGE_TEXT_PASS);
    }
    message->setAnchorPoint(Point(0,0));
    message->setScale(0);
    
    bird->addChild(message);
    message->setPosition(Vec2(0, bird->getContentSize().height/2));
    
    auto action = Sequence::create(MoveBy::create(1.0, Vec2(size.width - 150, 0)),
                                   Spawn::create(DelayTime::create(2.5f), CallFunc::create([=](){
        message->runAction(ScaleTo::create(0.4, 1));
        Audio->playEffect("Media/star_gain.m4a");
    }),NULL),
                                   MoveBy::create(1.0, Vec2(-size.width + 150, 0)), CallFunc::create([=](){
        bird->removeFromParent();
    }),NULL);
    
    bird->runAction(action);
}


void GameScene::gameoverAction() {
    auto size = Director::getInstance()->getWinSize();
    
    auto over = Sprite::create(GAME_OVER);
    over->setPosition(size/2);
    over->setScale(0);
    over->setAnchorPoint(Vec2(0.5, 0.5));
    over->runAction(ScaleTo::create(0.3, 1.0));
    this->addChild(over, kzOrderPopUp - 1);
    
    this->settouchTag(false);
    
    auto pause = (Button*)(Helper::seekWidgetByName(m_root, "pause"));
    auto quit = (Button*)(Helper::seekWidgetByName(m_root, "Button_17"));
    pause->setTouchEnabled(false);
    quit->setTouchEnabled(false);
    runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([=](){
        xGam->enterLoadinglayer();
    }),NULL));
    
    Audio->playEffect("music/TimeOver.caf");
}

void GameScene::showCombo(int count) {
    if (count < 2) {
        return;
    }
    
    std::string filename = COMBOM;
    if (count < 13) {
        filename = filename + std::to_string(count) + ".png";
    }
    else
    {
        filename = filename + "MAX.png";
    }
    Size winSize = Director::getInstance()->getWinSize();
    auto combom = Sprite::create(filename);
    combom->setPosition(winSize/2 + Size(90,0));
    addChild(combom, kzOrderContent);
    combom->setScale(0);
    combom->runAction(Sequence::create(ScaleTo::create(0.6, 2), CallFunc::create([=](){
        combom->removeFromParent();
    }),NULL));
    
    auto combomText = Sprite::create(COMBOM_TEXT);
    addChild(combomText, kzOrderContent);
    combomText->setScale(0);
    combomText->setPosition(Vec2(winSize/2 - Size(90,0)));
    combomText->runAction(Sequence::create(ScaleTo::create(0.6, 1.4), CallFunc::create([=](){
        combomText->removeFromParent();
    }),NULL));
}


void GameScene::touchDown(Ref* obj, ui::Widget::TouchEventType type) {
    if(ui::Widget::TouchEventType::ENDED != type) return;
    
    auto target = (Widget*)obj;
    std::string name = target->getName();
    
    Audio->playEffect("Media/ButtonClick.m4a");
    
    if (name.compare("pause") == 0) {

        auto pauseLayer = PauseLayer::create("pause.json");
        pauseLayer->setMenuClickCall(CC_CALLBACK_0(GameScene::yesBtnCall, this));
        addChild(pauseLayer,kzOrderPopUp);
        
//        auto target = m_starArr[5 * NUMX + 5];
//        target->changeAnimation();
//        m_countStar -= 1;
        
        
    }
    else if (name.compare("music") == 0){
        Audio->changeMode();
    }
    else
    {
        m_popLayer = PopLayer::create("quit.json");
        m_popLayer->setClickCall(CC_CALLBACK_0(GameScene::yesBtnCall, this), CC_CALLBACK_0(GameScene::noBtnCall, this));
        m_popLayer->setText("Are you sure quit the game?");
        addChild(m_popLayer,kzOrderPopUp,"pop");
    }
    
}

void GameScene::yesBtnCall() {
    // 保存 退出游戏
    xData->saveToFile(m_starArr); // 保存 star 数据信息
    xScor->saveScore();
    //xScor->addLevel();
    xGam->enterLoadinglayer();
}

void GameScene::noBtnCall() {
    m_popLayer->removeFromParent();
    m_popLayer = nullptr;
}

void GameScene::updateAnimation(float dt) {
    m_delay = 0.5;
    
    for (int row = 0; row < NUMX; row++) {
        for (int col = 0; col < NUMY; col++) {
            auto star = m_starArr[row * m_width + col];
            if(star){
                auto jump = Sequence::create(DelayTime::create(m_delay), MoveBy::create(0.15f, Vec2(0, 10)), MoveBy::create(0.15f, Vec2(0, -10)),NULL);
                star->runAction(jump);
                m_delay += 0.05;
            }
        }
    }
}

void GameScene::updateScore(float dt) {
    
    int score = xScor->getScore();
    
    m_cur_score = m_last_score++;
    
    if (m_last_score != score) {
        m_score->setString(std::to_string(m_cur_score));
        if(m_progress->getPercentage() < 100){
            m_progress->setPercentage((float)m_cur_score/(float)xScor->getTaskScore() * 100);
            Audio->playEffect("Media/ScoreUp.m4a");
        }
    }
    else
    {
        m_score->setString(std::to_string(score));
        if(m_progress->getPercentage() < 100){
            m_progress->setPercentage((float)score/(float)xScor->getTaskScore() * 100);
        }
        unschedule(schedule_selector(GameScene::updateScore));
    }

}

void GameScene::startAnimationOver(float dt) {
    settouchTag(true);
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event) {
    log("----touchMove----");
}
void GameScene::onTouchEnded(Touch *touch, Event *unused_event) {

}
void GameScene::onTouchCancelled(Touch *touch, Event *unused_event) {
    
}

