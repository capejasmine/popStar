//
//  StartScene.hpp
//  popStar
//
//  Created by huangwen on 16/2/23.
//
//

#ifndef StartScene_hpp
#define StartScene_hpp

#include "cocos2d.h"

USING_NS_CC;

class StartScene : public Scene{
public:
    
    CREATE_FUNC(StartScene);
    
    static Scene* scene();
    
    virtual bool init();
private:
    
};

#endif /* StartScene_hpp */
