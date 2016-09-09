//
//  CreateNailPolishScene.cpp
//  meijia
//
//  Created by xcode31 on 16/8/19.
//
//

#include "CreateNailPolishScene.hpp"
#include "ui/CocosGUI.h"
#include "DefaultHeader.h"
#include "cocostudio/CocoStudio.h"
#include "PaintingNailsScene.hpp"
#include <stdlib.h>
#include "Audio.hpp"
#include "CommonView.hpp"

USING_NS_CC;
using namespace ui;

Scene* CreateNailPolishScene::createScene(){
    auto scene = Scene::create();
    auto layer = CreateNailPolishScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool CreateNailPolishScene::init() {
    if (!Layer::init()) {
        return false;
    }
    //初始化数据
    choices = {0, 0, 0, 0};
    canSelectedMixButton = false;
    colors.bottle1 = UD->getStringForKey("b1Color", "0");
    colors.bottle2 = UD->getStringForKey("b2Color", "0");
    colors.bottle3 = UD->getStringForKey("b3Color", "0");
    colors.bottle4 = UD->getStringForKey("b4Color", "0");
    colors.bottle5 = UD->getStringForKey("b5Color", "0");
    seletecdBottle = Vector<Sprite *>();
    
    auto node = CSLoader::createNodeWithVisibleSize("game/createNeilpolish.csb");
    auto bg = (Layout *)(node->getChildByName("bg"));
    this->addChild(bg);
    auto pot = bg->getChildByName("pBg")->getChildByName("Pot");
    auto potPosition = pot->convertToWorldSpace(pot->getPosition());
    potPosition = Vec2(potPosition.x-pot->getContentSize().width, potPosition.y);
    //顶部按钮
    auto neilBtn = (Button *)(node->getChildByName("neil_button"));
    neilBtn->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickNeilBtn, this));
    auto polishBtn = (Button *)(node->getChildByName("polish_button"));
    this->addChild(neilBtn);
    this->addChild(polishBtn);
    //获取左边按钮
    auto purpleCB = (Button *)(bg->getChildByName("yellowBottle"));
//    purpleCB->setSkewY(-6);
//    purpleCB->setSkewX(6);
    purpleCB->setTag(lYellow);
    auto whiteCB = (Button *)(bg->getChildByName("blackBottle"));
    whiteCB->setTag(lBlack);
//    whiteCB->setSkewY(-3);
//    whiteCB->setSkewX(3);
    auto redCB = (Button *)(bg->getChildByName("blueBottle"));
    redCB->setTag(lBlue);
//    redCB->setSkewY(-6);
//    redCB->setSkewX(6);
    auto blackCB = (Button *)(bg->getChildByName("pinkBottle"));
    blackCB->setTag(lPink);
//    blackCB->setSkewY(-4);
//    blackCB->setSkewX(4);
    auto yellowCB = (Button *)(bg->getChildByName("whiteBottle"));
    yellowCB->setTag(lWhite);
