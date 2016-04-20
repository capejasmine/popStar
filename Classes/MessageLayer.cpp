//
//  MessageLayer.cpp
//  popStar
//
//  Created by huangwen on 16/4/19.
//
//

#include "MessageLayer.hpp"
#include "Appconfig.hpp"

#define  LAYER_BG       "popup/event_reward_cloud_RETINA.png"
#define  TEXT_ABOUT     "popup/event_reward_cloud_about_RETINA.png"
#define  TEXT_CLEAR     "popup/event_reward_cloud_clear_RETINA.png"
#define  TEXT_WARNING   "popup/event_reward_cloud__waring_RETINA.png"

MessageLaye* MessageLaye::create(kEventType type) {
    MessageLaye *ret = new MessageLaye();
    if (ret && ret->init(type))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool MessageLaye::init(kEventType type) {
    if (!Layer::init()) {
        return false;
    }
    auto size = Director::getInstance()->getWinSize();
    auto bg = Sprite::create(LAYER_BG);
    bg->setPosition(size/2);
    addChild(bg, kzOrderPopUp);
    bg->setScale(0);
    
    bg->runAction(ScaleTo::create(0.4f, 1));
    
    auto text = Sprite::create();
    if (type == kEventType::kAbout) {
        text->setTexture(TEXT_ABOUT);
    }
    else if(type == kEventType::kWorning)
    {
        text->setTexture(TEXT_WARNING);
    }
    else
    {
        text->setTexture(TEXT_CLEAR);
    }
    bg->addChild(text);
    text->setPosition(bg->getContentSize()/2);
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MessageLaye::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MessageLaye::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(MessageLaye::onTouchBegan, this);
    listener->onTouchCancelled = CC_CALLBACK_2(MessageLaye::onTouchBegan, this);
    
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

//touch event
bool MessageLaye::onTouchBegan(Touch *touch, Event *unused_event) {
    runAction(Sequence::create(ScaleTo::create(0.4, 0), CallFunc::create([=](){
        if(removeCall)
        {
            removeCall();
        }
        this->removeFromParent();
    }),NULL));
    return true;
}

void MessageLaye::onTouchMoved(Touch *touch, Event *unused_event) {}

void MessageLaye::onTouchEnded(Touch *touch, Event *unused_event) {
    
}
void MessageLaye::onTouchCancelled(Touch *touch, Event *unused_event) {}