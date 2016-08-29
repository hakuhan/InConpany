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
#define BOTTLENUMBER UserDefault::getInstance()->getIntegerForKey("numberOfBottle", 0)


struct XXX{
    int a;
};

typedef struct XXX xx1;

enum Pptag{
    lYellow = 11,
    lBlack = 12,
    lBlue = 13,
    lPink=14,
    lWhite=15,
    rSlash = 21,
    rFlower = 22,
    rShap = 23,
    rHeart = 24,
    tSpecial = 31
};

struct selectedTag{
    int lFirstC;
    int lSecondC;
    int rChoice;
    int tChoice;
    
    
    //    enum leftP{
    //        lPurple=11,
    //        lWhite=12,
    //        lRed=13,
    //        lBlack=14,
    //        lYellow=15
    //    };
    //    enum rightP{
    //        rYellow = 21,
    //        rPurple = 22,
    //        rBlue = 23,
    //        rGreen = 24
    //    };
    //    enum topP{
    //        tBlue = 31,
    //        tGreen = 32
    //    };
};

//5个瓶子所装的颜料
struct bottleColors {
    std::string bottle1;
    std::string bottle2;
    std::string bottle3;
    std::string bottle4;
    std::string bottle5;
};


#endif /* DefaultHeader_h */
