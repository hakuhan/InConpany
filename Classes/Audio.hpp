//
//  Audio.hpp
//  meijia
//
//  Created by xcode31 on 16/9/2.
//
//

#ifndef Audio_hpp
#define Audio_hpp

#include <stdio.h>
#include <cocos2d.h>
#include "DefaultHeader.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class Audio {
public:
    static Audio *getInstance();
    bool init();
    void release();
    void playBgm(std::string path);
    void playBgm();
    void playEffect(std::string path);
    Audio();
private:
    static Audio* audio;
};

#endif /* Audio_hpp */
