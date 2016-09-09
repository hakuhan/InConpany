//
//  DefaultHeader.h
//  meijia
//
//  Created by xcode31 on 16/8/22.
//
//

#ifndef DefaultHeader_h
#define DefaultHeader_h

#include <stdio.h>
#define SCREAN_SIZE Director::getInstance()->getVisibleSize()
#define TITLE_POSITION Vec2(30, SCREAN_SIZE.height-30)
#define UD UserDefault::getInstance()
#define ISSOUNDOPEN UD->getBoolForKey("isSoundOpen", true)
#define ISEFFECTOPEN UD->getBoolForKey("isEffectOpen", true)
#define SETSOUND(key) UD->setBoolForKey("isSoundOpen", key)
#define SETEFFECT(key) UD->setBoolForKey("isEffectOpen", key)

struct XXX{
    int a;
};

typedef struct XXX xx1;

enum Pptag{
    lYellow = 14,
    lBlack = 12,
    lBlue = 15,
    lPink=13,
    lWhite=11,
    rSlash = 23,
    rFlower = 22,
    rShap = 21,
    rHeart = 24,
    tSpecial = 31
};

struct selectedTag{
    int lFirstC;
    int lSecondC;
    int rChoice;
    int tChoice;
};

//5个瓶子所装的颜料
struct bottleColors {
    std::string bottle1;
    std::string bottle2;
    std::string bottle3;
    std::string bottle4;
    std::string bottle5;
};

const std::string BGM = "tAudio/bgm.mp3";
const std::string C_LEFT = "tAudio/click.mp3";
const std::string C_RIGHT = "tAudio/click.mp3";
const std::string C_MIX = "tAudio/clickMix.mp3";
const std::string MOVE = "tAudio/Move.mp3";
const std::string DUMP = "tAudio/dump.mp3";
const std::string DUMPL = "tAudio/DumpL.mp3";
const std::string CLEANBTN = "tAudio/cleanBtn.mp3";
const std::string CLEANNEIL = "tAudio/cleanNeils.mp3";
const std::string MIXPROCESS = "tAudio/making.mp3";
const std::string MIXRESULT = "tAudio/result.mp3";
const std::string SMEAR = "tAudio/neils.mp3";
const std::string BLING = "tAudio/Bling.mp3";

const std::string SOUNDBTN = "commonViews/bgmBtn.png";
const std::string SOUNDBTN_U = "commonViews/bgmBtn_u.png";
const std::string EFFECTBTN = "commonViews/effectBtn.png";
const std::string EFFECTBTN_U = "commonViews/effectBtn_u.png";

const std::string ISPURCHASE = "isPurchase";

#endif /* DefaultHeader_h */
