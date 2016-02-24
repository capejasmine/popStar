//
//  Appconfig.hpp
//  popStar
//
//  Created by huangwen on 16/2/23.
//
//

#ifndef Appconfig_hpp
#define Appconfig_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Globle.hpp"
USING_NS_CC;

typedef enum {
    kzOrderBackground = 1,
    kzOrderContent = 50,
    kzOrderUI = 100,
    kzOrderPopUp = 200
}LAYER_ZORDER;

void STsetPostion(Node* node,Vec2 pos){
    node->setPosition(pos);
    node->setScale(DESIGN_SCALE.x,DESIGN_SCALE.y);
}



#endif /* Appconfig_hpp */
