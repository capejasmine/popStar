//
//  StartSprite.hpp
//  popStar
//
//  Created by huangwen on 16/2/24.
//
//

#ifndef PropsSprite_hpp
#define PropsSprite_hpp

#include "cocos2d.h"

USING_NS_CC;



struct starData{
    int row;
    int col;
    std::string name;
};

class PropsSprite : public Sprite {
public:
    
    static PropsSprite* create(int row, int col);
    
    static PropsSprite* createWithTag(int row, int col, int tag);
    
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
