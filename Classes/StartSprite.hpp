//
//  StartSprite.hpp
//  popStar
//
//  Created by huangwen on 16/2/24.
//
//

#ifndef StartSprite_hpp
#define StartSprite_hpp

#include "cocos2d.h"

USING_NS_CC;

enum kStarColorTag{
    kBlueTag = 456,
    kGreenTag,
    kPurpleTag,
    kRedTag,
    kYellowTag
};

class StartSprite : public Sprite {
public:
    
    static StartSprite* create(int row, int col);
    
    std::string getStarFilename();
    
    void initAction(int row, int col);
    
private:
    
};

#endif /* StartSprite_hpp */
