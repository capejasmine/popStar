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
                data.append((getTagFromNmae(target->getData().name))); // 将star信息以tag 的形式追加到 string中
            }
            else
            {
                data.append("0");
            }
        }
    }
    //  构造一个valuemap 然后 保存在 指定 路径
    Value value =  Value(data);
    
    ValueMap map;
    map["data"] = value;
    auto path = FileUtils::getInstance()->getWritablePath();
    auto fullPath = path + "data.plist";
    
    log("----path = %s", fullPath.c_str());
    FileUtils::getInstance()->writeToFile(map, fullPath);
}

std::string DataManager::getTagFromNmae(std::string name) {
    name = name.substr(0,4);
    if (name.compare("sb_b") == 0) {
        return "1";
    }else if (name.compare("sb_p") == 0){
        return "2";
    }else if (name.compare("sb_r") == 0){
        return "3";
    }else if (name.compare("sb_v") == 0){
        return "4";
    }else{
        return "5";
    }
}


std::string DataManager::getData() {
    auto path = FileUtils::getInstance()->getWritablePath() + "data.plist";
    bool exist = FileUtils::getInstance()->isFileExist(path);
    
    // 查看文件是否存在
    if (exist) {
        auto map = FileUtils::getInstance()->getValueMapFromFile(path);
        std::string data = map["data"].asString();
        
        return data;
    }
    CCASSERT(!exist, "----the path is wrong or the file is not exist!");
    return nullptr;
}

bool DataManager::isExsitRecord() {
    auto path = FileUtils::getInstance()->getWritablePath() + "data.plist";
    return FileUtils::getInstance()->isFileExist(path);
}

void DataManager::removeRecord() {
    auto path = FileUtils::getInstance()->getWritablePath() + "data.plist";
    bool exist = FileUtils::getInstance()->isFileExist(path);
    
    // 查看文件是否存在
    if (exist) {
        std::remove(path.c_str());
    }
}



