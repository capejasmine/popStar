//
//  GameScene.hpp
//  popStar
//
//  Created by huangwen on 16/2/23.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public Scene{
public:
    CREATE_FUNC(GameScene);
    
    static Scene* scene();
    
    virtual bool init();
private:
    
};

#endif /* GameScene_hpp */
