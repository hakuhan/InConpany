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
    Button *rmAds;        //广告按钮
    bool canSelectedMixButton;  //是否能够点击确定按钮
    bool isL1Animating;  //左边第一个是否在进行动画
    bool isL2Animating;  //左边第二个是否正在动画
    bool isRAnimating;  //右边是否正在动画
    bool isTAnimaitng;  //上边是否正在动画
    int numberOfBottle;     //记录瓶子的个数
    bottleColors colors;    //5个瓶子颜色
    Vector<Sprite *>seletecdBottle; //选中的瓶子
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
    void onClickYes();
    void onClickNo();
    void onClickNeilBtn();
    void showCenterBottleWithTag(int tag);
    void showNoticeAnimationBySprite(Sprite *sprite);
};

#endif /* CreateNailPolishScene_hpp */
