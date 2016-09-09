//
//  Audio.cpp
//  meijia
//
//  Created by xcode31 on 16/9/2.
//
//

#include "Audio.hpp"
Audio* Audio::getInstance() {
    if (audio == NULL) {
        audio = new Audio();
        audio->init();
    }
    
    return audio;
}
Audio* Audio::audio = NULL;

bool Audio::init() {
    //初始化声音
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(C_LEFT.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(C_RIGHT.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(C_MIX.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(MOVE.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(DUMP.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(CLEANNEIL.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(CLEANBTN.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(MIXPROCESS.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(SMEAR.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(BLING.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(DUMPL.c_str());
    
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
    return true;
}

Audio::Audio() {
    
}

void Audio::release()
{
    if(audio != NULL)
    {
        delete audio;
        audio = NULL;
    }
}

void Audio::playBgm() {
    if (ISSOUNDOPEN) {
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    } else {
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
}

void Audio::playBgm(std::string path) {
    SimpleAudioEngine::getInstance()->playBackgroundMusic(path.c_str(), true);
}

void Audio::playEffect(std::string path) {
    if (ISEFFECTOPEN) {
        SimpleAudioEngine::getInstance()->playEffect(path.c_str());
    } else {
        SimpleAudioEngine::getInstance()->stopAllEffects();
    }
}
