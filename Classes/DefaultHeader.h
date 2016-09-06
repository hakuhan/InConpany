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
#define ISADDEXITS "isAddExists"
#define ISSOUNDOPEN UD->getBoolForKey("isSoundOpen", true)
#define SETSOUND(key) UD->setBoolForKey("isSoundOpen", key)

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

const std::string BGM = "tAudio/music.mp3";
const std::string C_LEFT = "tAudio/combo_1.mp3";
const std::string C_RIGHT = "tAudio/combo_2.mp3";
const std::string MOVE = "tAudio/select.mp3";
const std::string DUMP = "tAudio/readygo.mp3";
const std::string CLEAN = "tAudio/clean.mp3";
const std::string POP = "tAudio/pop.mp3";

#endif /* DefaultHeader_h */
