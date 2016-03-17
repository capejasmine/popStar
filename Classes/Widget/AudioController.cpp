//
//  AudioController.cpp
//  popStar
//
//  Created by huangwen on 16/3/14.
//
//

#include "AudioController.hpp"
#include "SimpleAudioEngine.h"

bool AudioController::m_tag = false;

using namespace CocosDenshion;

#define  GetAudioEnging     SimpleAudioEngine::getInstance()

AudioController* AudioController::instance = nullptr;

AudioController* AudioController::getInstance(){
    if (!instance) {
        instance = new AudioController();
    }
    return instance;
}

void AudioController::playEffect(std::string filename){
    GetAudioEnging->playEffect(filename.c_str());
}

void AudioController::playMuic(std::string filename) {
    GetAudioEnging->playBackgroundMusic(filename.c_str());
}

void AudioController::changeMode() {
    if(!m_tag){
        GetAudioEnging->setEffectsVolume(0);
        GetAudioEnging->setBackgroundMusicVolume(0);
        m_tag = true;
    }
    else
    {
        GetAudioEnging->setEffectsVolume(1);
        GetAudioEnging->setBackgroundMusicVolume(1);
        m_tag = false;
    }
}