//    yellowCB->setSkewY(-3);
//    yellowCB->setSkewX(3);
    //按钮事件
    purpleCB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, purpleCB, potPosition));
    whiteCB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, whiteCB, potPosition));
    redCB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, redCB, potPosition));
    blackCB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, blackCB, potPosition));
    yellowCB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, yellowCB, potPosition));
    //获取右边按钮
    auto rYellowB = (Button* )(bg->getChildByName("slashBottle"));
    auto rPurpleB = (Button* )(bg->getChildByName("flowerBottle"));
    auto rBlueB = (Button* )(bg->getChildByName("shapBottle"));
    auto rGreenB = (Button *)(bg->getChildByName("heartBottle"));
    rYellowB->setTag(rSlash);
    rPurpleB->setTag(rFlower);
    rBlueB->setTag(rShap);
    rGreenB->setTag(rHeart);
    //点击事件
    rYellowB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, rYellowB, potPosition));
    rPurpleB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, rPurpleB, potPosition));
    rBlueB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, rBlueB, potPosition));
    rGreenB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, rGreenB, potPosition));
    //获取上方按钮
    auto tBlueB = (Button *)(bg->getChildByName("effectPanel")->getChildByName("specialBottle"));
    tBlueB->setTag(tSpecial);
    //点击事件
    tBlueB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, tBlueB, potPosition));
    //确定按钮
    auto mixBtn = (Button *)(bg->getChildByName("MixBtn"));
    mixBtn->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickMixButton, this));
    mixBtn->setEnabled(false);
    //创建schedule
    schedule(schedule_selector(CreateNailPolishScene::updateCustom));
    //保存界面
    auto saveNotice = (Layout *)(node->getChildByName("saveNotice"));
    saveNotice->setVisible(false);
    this->addChild(saveNotice, 5);
    //保存和取消按钮
    auto yesBtn = (Button *)(saveNotice->getChildByName("yesBtn"));
    auto noBtn = (Button *)(saveNotice->getChildByName("noBtn"));
    yesBtn->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickYes, this));
    noBtn->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickNo, this));
    
    
    //音效、评论和去广告按钮
    rmAds = (Button *)(bg->getChildByName("rmBtn"));
    
    rmAds->addClickEventListener([=](Ref *p){
        //创建动画
        auto view = CommonView::getInstance()->getCommentView();
#define ADSTAG 11
        this->addChild(view);
        view->setScale(0.1);
        auto scaleB = EaseBackOut::create(ScaleBy::create(1, 10));
        view->runAction(scaleB);
    });
    //声音开关
    auto soundBtn = (Button *)(bg->getChildByName("soundBtn"));
    soundBtn->loadTextures(ISSOUNDOPEN?SOUNDBTN.c_str():SOUNDBTN_U.c_str(), ISSOUNDOPEN?SOUNDBTN_U.c_str():SOUNDBTN.c_str());
    soundBtn->addClickEventListener([=](Ref *p){
        if (ISSOUNDOPEN) {
            SETSOUND(false);
            soundBtn->loadTextures(SOUNDBTN_U.c_str(), SOUNDBTN.c_str());
        } else {
            SETSOUND(true);
            soundBtn->loadTextures(SOUNDBTN.c_str(), SOUNDBTN_U.c_str());
        }
        Audio::getInstance()->playBgm();
        //设置开关状态
    });
    auto effectBtn = (Button *)(bg->getChildByName("effectBtn"));
    effectBtn->loadTextures(ISEFFECTOPEN?EFFECTBTN.c_str():EFFECTBTN_U.c_str(), ISEFFECTOPEN?EFFECTBTN_U.c_str():EFFECTBTN.c_str());
    effectBtn->addClickEventListener([=](Ref *){
        if (ISEFFECTOPEN) {
            SETEFFECT(false);
            effectBtn->loadTextures(EFFECTBTN_U.c_str(), EFFECTBTN.c_str());
        } else {
            SETEFFECT(true);
            effectBtn->loadTextures(EFFECTBTN.c_str(), EFFECTBTN_U.c_str());
        }
    });
    //评论
    auto commentBtn = (Button *)(bg->getChildByName("scoreBtn"));
    commentBtn->addClickEventListener([](Ref *){
        //评论
        Application::getInstance()->openURL("http://www.baidu.com");
    });
    //提示版
    auto color_title = (Text *)(bg->getChildByName("color_title")->getChildByName("title"));
    auto shape_title = (Text *)(bg->getChildByName("potion_title")->getChildByName("title"));
    //提示
    auto saveNtc = (Text *)(saveNotice->getChildByName("info"));
    //国际化
    if (Application::getInstance()->getCurrentLanguage() == LanguageType::CHINESE) {
        commentBtn->setTitleText("评论");
        rmAds->setTitleText("去广告");
        mixBtn->setTitleText("混合");
        color_title->setString("颜色");
        shape_title->setString("形状");
        saveNtc->setString("要保存这个指甲油吗？");
        yesBtn->setTitleText("是");
        noBtn->setTitleText("不");
    }
    
    return true;
}

void CreateNailPolishScene::updateCustom(float dt) {
    //检查是否能够点击确定按钮
    this->chechStateOfMixButton();
    //获取按钮
    auto bg = this->getChildByName("bg");
    auto btn = (Button *)(bg->getChildByName("MixBtn"));
    btn->setEnabled(canSelectedMixButton);
    //判断是否购买
    bool isPurchase = UserDefault::getInstance()->getBoolForKey(ISPURCHASE.c_str(), false);
    rmAds->setVisible(isPurchase?false:true);
}

