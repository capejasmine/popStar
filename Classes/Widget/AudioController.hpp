//
//  AudioController.hpp
//  popStar
//
//  Created by huangwen on 16/3/14.
//
//

#ifndef AudioController_hpp
#define AudioController_hpp

#include "cocos2d.h"

#define Audio      AudioController::getInstance()

USING_NS_CC;

class AudioController : public Ref{
public:
    static AudioController* getInstance();
    
    void playEffect(std::string filename);
    
    void playMuic(std::string filename);
    
private:
    static AudioController* instance;
};

#endif /* AudioController_hpp */
