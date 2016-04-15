//
//  LoadingLaeyr.hpp
//  popStar
//
//  Created by huangwen on 16/2/23.
//
//

#ifndef LoadingLaeyr_hpp
#define LoadingLaeyr_hpp

#include <cocos2d.h>

USING_NS_CC;

class LoadingLaeyr: public Layer{
public:
    CREATE_FUNC(LoadingLaeyr);
    
    static Scene* scene();
    
    virtual bool init();
    
    void changeScene(float dt);
private:
    
    
    static bool firstPlay;
};

#endif /* LoadingLaeyr_hpp */