//点击事件
void CreateNailPolishScene::onClickColor(Button *btn, Vec2 movePosition) {
    //判断是否已经选择
    int tag = btn->getTag();
    int result = 4;     //表示最终选择情况，0，1表示选择左边，2右边，3上边，4选择失败
    if (tag>=11&&tag<=15) {
        if (choices.lSecondC != 0) {
            this->showNotice();
        } else if (choices.lFirstC !=0 && tag==choices.lFirstC) {
            this->showNotice();
        } else if (choices.lFirstC == 0){
            choices.lFirstC = tag;
            result = 0;
        } else {
            choices.lSecondC = tag;
            result = 1;
        }
    } else if (tag>=21 && tag<=24) {
        if (choices.rChoice != 0) {
            this->showNotice();
        } else {
            choices.rChoice = tag;
            result = 2;
        }
    } else if (tag>30 && tag<33){
        if (choices.tChoice != 0) {
            this->showNotice();
        } else {
            choices.tChoice = tag;
            result = 3;
        }
    }
    //创建动画
    auto sprite = createSpriteWithTagAndPosition(tag, btn->convertToWorldSpace(btn->getContentSize()/2));
    this->addChild(sprite);
    btn->setCascadeOpacityEnabled(false);
    btn->setOpacity(0);
    switch (result) {
        case 0:
        case 1:
        {
            this->showLeftAndTopButtonClickedAnimationsWithSpriteAndPositionAndButtton(sprite, movePosition, btn);
        }
            break;
            
        case 2:
        {
            this->showRightButtonClickedAnimationsWithSpriteAndPositionAndButton(sprite, movePosition, btn);
        }
            break;
            
        case 3:
        {
            this->showLeftAndTopButtonClickedAnimationsWithSpriteAndPositionAndButtton(sprite, movePosition, btn);
        }
            break;
        default:
        {
            btn->setOpacity(255);
            this->removeChild(sprite);
        }
            break;
    }
    
}

#pragma mark 创建左边和上边的动画
void CreateNailPolishScene::showLeftAndTopButtonClickedAnimationsWithSpriteAndPositionAndButtton(Sprite *sprite, Vec2 movePosition, Button *btn) {
    //音效
    Audio::getInstance()->playEffect(C_LEFT);
    //创建屏蔽点击事件层
    auto layout = Layout::create();
#define LAYOUTTAG 11
    layout->setTag(LAYOUTTAG);
    layout->setContentSize(Size(SCREAN_SIZE.width, SCREAN_SIZE.height));
    layout->setAnchorPoint(Vec2(0, 0));
    layout->setTouchEnabled(true);
    this->addChild(layout);
    //判断按钮位置
    bool isLeftButton = false;
    
    
    if (btn->getTag()>10 &&btn->getTag()<16) {
        isLeftButton = true;
    }
    //获取最开始位置
    Vec2 firstPstn;
    if (isLeftButton) {
        firstPstn = sprite->getPosition();
    } else {
        firstPstn = sprite->convertToWorldSpace(sprite->getContentSize()/2);
    }
    //创建动画:缩小、放大并上升、摇晃、移动、倾倒、返回
    auto scaleS = ScaleBy::create(0.1, 1, 0.5);
    auto scaleB = ScaleBy::create(0.2, 1, 2);
    auto moveUp = MoveBy::create(0.2, Vec2(0, sprite->getContentSize().height/3));
    auto spawn1 = Spawn::create(scaleB, moveUp, NULL);
    
    auto shake1 = RotateBy::create(0.1, 15);
    auto shake2 = RotateBy::create(0.1, -15);
    ccBezierConfig bzr;
    bzr.controlPoint_1 = Vec2(firstPstn.x, firstPstn.y+300);
    bzr.controlPoint_2 = Vec2(movePosition.x-(movePosition.x-firstPstn.x)/2, movePosition.y+sprite->getContentSize().height/2);
    bzr.endPosition = Vec2(movePosition.x-(isLeftButton?55:-(sprite->getContentSize().height)/2), movePosition.y+20);
    auto bzl =BezierTo::create(1, bzr);
    auto moveB = MoveTo::create(0.5, firstPstn);
    //移动过程中变小
    auto scaleSmlWhenMove = TargetedAction::create(sprite, ScaleBy::create(1, 0.5));
    auto moveAndScaleS = Spawn::create(bzl, scaleSmlWhenMove, CallFunc::create([](){
        //播放音效
        Audio::getInstance()->playEffect(MOVE);
    }), NULL);
    //变回以前大小
    auto scaleBWhenMoveB = TargetedAction::create(sprite, ScaleBy::create(0.5, 2));
    auto deltaAngle = 90;
    if (isLeftButton == false) {
        deltaAngle = -90;
    }
    auto rotate = RotateBy::create(0.3, deltaAngle);
    auto rotateB = RotateBy::create(0.5, -deltaAngle);
    auto spawn2 = Spawn::create(moveB, rotateB, scaleBWhenMoveB, CallFunc::create([](){
        //播放音效
        Audio::getInstance()->playEffect(MOVE);
    }), NULL);
    //倒水动画
    auto efects = (Sprite *)(this->getChildByName("bg")->getChildByName("pBg")->getChildByName("efects"));
    TargetedAction *efectsMove;
//    auto pstn = efects->getPosition();
    auto catche = SpriteFrameCache::getInstance();
    auto fadeIn = FadeIn::create(0.1);
    auto fadeOut = FadeOut::create(0.1);
    if (isLeftButton) {
        //创建精灵帧
        switch (btn->getTag()) {
            case lYellow:
                efects->setSpriteFrame(catche->getSpriteFrameByName("firstSceneView/yellowDrop.png"));
                break;
            case lBlack:
                efects->setSpriteFrame(catche->getSpriteFrameByName("firstSceneView/blackDrop.png"));
                break;
            case lBlue:
                efects->setSpriteFrame(catche->getSpriteFrameByName("firstSceneView/blueDrop.png"));
                break;
            case lPink:
                efects->setSpriteFrame(catche->getSpriteFrameByName("firstSceneView/pinkDrop.png"));
                break;
            case lWhite:
                efects->setSpriteFrame(catche->getSpriteFrameByName("firstSceneView/whiteDrop.png"));
                break;
            default:
                efects->setSpriteFrame(catche->getSpriteFrameByName("firstSceneView/blackDrop.png"));
                break;
        }
        //滴水效果
        efects->setAnchorPoint(Vec2(0.5, 1));
        auto scaleL = ScaleBy::create(0.1, 1, 1.5);
        auto scaleLB = ScaleTo::create(0.3, 1, 0.5);
        auto scaleB = ScaleBy::create(0.2, 1, 2);
        auto moveDown = EaseBackIn::create(MoveBy::create(0.3, Vec2(0, -50)));
        auto moveBack = MoveBy::create(0.1, Vec2(0, 50));
        efectsMove = TargetedAction::create(efects, Sequence::create(fadeIn, scaleL, scaleLB, scaleB, moveDown, fadeOut, moveBack, fadeIn->clone(), scaleL->clone(), scaleLB->clone(), scaleB->clone(), moveDown->clone(), fadeOut->clone(), moveBack->clone(), NULL));
    }else {
        efects->setSpriteFrame(catche->getSpriteFrameByName("firstSceneView/dumpedSpecialEffect.png"));
        //创建效果
        efects->setAnchorPoint(Vec2(0.5, 0.5));
        auto flipY = FlipY::create(true);
        auto flipBack = FlipY::create(false);
        auto moveDown = MoveBy::create(0.3, Vec2(0, -30));
        auto moveBack = MoveBy::create(0.3, Vec2(0, 30));
        efectsMove = TargetedAction::create(efects, Sequence::create(flipY, fadeIn, moveDown, moveBack, moveDown->clone(), moveBack->clone(), fadeOut, flipBack, NULL));
    }
    
    auto effectWithAudio = Spawn::create(efectsMove, CallFunc::create([=](){
        //播放音效
        if (isLeftButton) {
            Audio::getInstance()->playEffect(DUMPL);
        } else {
            Audio::getInstance()->playEffect(BLING);
        }
        
    }), NULL);
    
    auto sqnc = Sequence::create(scaleS, spawn1, shake1, shake2, shake2, shake1, shake1, shake2, moveAndScaleS, rotate, effectWithAudio, spawn2, CallFuncN::create(CC_CALLBACK_0(CreateNailPolishScene::clearSprite, this, sprite, btn)), NULL);
    sprite->runAction(sqnc);
}

