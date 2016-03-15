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

struct starData{
    int row;
    int col;
    std::string name;
};

class StartSprite : public Sprite {
public:
    
    static StartSprite* create(int row, int col);
    
    static StartSprite* createWithTag(int row, int col, int tag);
    
    std::string getStarFilename();
    
    std::string getStarFilenameWhihTag(int tag);
    
    void initAction(int row, int col);
    
    void setData(std::string name, int row, int col);
    
    void deadAction();
    
    starData getData();
    
    
    
private:
    starData m_data;
};

#endif /* StartSprite_hpp */
