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

#define     NUMX    10
#define     NUMY    10

#define     POPSTAR_SCORE        "popstar_core"


#endif /* Appconfig_hpp */