#pragma mark 创建右边的动画
void CreateNailPolishScene::showRightButtonClickedAnimationsWithSpriteAndPositionAndButton(Sprite* sprite, Vec2 movePosition, Button *btn) {
    //音效
    Audio::getInstance()->playEffect(C_RIGHT);
    //设置不可点击层
    auto layout = Layout::create();
    layout->setTag(LAYOUTTAG);
    layout->setContentSize(Size(SCREAN_SIZE.width, SCREAN_SIZE.height));
    layout->setAnchorPoint(Vec2(0, 0));
    layout->setTouchEnabled(true);
    this->addChild(layout);
    //缩小、放大并弹出塞子、移动、倾倒、返回
    Vec2 firstPstn = sprite->getPosition();
    auto moveUpHight = sprite->getContentSize().height/3;
    auto plug = (Sprite* )(btn->getChildByName("plug"));
    plug->setVisible(true);
    auto scaleS = ScaleBy::create(0.1, 1, 0.4);     //缩小
    auto scaleB = ScaleBy::create(0.3, 1, 2.5);       //变回
    auto pMove1 = MoveBy::create(0.3, Vec2(0, moveUpHight));    //塞子升高
    auto plugAction = TargetedAction::create(plug, pMove1);
    auto potAction = TargetedAction::create(sprite, scaleB);
    auto spawn1 = Spawn::create(plugAction, potAction, NULL);
    Vec2 plugM2;
    if (btn->getTag() == 23 || btn->getTag() == 21) {
        plugM2 = Vec2(-sprite->getContentSize().width, -moveUpHight*1.5);
    } else {
        plugM2 = Vec2(sprite->getContentSize().width, -moveUpHight*1.5);
    }
    auto pMove2 = MoveBy::create(0.3, plugM2);  //塞子移动
    auto pMoveB = MoveBy::create(0.1, Vec2(-plugM2.x, -(plugM2.y+moveUpHight)));
    auto plugActionF = TargetedAction::create(plug, Hide::create());  //塞子消失
    auto plugAction2 = TargetedAction::create(plug, pMove2);
    auto plugActionB = TargetedAction::create(plug, pMoveB);    //塞子移回
    
    ccBezierConfig bzr;
    bzr.controlPoint_1 = Vec2(firstPstn.x, firstPstn.y+400);
    bzr.controlPoint_2 = Vec2(movePosition.x-(movePosition.x-firstPstn.x)/2, movePosition.y);
    bzr.endPosition = Vec2(movePosition.x+60, movePosition.y+20);
    auto move = BezierTo::create(1, bzr);
    auto spriteMove = TargetedAction::create(sprite, move);
    //移动过程中变小
    auto scaleSmlWhenMove = TargetedAction::create(sprite, ScaleBy::create(1, 0.5));
    //变回以前大小
    auto scaleBFast = ScaleBy::create(0.1, 2);
    auto scaleSFast = ScaleBy::create(0.1, 0.5);
    auto scaleBWhenMoveB = TargetedAction::create(sprite, ScaleBy::create(0.5, 2));
    auto moveB = MoveTo::create(0.5, firstPstn);
    auto rotate = RotateBy::create(0.5, -90);
    auto rotateB = RotateBy::create(0.5, 90);
    auto spawn2 = Spawn::create(moveB, rotateB, scaleBWhenMoveB, CallFunc::create([](){
        //播放音效
        Audio::getInstance()->playEffect(MOVE);
    }), NULL);
    auto spawn3 = Spawn::create(plugActionB, spriteMove, CallFunc::create([](){
        //播放音效
        Audio::getInstance()->playEffect(MOVE);
    }), scaleSmlWhenMove, NULL);
    //创建精灵帧动画
    auto spriteFrameCatche = SpriteFrameCache::getInstance();
    std::string fNm1, fNm2, fNm3, fNm4, fNm5;
    switch (btn->getTag()) {
        case rSlash:
            {
                fNm1 = "firstSceneView/slashD.png";
                fNm2 = "firstSceneView/slashD1.png";
                fNm3 = "firstSceneView/slashD2.png";
                fNm4 = "firstSceneView/slashD1.png";
                fNm5 = "firstSceneView/slashD2.png";
            }
            break;
        case rFlower:
            {
                fNm1 = "firstSceneView/slashD.png";
                fNm2 = "firstSceneView/slashD1.png";
                fNm3 = "firstSceneView/slashD2.png";
                fNm4 = "firstSceneView/slashD1.png";
                fNm5 = "firstSceneView/slashD2.png";
            }
            break;
        case rShap:
            {
                fNm1 = "firstSceneView/slashD.png";
                fNm2 = "firstSceneView/slashD1.png";
                fNm3 = "firstSceneView/slashD2.png";
                fNm4 = "firstSceneView/slashD1.png";
                fNm5 = "firstSceneView/slashD2.png";
            }
            break;
        case rHeart:
            {
                fNm1 = "firstSceneView/slashD.png";
                fNm2 = "firstSceneView/slashD1.png";
                fNm3 = "firstSceneView/slashD2.png";
                fNm4 = "firstSceneView/slashD1.png";
                fNm5 = "firstSceneView/slashD2.png";
            }
            break;
            
        default:
        {
            fNm1 = "firstSceneView/slashD.png";
            fNm2 = "firstSceneView/slashD1.png";
            fNm3 = "firstSceneView/slashD2.png";
            fNm4 = "firstSceneView/slashD1.png";
            fNm5 = "firstSceneView/slashD2.png";
        }
            break;
    }
    Vector<SpriteFrame *>array;

    auto frame1 = spriteFrameCatche->getSpriteFrameByName(fNm1);
    auto frame2 = spriteFrameCatche->getSpriteFrameByName(fNm2);
    auto frame3 = spriteFrameCatche->getSpriteFrameByName(fNm3);
    auto frame4 = spriteFrameCatche->getSpriteFrameByName(fNm4);
    auto frame5 = spriteFrameCatche->getSpriteFrameByName(fNm5);
    
    array.pushBack(frame1);
    array.pushBack(frame2);
    array.pushBack(frame3);
    array.pushBack(frame4);
    array.pushBack(frame5);
    
    auto animation = Animation::createWithSpriteFrames(array, 0.3, 1);
    animation->setRestoreOriginalFrame(true);
    auto spriteAnimate = Animate::create(animation);
    auto frameAndRoleB = Spawn::create(spriteAnimate,CallFunc::create([](){
        //播放音效
        Audio::getInstance()->playEffect(DUMP);
    }), scaleBFast, NULL);
    
    auto sqnc = Sequence::create(scaleS, spawn1, plugAction2, plugActionF, spawn3, rotate, frameAndRoleB, scaleSFast, spawn2, CallFuncN::create(CC_CALLBACK_0(CreateNailPolishScene::clearSprite, this, sprite, btn)), NULL);
    sprite->runAction(sqnc);
}

