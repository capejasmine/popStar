//
//  NumberScroller.cpp
//  popStar
//
//  Created by huangwen on 16/4/7.
//
//

#include "NumberScroller.hpp"

NumberScroller* NumberScroller::create(int level){
    NumberScroller * ret = new NumberScroller();
    ret->setDigitalLevel(level);
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool NumberScroller::init() {
    if (!Node::init()) {
        return false;
    }
    
    Size screenSize = Director::getInstance()->getWinSize();
    
    for (int i = 0; i < m_level; i++) {
        auto node = Node::create();
        for (int j = 9; j >= 0; j--) {
            auto label = Label::createWithTTF(std::to_string(j), "Marker Felt.ttf", m_fontSize);
            label->setPosition(Vec2(screenSize.width/2 + i * m_fontSize, screenSize.height - (j+4) * m_fontSize));
            node->addChild(label);
        }
        auto label = Label::createWithTTF(std::to_string(0), "Marker Felt.ttf", m_fontSize);
        label->setPosition(Vec2(screenSize.width/2 + i * m_fontSize, screenSize.height - (10+4) * m_fontSize));
        node->addChild(label);
        
        addChild(node);
        m_scroller.push_back(node);
    }
   
    
    return true;
}

void NumberScroller::addNumber(int num) {
    int last_num = m_cur_num;
    m_cur_num += num;
    
    int tag = 3;
    
    while (last_num >= 10) {
        int time;
        for (int i = 1; i < 5; i++) {
            while(i){
                
                i--;
            }
        }
        
        last_num /= 10;
        tag--;
    }
}

void NumberScroller::setNumber(int tag, int time) {
    Size screenSize = Director::getInstance()->getWinSize();

    auto node = m_scroller.at(tag);
    auto action = Sequence::create(MoveBy::create(1/time, Vec2(0, m_fontSize)), CallFunc::create([=](){
        if (node->getPosition().y == 10 * m_fontSize) {
            node->setPositionY(0);
        }
    }),NULL);
    
    node->runAction(Repeat::create(action, time));
    
    
}

void NumberScroller::setDigitalLevel(int level) {
    m_level = level;
}

void NumberScroller::setFontSize(int size) {
    m_fontSize = size;
}


