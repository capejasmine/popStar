//
//  Globle.cpp
//  popStar
//
//  Created by huangwen on 16/2/24.
//
//

#include "Globle.hpp"

Size DESIGN_SIZE = Size::ZERO;
Size REAL_SIZE = Size::ZERO;
Point DESIGN_SCALE = Point::ZERO;

void STsetPostion(Node* node,Vec2 pos){
    node->setPosition(pos);
    node->setScale(DESIGN_SCALE.x,DESIGN_SCALE.y);
}