#pragma mark 点击合成按钮
void CreateNailPolishScene::onClickMixButton() {
    //音效
    Audio::getInstance()->playEffect(C_LEFT);
    //合成指甲油
    std::string str;
    //用户选择花纹和颜色
    int first = choices.lFirstC;
    int second = choices.lSecondC;
    int third = choices.rChoice;
    //判断
    if (second == 0) {
        //使用单色
        str = StringUtils::format("commonViews/%d.png", (first-10));
    } else {
        //使用颜色和底纹
        str = StringUtils::format("commonViews/%d%d%d.png", (first-10), (second-10), (third-20));
    }
    //设置指甲油瓶子
    auto saveNotice =(Layout *)(this->getChildByName("saveNotice"));
    auto resultPot = (Sprite *)(saveNotice->getChildByName("bottle"));
    resultPot->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
    //获取罐子
    auto bg = (Sprite*)(this->getChildByName("bg"));
    auto pot = (Sprite *)(bg->getChildByName("pBg")->getChildByName("Pot"));
    auto mixSuccess = (Sprite *)(pot->getChildByName("mixSuccess"));
    mixSuccess->setScale(0.1);
    //创建动画
    auto bLayout = Layout::create();
    bLayout->setContentSize(SCREAN_SIZE);
    bLayout->setPosition(Vec2(0, 0));
    bLayout->setTouchEnabled(true);
#define bLayoutTag 4
    this->addChild(bLayout, 4, bLayoutTag);
    auto scaleS = ScaleBy::create(0.1, 0.1);
    auto show = Show::create();
    auto scale = ScaleBy::create(0.3, 10);
    //罐子动画
    auto potShake1 = TargetedAction::create(pot, RotateBy::create(0.15, 10));
    auto potShake2 = TargetedAction::create(pot, RotateBy::create(0.15, -10));
    auto potScaleS = TargetedAction::create(pot, ScaleBy::create(0.1, 0.5));
    auto potScaleB = EaseBackInOut::create(TargetedAction::create(pot, ScaleBy::create(0.3, 2)));
    auto mixScaleB = Spawn::create(EaseInOut::create(TargetedAction::create(mixSuccess, ScaleBy::create(0.5, 10)), 10), CallFunc::create([](){
        //播放音效
        Audio::getInstance()->playEffect(MIXRESULT);
    }), NULL);
    auto mixFadeOut = TargetedAction::create(mixSuccess, FadeOut::create(1));
    auto mixFadeIn = TargetedAction::create(mixSuccess, FadeIn::create(0.1));
    saveNotice->runAction(Sequence::create(potShake1, CallFunc::create([](){
        Audio::getInstance()->playEffect(MIXPROCESS);
    }), potShake2, potShake1->clone(), potShake2->clone(), potScaleS, potScaleB, mixFadeIn, mixScaleB, scaleS, show, scale, mixFadeOut, NULL));
}

