//
//  StartSprite.cpp
//  popStar
//
//  Created by huangwen on 16/2/24.
//
//

#define   STAR_BLUE         "sb_b"
#define   STAR_GREEN        "sb_p"
#define   STAR_PURPLE       "sb_r"
#define   STAR_RED          "sb_v"
#define   STAR_YELLOW       "sb_w"

#define   STAR_DEAD_PARTICLE  "point_star.plist"
#define   EFFECT_CIRCLE       "effect/effect_pop_circle_RETINA.png"
#define   EFFECT_CENTER       "effect/effect_pop_center_RETINA.png"

#include "StartSprite.hpp"
#include "Globle.hpp"
#include "UITools.h"
#include "GameController.hpp"


StartSprite* StartSprite::create(int row, int col) {
    auto star = new StartSprite();
    auto filename = star->getStarFilename();
    if (star && star->initWithFile(filename)) {
        star->setData(filename.substr(0,4), row, col);
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
            star->setData(filename.substr(0,4), row, col);
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
    return (string(arrStar[quickRandom(0, len)]) + std::to_string(quickRandom(1, 4)) +".png");
}

std::string StartSprite::getStarFilenameWhihTag(int tag) {
    switch (tag) {
        case 1:
            return STAR_BLUE + std::to_string(quickRandom(1, 4)) +".png";
            break;
        case 2:
            return STAR_GREEN + std::to_string(quickRandom(1, 4)) +".png";
            break;
        case 3:
            return STAR_PURPLE + std::to_string(quickRandom(1, 4)) +".png";
            break;
        case 4:
            return STAR_RED + std::to_string(quickRandom(1, 4)) +".png";
            break;
        case 5:
            return STAR_YELLOW + std::to_string(quickRandom(1, 4)) +".png";
            break;
        default:
            break;
    }
    CCASSERT(!tag, "dont exsit the tag picture");
    return nullptr;
}

void StartSprite::initAction(int row, int col){
    int starSize = 67;
    setPosition(Vec2(36 + starSize * col, 1330));
    //   row/5     0     1.2
    int mode = xGam->getFallMode();
    float  fallTime;
    switch (mode) {
        case 0:
            fallTime = 0;
            break;
        case 1:
            fallTime = 1.2;
            break;
        case 2:
            fallTime = row/5;
            break;
        default:
            break;
    }
    auto fallAction = MoveTo::create(fallTime, Vec2(60 + starSize * col, 57 + starSize * row));
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
    
//    auto particle = ParticleSystemQuad::create(STAR_DEAD_PARTICLE);
//    particle->setPosition(getContentSize()/2);
//    addChild(particle);
    
    
    auto circle = Sprite::create(EFFECT_CIRCLE);
    circle->setPosition(getContentSize()/2);
    addChild(circle);
    
    circle->runAction(Sequence::create(ScaleTo::create(0.4, 0.15), CallFunc::create([=](){
        auto center = Sprite::create(EFFECT_CENTER);
        circle->setTexture(center->getTexture());
        circle->setScale(1.0);
    }),NULL));
    
    auto dead = Sequence::create(ScaleTo::create(0.4, 0.15), Spawn::create(MoveTo::create(0.5, Vec2(620,1180)), FadeOut::create(0.5), NULL),CallFunc::create([&](){
        this->removeFromParent();
    }),NULL);
    runAction(dead);
}




