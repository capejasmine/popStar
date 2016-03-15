//
//  DataManager.hpp
//  popStar
//
//  Created by huangwen on 16/3/15.
//
//

#ifndef DataManager_hpp
#define DataManager_hpp

#include "cocos2d.h"
#include "SingleTon.hpp"
#include "StartSprite.hpp"

USING_NS_CC;

class DataManager : public SingleTon<DataManager>{
public:
    
    void saveToFile(StartSprite** m_starArr);
    
    std::string getTagFromNmae(std::string name);
    
    std::string getData();
    
private:
    
};

#endif /* DataManager_hpp */