//判断瓶子是否装满
bool CreateNailPolishScene::isBottleFull() {
    bool result = false;
    if (numberOfBottle == 5) {
        result = true;
    }
    
    return result;
}

//回调函数
void CreateNailPolishScene::clearSprite(Sprite* s, Button* btn) {
    this->removeChildByTag(LAYOUTTAG);
    this->removeChild(s);
    btn->setOpacity(255);
    this->chechStateOfMixButton();
    this->showCenterBottleWithTag(btn->getTag());
}

//提示其他选项
void CreateNailPolishScene::showNotice() {
    bool noticeAreaL = true;
    bool noticeAreaR = true;
    bool noticeAreaT = true;
    bool specailCondition = false;
    if (choices.lFirstC!=0 || choices.lSecondC!=0) {
        noticeAreaL = false;
    }
    if (choices.rChoice!=0) {
        noticeAreaR = false;
    }
    if (choices.tChoice!=0) {
        noticeAreaT = false;
    }
    if (choices.lFirstC!=0 && choices.lSecondC == 0) {
        specailCondition = true;
    }
    //提示
    if (noticeAreaL == true) {
        //获取右边的notice节点
        for (int i = lWhite; i<=lBlue; i++) {
            auto notice = (Sprite *)(this->getChildByName("bg")->getChildByTag(i)->getChildByName("notice"));
            this->showNoticeAnimationBySprite(notice);
        }
    }
    if (noticeAreaR == true) {
        for (int i = rSlash; i<=rHeart; i++) {
            auto notice = (Sprite *)(this->getChildByName("bg")->getChildByTag(i)->getChildByName("notice"));
            this->showNoticeAnimationBySprite(notice);
        }
    }
    if (noticeAreaT == true) {
        auto notice = (Sprite *)(this->getChildByName("bg")->getChildByName("effectPanel")->getChildByName("specialBottle")->getChildByName("notice"));
        this->showNoticeAnimationBySprite(notice);
    }
    if ((noticeAreaL == false && noticeAreaR == false) || specailCondition == true){
        canSelectedMixButton = true;
    } else {
        canSelectedMixButton = false;
    }
}

