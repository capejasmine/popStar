//
//  GameController.hpp
//  popStar
//
//  Created by huangwen on 16/2/24.
//
//

#ifndef GameController_hpp
#define GameController_hpp

#include "StartScene.hpp"
#include "GameScene.hpp"
#include "SingleTon.hpp"

enum KSceneType{
    kTagStartScene = 111,
    kTagGameScene
};

class GameController : public SingleTon<GameController>{
public:
    
    void enterStartScene();
    
    void enterGameScene();
    
    KSceneType getCurrentSceneType();
    
private:
    
    
    KSceneType m_currentType;
};

#endif /* GameController_hpp */
