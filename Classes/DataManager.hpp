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

#define xData       DataManager::getInstace()

USING_NS_CC;

class DataManager : public SingleTon<DataManager>{
public:
    
    CC_SYNTHESIZE(bool, pass, PassRecord);
    
    void removeRecord();
    
    void saveToFile(StartSprite** m_starArr);
    
    std::string getTagFromNmae(std::string name);
    
    std::string getData();
    
    bool isExsitRecord();
    
    void initNote();
    
    std::string getNoteFromPlist();
    
private:
    std::string m_note;
    
    int m_pos = 0;
    
    int m_size;
};

#endif /* DataManager_hpp */