//通知的动画
void CreateNailPolishScene::showNoticeAnimationBySprite(Sprite *sprite) {
    auto fadeIn = FadeIn::create(0.1);
    auto moveUp = MoveBy::create(0.3, Vec2(0, -30));
    auto moveDown = MoveBy::create(0.3, Vec2(0, 30));
    auto fadeOut = FadeOut::create(0.1);
    auto sqnc = Sequence::create(fadeIn, moveUp, moveDown, moveUp->clone(), moveDown->clone(), fadeOut, NULL);
    sprite->runAction(sqnc);
}

//创建精灵
Sprite* CreateNailPolishScene::createSpriteWithTagAndPosition(int tag, Vec2 position) {
    auto frameCatch = SpriteFrameCache::getInstance();
    frameCatch->addSpriteFramesWithFile("firstSceneView/left.plist", "firstSceneView/left.png");
    std::string textureName;
    switch (tag) {
        case lYellow:
            textureName = "firstSceneView/yellowPolishU1.png";
            break;
        case lBlack:
            textureName = "firstSceneView/blackPolishU1.png";
            break;
        case lBlue:
            textureName = "firstSceneView/bluePolishU1.png";
            break;
        case lPink:
            textureName = "firstSceneView/pinkPolishU.png";
            break;
        case lWhite:
            textureName = "firstSceneView/whitePolishU1.png";
            break;
        case rSlash:
            textureName = "firstSceneView/slashBottleU.png";
            break;
        case rFlower:
            textureName = "firstSceneView/flowBottleU.png";
            break;
        case rShap:
            textureName = "firstSceneView/shapBottleU.png";
            break;
        case rHeart:
            textureName = "firstSceneView/heartBottleU.png";
            break;
        case tSpecial:
            textureName = "firstSceneView/specialBottle.png";
            break;
            
        default:
            textureName = "firstSceneView/btn-share.png";
            break;
    }
    auto sprite = Sprite::createWithSpriteFrame(frameCatch->getSpriteFrameByName(textureName));
    sprite->setPosition(position);
    
    return sprite;
}

//判断是否能够选择
void CreateNailPolishScene::chechStateOfMixButton() {
    if (((choices.lFirstC != 0 || choices.lSecondC != 0)&&choices.rChoice != 0)||(choices.lFirstC != 0 && choices.lSecondC == 0)) {
        canSelectedMixButton = true;
    } else {
        canSelectedMixButton = false;
    }
}

