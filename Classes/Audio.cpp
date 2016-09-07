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
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("tAudio/music.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("tAudio/combo_1.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("tAudio/combo_2.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("tAudio/pop.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("tAudio/select.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("tAudio/readygo.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("tAudio/clear.mp3");
    
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
