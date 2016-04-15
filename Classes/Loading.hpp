//
//  Loading.hpp
//  popStar
//
//  Created by huangwen on 16/4/14.
//
//

#ifndef Loading_hpp
#define Loading_hpp

#include <cocos2d.h>

USING_NS_CC;

class Loading: public Layer{
public:
    CREATE_FUNC(Loading);
    
    static Scene* scene();
    
    virtual bool init();
private:
    void changeScene(float dt);
};

#endif /* Loading_hpp */