//保存按钮
void CreateNailPolishScene::onClickYes() {
    //得到数据
#pragma mark 通过用户选择保存数据
    std::string str;
    //用户选择花纹和颜色
    int first = choices.lFirstC;
    int second = choices.lSecondC;
    int third = choices.rChoice;
    //闪光效果
    int blink;
    if (choices.tChoice == 0) {
        blink = 0;
    } else {
        blink = 1;
    }
    //判断
    if (second == 0) {
        //使用单色
        str = StringUtils::format("commonViews/%d.png%d", (first-10), blink);
    } else {
        //使用颜色和底纹
        str = StringUtils::format("commonViews/%d%d%d.png%d", (first-10), (second-10), (third-20), blink);
    }
    
    //获取之前数据
    if (colors.bottle1 == "0") {
        colors.bottle1 = str;
        UD->setStringForKey("b1Color", str);
    } else if (colors.bottle2 == "0"){
        colors.bottle2 = str;
        UD->setStringForKey("b2Color", str);
    } else if (colors.bottle3 == "0"){
        colors.bottle3 = str;
        UD->setStringForKey("b3Color", str);
    } else if (colors.bottle4 == "0"){
        colors.bottle4 = str;
        UD->setStringForKey("b4Color", str);
    } else if (colors.bottle5 == "0"){
        colors.bottle5 = str;
        UD->setStringForKey("b5Color", str);
    } else {
        //覆盖
        switch (UD->getIntegerForKey("oldestStore", 1)) {
            case 1:
            {
                colors.bottle1 = str;
                UD->setStringForKey("b1Color", str);
                UD->setIntegerForKey("oldestStore", 2);
            }
                break;
            case 2:
            {
                colors.bottle1 = str;
                UD->setStringForKey("b2Color", str);
                UD->setIntegerForKey("oldestStore", 3);
            }
                break;
            case 3:
            {
                colors.bottle1 = str;
                UD->setStringForKey("b3Color", str);
                UD->setIntegerForKey("oldestStore", 4);
            }
                break;
            case 4:
            {
                colors.bottle1 = str;
                UD->setStringForKey("b4Color", str);
                UD->setIntegerForKey("oldestStore", 5);
            }
                break;
            default:
            {
                colors.bottle1 = str;
                UD->setStringForKey("b5Color", str);
                UD->setIntegerForKey("oldestStore", 1);
            }
                break;
        }
    }
    UD->setIntegerForKey("numberOfBottle", numberOfBottle);
    
    //隐藏界面
    this->removeChildByTag(bLayoutTag);
    auto saveLayout = this->getChildByName("saveNotice");
    auto scale = ScaleBy::create(0.3, 0.1);
    auto scaleB = ScaleBy::create(0.1, 10);
    auto hideAnimation = Hide::create();
    auto sqnc = Sequence::create(scale, hideAnimation, scaleB, CallFunc::create(CC_CALLBACK_0(CreateNailPolishScene::onClickNeilBtn, this)), NULL);
    saveLayout->runAction(sqnc);
    //清除临时数据
    memset(&choices, 0, sizeof(choices));
    canSelectedMixButton = false;
    //隐藏中间瓶子
    if (!seletecdBottle.empty()) {
        for (Sprite* s : seletecdBottle){
            s->setVisible(false);
        }
        seletecdBottle.clear();
    }
}

void CreateNailPolishScene::onClickNo() {
    //清除临时数据
    memset(&choices, 0, sizeof(choices));
    canSelectedMixButton = false;
    //隐藏界面
    this->removeChildByTag(bLayoutTag);
    auto saveLayout = this->getChildByName("saveNotice");
    auto scale = ScaleBy::create(0.3, 0.1);
    auto scaleB = ScaleBy::create(0.1, 10);
    auto hideAnimation = Hide::create();
    auto sqnc = Sequence::create(scale, hideAnimation, scaleB, NULL);
    saveLayout->runAction(sqnc);
    //隐藏中间瓶子
    if (!seletecdBottle.empty()) {
        for (Sprite* s : seletecdBottle)
            s->setVisible(false);
        seletecdBottle.clear();
    }
}

//点击涂指甲界面
void CreateNailPolishScene::onClickNeilBtn() {
    auto paintScene = PaintingNailsScene::createScene();
    auto transition = TransitionFade::create(1.0, paintScene);
    Director::getInstance()->replaceScene(transition);
}

#pragma mark 显示中间瓶子
void CreateNailPolishScene::showCenterBottleWithTag(int tag) {
    //得到瓶子
    auto sp = this->getChildByName("bg")->getChildByName("centerBg");
    std::string name;
    //得到点击位置
    switch (tag) {
        case lYellow:
            name = "yellowBottle";
            break;
        case lBlack:
            name = "blackBottle";
            break;
        case lBlue:
            name = "blueBottle";
            break;
        case lPink:
            name = "pinkBottle";
            break;
        case lWhite:
            name = "whiteBottle";
            break;
        case rSlash:
            name = "slashBottle";
            break;
        case rFlower:
            name = "flowerBottle";
            break;
        case rShap:
            name = "shapBottle";
            break;
        case rHeart:
            name = "heartBottle";
            break;
        case tSpecial:
            name = "specialBottle";
            break;
        default:
            name = "yellowBottle";
            break;
    }
    auto bottle = (Sprite *)(sp->getChildByName(name));
    bottle->setVisible(true);
    //添加
    seletecdBottle.pushBack(bottle);
}