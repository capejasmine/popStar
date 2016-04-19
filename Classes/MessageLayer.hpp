//
//  MessageLayer.hpp
//  popStar
//
//  Created by huangwen on 16/4/19.
//
//

#ifndef MessageLayer_hpp
#define MessageLayer_hpp

#include "cocos2d.h"

USING_NS_CC;

enum kEventType{
    kWorning = 188,
    kAbout
};

class MessageLaye : public Layer {
public:
    
    static MessageLaye* create(kEventType type);
    
    virtual bool init(kEventType type);
    
    //touch event
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    
private:
    
};

#endif /* MessageLayer_hpp */
