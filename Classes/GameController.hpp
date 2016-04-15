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
#include "Loading.hpp"
#include "LoadingLaeyr.hpp"

#define  xGam       GameController::getInstace()

enum KSceneType{
    kTagLoadingLayer = 111,
    kTagLoading,
    kTagStartScene,
    kTagGameScene
};

class GameController : public SingleTon<GameController>{
public:
    
    CC_SYNTHESIZE(int, mode, FallMode);
    
    void enterLoading();
    
    void enterLoadinglayer();
    
    void enterStartScene();
    
    void enterGameScene();
    
    KSceneType getCurrentSceneType();
    
    
private:
    
    
    KSceneType m_currentType;
};

#endif /* GameController_hpp */
