//
//  GameScene.cpp
//  popStar
//
//  Created by huangwen on 16/2/23.
//
//
#define   BACK_GROUND_PNG   "bg_main.png"
#define   STAR_COUNT        100;

#include "GameScene.hpp"
#include "AudioController.hpp"
#include "Appconfig.hpp"
#include "ScoreManager.hpp"
#include "GameController.hpp"
#include "DataManager.hpp"

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
    initBackGround();
    
    if(!xData->isExsitRecord()){
        initStar();
    }
    else{
        intStarWithRecord();
        m_score->setString(std::to_string(xScor->getScore()));
    }
    
    setCurrentTouchStar(nullptr);
    settouchTag(true);
    //Audio->playMuic("");
    
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
    
//    auto bg = Sprite::create(BACK_GROUND_PNG);
//    addChild(bg,kzOrderBackground);
//    STsetPostion(bg,size/2);
    auto pause = (Button*)(Helper::seekWidgetByName(m_root, "pause"));
    pause->addTouchEventListener(CC_CALLBACK_2(GameScene::touchDown, this));
    
    auto music = (Button*)(Helper::seekWidgetByName(m_root, "music"));
    music->addTouchEventListener(CC_CALLBACK_2(GameScene::touchDown, this));
    
    m_score = (Text*)(Helper::seekWidgetByName(m_root, "score"));
    m_score->setString("0");
    
    auto bg_particle = ParticleSystemQuad::create("bg_environment" + std::to_string(rand()%4) + ".plist");
    addChild(bg_particle,kzOrderPopUp);
    STsetPostion(bg_particle,Vec2(size.width/2,size.height));
    
    
    auto back = ui::Button::create("save&exit.png");
    back->addTouchEventListener(CC_CALLBACK_2(GameScene::touchDown, this));
    addChild(back,kzOrderUI);
    back->setPosition(Vec2(size.width/2,size.height));
    
}

void GameScene::initStar() {
    for (int row = 0; row < NUMX; row++) {
        for (int col= 0; col < NUMY; col++) {
            auto star = StartSprite::create(row, col);
            m_starArr[row * m_width + col] = star;
            addChild(star,kzOrderContent);
            m_countStar++;
        }
    }
}

void GameScene::intStarWithRecord() {
    std::string record = xData->getData();
    int pos = 0;
    
    for (int row = 0; row < NUMX; row++) {
        for (int col= 0; col < NUMY; col++) {
            int tag = record.at(pos++) - 48;
            auto star = StartSprite::createWithTag(row, col, tag);
            m_starArr[row * m_width + col] = star;
            if(star){
                addChild(star,kzOrderContent);
                m_countStar++;
            }
        }
    }
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event) {
    if (gettouchTag()) {  // 还没有消除 不能点击
    
    auto point = touch->getLocation();
        for (int row = 0; row < NUMX; row ++) {
            for (int col = 0; col <NUMY; col ++) {
                auto target = m_starArr[row * m_width + col];
                if(target){
                    if (target->getBoundingBox().containsPoint(point)) {
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
                        }
                        else
                        {
                            //第一次点击  判断  四周相同颜色star 加入队列
                            Audio->playEffect("select.mp3");
                            
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
    
    log("star = %s curr = %s ", star->getData().name.c_str(),getCurrentTouchStar()->getData().name.c_str());
    if (star->getData().name.compare(getCurrentTouchStar()->getData().name) == 0) {
        
        
        
        log(".................");
        for (auto s : sameColorList) {
        
            log("row = %d , col = %d ",s->getData().row,s->getData().col);
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
    
    auto time = sameColorList.size() - 1;   // 因为 执行循环动作 默认执行一次 所以要减一
    auto repeat = Repeat::create(Sequence::create(CallFunc::create([=](){
        auto it = sameColorList.back();
        sameColorList.pop_back();
        
        starData data = it->getData();
        it->deadAction();
        //cava->removeFromParent();
        m_starArr[data.row * m_width + data.col] = nullptr;
    }), DelayTime::create(0.08f),NULL), time);
    runAction(repeat);
    
    auto delay = CallFunc::create([=](){
        sameColorList.clear();
        cheakedColorList.clear();
        
        // 消除 后 检查 掉落
        this->cheakAndFallStar();
    });
    
    runAction(Sequence::create(repeat, delay,CallFunc::create([=](){
        this->cheakAndGameOver();
    }),NULL));
    
    xScor->addScore(sameColorList.size());
    m_score->setString(std::to_string(xScor->getScore()));
}

void GameScene::playBrokenEffect() {
    // 延时 播放 star 消失音效
    
    auto count = sameColorList.size();
    auto repeat = Repeat::create(Sequence::create(CallFunc::create([=](){
        Audio->playEffect("broken.mp3");
    }), DelayTime::create(0.05),NULL), count);
    runAction(repeat);
}

void GameScene::cheakAndFallStar() {
    for (int row = 0; row < m_width; row++) {
        for (int col = 0; col < m_height; col++) {
            auto target = m_starArr[row * m_width + col];
            
            if (target == nullptr) {
                log("target = %d %d",row,col);
                // 如果 目标 为空 那么 由他上面那个方块掉下补充
                StartSprite* temp = nullptr;
                int dest = row;
                do{
                    if (++dest < m_width ) {
                        log("temp = %d %d",dest,col);
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
                    log("temp : name = %s row = %d,col = %d",temp->getData().name.c_str(),temp->getData().row,temp->getData().col);
                    temp->runAction(MoveBy::create(0.2, Vec2(0, -(dest - row) * 72)));
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
                            temp_star->runAction(MoveBy::create(0.2, Vec2(-72 * (temp_col - col), 0)));
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
    log("cheakAndGameOver()  sameColorList.szie =   %ld", sameColorList.size() - m_countStar);
    if(sameColorList.size() - m_countStar < 1)  //  减去 每次遍历 添加的 m_countStar 个本体,  剩下的就是目前游戏中还 可以 消除的 队列数
    {
        log("gameOver");
        settouchTag(false);
        
        if (xScor->getScore() > xScor->getTaskScore(1)) {
            // 过关
            Audio->playEffect("fire.mp3");
            m_popLayer = PopLayer::create("");
            m_popLayer->setClickCall(CC_CALLBACK_0(GameScene::yesBtnCall, this), CC_CALLBACK_0(GameScene::noBtnCall, this));
            m_popLayer->setText("Are you sure quit the game?");
            addChild(m_popLayer,kzOrderPopUp,"pop");
        }
        else
        {
            Audio->playEffect("gameover.mp3");
        }
    }
    
    sameColorList.clear();
    cheakedColorList.clear();
    
}


void GameScene::saveData() {
    
    
    
}


void GameScene::touchDown(Ref* obj, ui::Widget::TouchEventType type) {
    if(ui::Widget::TouchEventType::ENDED != type) return;
    
    auto target = (Widget*)obj;
    std::string name = target->getName();
    
    if (name.compare("pause") == 0) {
        
    }
    else if (name.compare("music") == 0){
    
    }
    else
    {
        xData->saveToFile(m_starArr); // 保存 star 数据信息
        yesBtnCall();
    }
    
    Audio->playEffect("click.mp3");
}

void GameScene::yesBtnCall() {
    // 保存 退出游戏
    xScor->saveScore();
    xGam->enterStartScene();
}

void GameScene::noBtnCall() {
    m_popLayer->removeFromParent();
    m_popLayer = nullptr;
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event) {
    log("----touchMove----");
}
void GameScene::onTouchEnded(Touch *touch, Event *unused_event) {

}
void GameScene::onTouchCancelled(Touch *touch, Event *unused_event) {
    
}

