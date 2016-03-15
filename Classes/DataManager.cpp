//
//  DataManager.cpp
//  popStar
//
//  Created by huangwen on 16/3/15.
//
//

#include "DataManager.hpp"

void DataManager::saveToFile(StartSprite** m_starArr) {
    std::string data;
    
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            auto target = m_starArr[row * 10 + col];
            if (target) {
                data.append((getTagFromNmae(target->getData().name)));
            }
            else
            {
                data.append("0");
            }
        }
    }
    
    Value value =  Value(data);
    
    ValueMap map;
    map["data"] = value;
    auto path = FileUtils::getInstance()->getWritablePath();
    auto fullPath = path + "/Data";
    FileUtils::getInstance()->writeToFile(map, fullPath);
}

std::string DataManager::getTagFromNmae(std::string name) {
    if (name.compare("star_b.png") == 0) {
        return "1";
    }else if (name.compare("star_g.png") == 0){
        return "2";
    }else if (name.compare("star_p.png") == 0){
        return "3";
    }else if (name.compare("star_r.png") == 0){
        return "4";
    }else{
        return "5";
    }
}


std::string DataManager::getData() {
    auto path = FileUtils::getInstance()->getWritablePath() + "/Data";
    bool exist = FileUtils::getInstance()->isFileExist(path);
    
    if (exist) {
        auto map = FileUtils::getInstance()->getValueMapFromFile(path);
        std::string data = map["data"].asString();
        
        return data;
    }
    CCASSERT(!exist, "----the path is wrong or the file is not exist!");
    return nullptr;
}


