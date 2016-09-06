//
//  PaintingNailsScene.hpp
//  meijia
//
//  Created by xcode31 on 16/8/24.
//
//

#ifndef PaintingNailsScene_hpp
#define PaintingNailsScene_hpp

#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "DefaultHeader.h"
#include "CreateNailPolishScene.hpp"

USING_NS_CC;
using namespace ui;

class PaintingNailsScene : Layer {
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(PaintingNailsScene);
    
private:
    bottleColors colors;
    bool isCleanBtnClicked; //判断清理按钮是否点击
    Vector<Sprite *> neils;
    std::string names[5];
    
    void onClickPolishBtn();
    void onClickCrossBtnWithTag(int tag);
    void onClickCleanBtn();
    void onClickResetBtn();
    void setBrushWithBottle(Sprite* bottle);
    void updateBottle();
};

#endif /* PaintingNailsScene_hpp */
