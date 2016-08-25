//
//  CreateNailPolishScene.hpp
//  meijia
//
//  Created by xcode31 on 16/8/19.
//
//

#ifndef CreateNailPolishScene_hpp
#define CreateNailPolishScene_hpp

#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "DefaultHeader.h"

USING_NS_CC;
using namespace ui;


class CreateNailPolishScene : cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(CreateNailPolishScene);
    
private:
    selectedTag choices;  //标记选择
    bool canSelectedMixButton;  //是否能够点击确定按钮
    int numberOfBottle;     //记录瓶子的个数
    bottleColors colors;    //5个瓶子颜色
    
    void onClickColor(Button* btn, Vec2 movePosition);
    Sprite* createSpriteWithTagAndPosition(int tag, Vec2 position);
    void showNotice();
    void showLeftAndTopButtonClickedAnimationsWithSpriteAndPositionAndButtton(Sprite *sprite, Vec2 movePosition, Button *btn);
    void showRightButtonClickedAnimationsWithSpriteAndPositionAndButton(Sprite *sprite, Vec2 movePosition, Button *btn);
    void onClickMixButton();
    
    void clearSprite(Sprite* s, Button *btn);
    void updateCustom(float dt);
    void chechStateOfMixButton();
    bool isBottleFull();
    void showBottleFullNotice();
    void onClickYes();
    void onClickNo();
    void onClickNeilBtn();
};

#endif /* CreateNailPolishScene_hpp */
