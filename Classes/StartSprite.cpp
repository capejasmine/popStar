//
//  StartSprite.cpp
//  popStar
//
//  Created by huangwen on 16/2/24.
//
//

#define   STAR_BLUE         "star_b.png"
#define   STAR_GREEN        "star_g.png"
#define   STAR_PURPLE       "star_p.png"
#define   STAR_RED          "star_r.png"
#define   STAR_YELLOW       "star_y.png"

#define   STAR_DEAD_PARTICLE  "point_star.plist"

#include "StartSprite.hpp"
#include "Globle.hpp"
#include "UITools.h"


StartSprite* StartSprite::create(int row, int col) {
    auto star = new StartSprite();
    auto filename = star->getStarFilename();
    if (star && star->initWithFile(filename)) {
        star->setData(filename, row, col);
        star->autorelease();
        star->initAction(row, col);
        return star;
    }
    CC_SAFE_DELETE(star);
    return nullptr;
}

StartSprite* StartSprite::createWithTag(int row, int col, int tag) {
    if (tag == 0) {
        return nullptr;
    }else
    {
        auto star = new StartSprite();
        auto filename = star->getStarFilenameWhihTag(tag);
        if (star && star->initWithFile(filename)) {
            star->setData(filename, row, col);
            star->autorelease();
            star->initAction(row, col);
            return star;
        }
        CC_SAFE_DELETE(star);
        return nullptr;
    }
}

std::string StartSprite::getStarFilename() {
    std::string arrStar[] = {STAR_BLUE,STAR_GREEN,STAR_PURPLE,STAR_RED,STAR_YELLOW};
    
    int len = sizeof(arrStar)/sizeof(arrStar[0]) - 1;
    return arrStar[quickRandom(0, len)];
}

std::string StartSprite::getStarFilenameWhihTag(int tag) {
    switch (tag) {
        case 1:
            return STAR_BLUE;
            break;
        case 2:
            return STAR_GREEN;
            break;
        case 3:
            return STAR_PURPLE;
            break;
        case 4:
            return STAR_RED;
            break;
        case 5:
            return STAR_YELLOW;
            break;
        default:
            break;
    }
    CCASSERT(!tag, "dont exsit the tag picture");
    return nullptr;
}

void StartSprite::initAction(int row, int col){
    int starSize = 72;
    setPosition(Vec2(36 + starSize * col, 1300));
    auto fallTime = row/5;
    auto fallAction = MoveTo::create(fallTime, Vec2(60 + starSize * col, 36 + starSize * row));
    runAction(fallAction);
}

void StartSprite::setData(std::string name, int row, int col) {
    m_data.name = name;
    m_data.row = row;
    m_data.col = col;
}

starData StartSprite::getData() {
    return m_data;
}

void StartSprite::deadAction() {
    auto particle = ParticleSystemQuad::create(STAR_DEAD_PARTICLE);
    particle->setPosition(getContentSize()/2);
    addChild(particle);
    
    auto dead = Sequence::create(ScaleTo::create(0.4, 0), CallFunc::create([&](){
        this->removeFromParent();
    }),NULL);
    runAction(dead);
}




