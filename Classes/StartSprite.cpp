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

#include "StartSprite.hpp"
#include "Globle.hpp"
#include "UITools.h"


StartSprite* StartSprite::create(int row, int col) {
    auto star = new StartSprite();
    auto filename = star->getStarFilename();
    if (star && star->initWithFile(filename)) {
        star->setName(filename);
        star->autorelease();
        star->initAction(row, col);
        return star;
    }
    CC_SAFE_DELETE(star);
    return nullptr;
}

std::string StartSprite::getStarFilename() {
    std::string arrStar[] = {STAR_BLUE,STAR_GREEN,STAR_PURPLE,STAR_RED,STAR_YELLOW};
    
    int len = sizeof(arrStar)/sizeof(arrStar[0]) - 1;
    return arrStar[quickRandom(0, len)];
}

void StartSprite::initAction(int row, int col){
    int starSize = 72;
    setPosition(Vec2(36 + starSize * col, 1300));
    auto fallTime = row/5;
    auto fallAction = MoveTo::create(fallTime, Vec2(60 + starSize * col, 36 + starSize * row));
    runAction(fallAction);
}






