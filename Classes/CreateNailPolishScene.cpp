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
    numberOfBottle = BOTTLENUMBER;
    colors.bottle1 = UD->getStringForKey("b1Color", "0");
    colors.bottle2 = UD->getStringForKey("b2Color", "0");
    colors.bottle3 = UD->getStringForKey("b3Color", "0");
    colors.bottle4 = UD->getStringForKey("b4Color", "0");
    colors.bottle5 = UD->getStringForKey("b5Color", "0");
    
    auto node = CSLoader::createNodeWithVisibleSize("game/createNeilpolish.csb");
    auto bg = (Layout *)(node->getChildByName("bg"));
    this->addChild(bg);
    auto pot = bg->getChildByName("Pot");
    auto potPosition = pot->getPosition();
    //顶部按钮
    auto neilBtn = (Button *)(node->getChildByName("neil_button"));
    neilBtn->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickNeilBtn, this));
    auto polishBtn = (Button *)(node->getChildByName("polish_button"));
    this->addChild(neilBtn);
    this->addChild(polishBtn);
    //获取左边按钮
    auto purpleCB = (Button *)(bg->getChildByName("purpleB"));
    purpleCB->setTag(lPurple);
    auto whiteCB = (Button *)(bg->getChildByName("whiteB"));
    whiteCB->setTag(lWhite);
    auto redCB = (Button *)(bg->getChildByName("redB"));
    redCB->setTag(lRed);
    auto blackCB = (Button *)(bg->getChildByName("blackB"));
    blackCB->setTag(lBlack);
    auto yellowCB = (Button *)(bg->getChildByName("yellowB"));
    yellowCB->setTag(lYellow);
    //按钮事件
    purpleCB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, purpleCB, potPosition));
    whiteCB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, whiteCB, potPosition));
    redCB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, redCB, potPosition));
    blackCB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, blackCB, potPosition));
    yellowCB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, yellowCB, potPosition));
    //获取右边按钮
    auto rYellowB = (Button* )(bg->getChildByName("yellowP"));
    auto rPurpleB = (Button* )(bg->getChildByName("purpleP"));
    auto rBlueB = (Button* )(bg->getChildByName("blueP"));
    auto rGreenB = (Button *)(bg->getChildByName("greenP"));
    rYellowB->setTag(rYellow);
    rPurpleB->setTag(rPurple);
    rBlueB->setTag(rBlue);
    rGreenB->setTag(rGreen);
    //点击事件
    rYellowB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, rYellowB, potPosition));
    rPurpleB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, rPurpleB, potPosition));
    rBlueB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, rBlueB, potPosition));
    rGreenB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, rGreenB, potPosition));
    //获取上方按钮
    auto tBlueB = (Button *)(bg->getChildByName("blueS"));
    auto tGreenB = (Button *)(bg->getChildByName("greenS"));
    tBlueB->setTag(tBlue);
    tGreenB->setTag(tGreen);
    //点击事件
    tBlueB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, tBlueB, potPosition));
    tGreenB->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickColor, this, tGreenB, potPosition));
    //确定按钮
    auto mixBtn = (Button *)(bg->getChildByName("MixBtn"));
    mixBtn->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickMixButton, this));
    mixBtn->setEnabled(false);
    //创建schedule
    schedule(schedule_selector(CreateNailPolishScene::updateCustom), 1.0f);
    //保存界面
    auto saveNotice = (Layout *)(node->getChildByName("saveNotice"));
    saveNotice->setVisible(false);
    this->addChild(saveNotice, 5);
    //保存和取消按钮
    auto yesBtn = (Button *)(saveNotice->getChildByName("yesBtn"));
    auto noBtn = (Button *)(saveNotice->getChildByName("noBtn"));
    yesBtn->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickYes, this));
    noBtn->addClickEventListener(CC_CALLBACK_0(CreateNailPolishScene::onClickNo, this));
    
//    //plist 的加载方法
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(".plist", ".png");
//    auto ins = SpriteFrameCache::getInstance();
//    auto frame1 = ins->getSpriteFrameByName("isdnsdna");
//    
//    
//    Vector<SpriteFrame*> xxx;           xxx.clear();
//    
//    //图片的加载方法
//    
//    const cocos2d::Rect rect(0,0,200,200);
//    for(int i = 1; i < 10; i++){
//        auto frame = SpriteFrame::create("1.png", rect);
//        xxx.pushBack(frame);
//    }
//    
//    //auto frame = SpriteFrame::create(<#const std::string &filename#>, );
//    xxx.pushBack(frame1);
//    auto animation = Animation::createWithSpriteFrames(xxx);
//    runAction(Animate::create(animation));
    
    //预加载  加入动画缓存
//    AnimationCache::getInstance()->addAnimation(animation, "playani");
//    AnimationCache::getInstance()->getAnimation("playani");
    
    
    return true;
}

void CreateNailPolishScene::updateCustom(float dt) {
    //检查是否能够点击确定按钮
    //获取按钮
    auto bg = this->getChildByName("bg");
    auto btn = (Button *)(bg->getChildByName("MixBtn"));
    btn->setEnabled(canSelectedMixButton);
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
    auto sprite = createSpriteWithTagAndPosition(tag, btn->getPosition());
    this->addChild(sprite);
    btn->setCascadeOpacityEnabled(false);
    btn->setOpacity(0);
    switch (result) {
        case 0:
        case 1:
        {
            this->showLeftAndTopButtonClickedAnimationsWithSpriteAndPositionAndButtton(sprite, movePosition, btn);
            this->chechStateOfMixButton();
        }
            break;
            
        case 2:
        {
            this->showRightButtonClickedAnimationsWithSpriteAndPositionAndButton(sprite, movePosition, btn);
            this->chechStateOfMixButton();
        }
            break;
            
        case 3:
        {
            this->showLeftAndTopButtonClickedAnimationsWithSpriteAndPositionAndButtton(sprite, movePosition, btn);
            this->chechStateOfMixButton();
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

//创建左边和上边的动画
void CreateNailPolishScene::showLeftAndTopButtonClickedAnimationsWithSpriteAndPositionAndButtton(Sprite *sprite, Vec2 movePosition, Button *btn) {
    //判断按钮位置
    bool isLeftButton = false;
    if (btn->getTag()>10 &&btn->getTag()<16) {
        isLeftButton = true;
    }
    //创建动画:缩小、放大并上升、摇晃、移动、倾倒、返回
    auto scaleS = ScaleBy::create(0.1, 1, 0.5);
    auto scaleB = ScaleBy::create(0.2, 1, 2);
    auto moveUp = MoveBy::create(0.2, Vec2(0, sprite->getContentSize().height));
    auto spawn1 = Spawn::create(scaleB, moveUp, NULL);
    
    auto shake1 = RotateBy::create(0.1, 10);
    auto shake2 = RotateBy::create(0.1, -10);
    ccBezierConfig bzr;
    bzr.controlPoint_1 = Vec2(0, movePosition.y-sprite->getPositionY());
    bzr.controlPoint_2 = Vec2(movePosition.x-sprite->getPositionX(), 0);
    bzr.endPosition = Vec2(movePosition.x-sprite->getPositionX(), movePosition.y-sprite->getPositionY());
    auto bzl =BezierBy::create(0.5, bzr);
    auto moveB = MoveBy::create(0.5, Vec2(sprite->getPositionX()-movePosition.x, sprite->getPositionY()-movePosition.y-sprite->getContentSize().height));
    auto deltaAngle = 90;
    if (isLeftButton == false) {
        deltaAngle = -90;
    }
    auto rotate = RotateBy::create(0.3, deltaAngle);
    auto rotateB = RotateBy::create(0.5, -deltaAngle);
    auto spawn2 = Spawn::create(moveB, rotateB, NULL);
    
    auto sqnc = Sequence::create(scaleS, spawn1, shake1, shake2, shake2, shake1, shake1, shake2, bzl, rotate,DelayTime::create(1), spawn2, CallFuncN::create(CC_CALLBACK_0(CreateNailPolishScene::clearSprite, this, sprite, btn)), NULL);
    sprite->runAction(sqnc);
    //存储数据：判断
    
}

//创建右边的动画
void CreateNailPolishScene::showRightButtonClickedAnimationsWithSpriteAndPositionAndButton(Sprite* sprite, Vec2 movePosition, Button *btn) {
    //缩小、放大并弹出塞子、移动、倾倒、返回
    auto spriteHight = sprite->getContentSize().height;
    auto plug = (Sprite* )(btn->getChildByName("plug"));
    auto scaleS = ScaleBy::create(0.1, 1, 0.5);     //缩小
    auto scaleB = ScaleBy::create(0.3, 1, 2);       //变回
    auto pMove1 = MoveBy::create(0.3, Vec2(0, spriteHight));    //塞子升高
    auto plugAction = TargetedAction::create(plug, pMove1);
    auto potAction = TargetedAction::create(sprite, scaleB);
    auto spawn1 = Spawn::create(plugAction, potAction, NULL);
    Vec2 plugM2;
    if (btn->getTag() == 21 ||btn->getTag() == 2) {
        plugM2 = Vec2(-sprite->getContentSize().width, -spriteHight*1.5);
    } else {
        plugM2 = Vec2(sprite->getContentSize().width, -spriteHight*1.5);
    }
    auto pMove2 = MoveBy::create(0.3, plugM2);  //塞子移动
    auto pMoveB = MoveBy::create(0.1, Vec2(-plugM2.x, -(plugM2.y+spriteHight)));
    auto plugActionF = TargetedAction::create(plug, FadeOut::create(0.1));  //塞子消失
    auto plugActionFI = TargetedAction::create(plug, FadeIn::create(0.1));  //塞子恢复
    auto plugAction2 = TargetedAction::create(plug, pMove2);
    auto plugActionB = TargetedAction::create(plug, pMoveB);    //塞子移回
    
    ccBezierConfig bzr;
    bzr.controlPoint_1 = Vec2((movePosition.x-sprite->getPositionX())*0.3, (movePosition.y-getPositionY())*0.3);
    bzr.controlPoint_2 = Vec2((movePosition.x-sprite->getPositionX())*0.7, (movePosition.y-getPositionY())*0.7);
    bzr.endPosition = Vec2(movePosition.x-sprite->getPositionX(), movePosition.y-sprite->getPositionY()+sprite->getContentSize().height);
    auto move = BezierBy::create(0.5, bzr);
    auto spriteMove = TargetedAction::create(sprite, move);
    auto moveB = MoveBy::create(0.5, Vec2(-(movePosition.x-sprite->getPositionX()), -(movePosition.y-sprite->getPositionY()+sprite->getContentSize().height)));
    auto rotate = RotateBy::create(0.5, -90);
    auto rotateB = RotateBy::create(0.5, 90);
    auto spawn2 = Spawn::create(moveB, rotateB, NULL);
    auto spawn3 = Spawn::create(plugActionB, spriteMove, NULL);
    auto sqnc = Sequence::create(scaleS, spawn1, plugAction2, plugActionF, spawn3, rotate, spawn2, plugActionFI, CallFuncN::create(CC_CALLBACK_0(CreateNailPolishScene::clearSprite, this, sprite, btn)), NULL);
    sprite->runAction(sqnc);
    //存储数据
}

//点击合成按钮
void CreateNailPolishScene::onClickMixButton() {
    //判断瓶子是否装满
    if (this->isBottleFull()) {
        //通知瓶子装满
        this->showBottleFullNotice();
        return;
    }
    //获取罐子
    auto bg = (Sprite*)(this->getChildByName("bg"));
    auto pot = (Sprite *)(bg->getChildByName("Pot"));
    //创建动画
    auto bLayout = Layout::create();
    bLayout->setContentSize(SCREAN_SIZE);
    bLayout->setPosition(Vec2(0, 0));
    bLayout->setTouchEnabled(true);
#define bLayoutTag 4
    this->addChild(bLayout, 4, bLayoutTag);
    auto saveNotice =(Layout *)(this->getChildByName("saveNotice"));
    auto scaleS = ScaleBy::create(0.1, 0.1);
    auto show = Show::create();
    auto scale = ScaleBy::create(0.3, 10);
    //罐子动画
    auto potScaleS = TargetedAction::create(pot, ScaleBy::create(0.1, 1, 0.5));
    auto potScaleB = TargetedAction::create(pot, ScaleBy::create(0.2, 1, 2));
    saveNotice->runAction(Sequence::create(potScaleS, potScaleB, scaleS, show, scale, NULL));
    //得到合成结果
}

//判断瓶子是否装满
bool CreateNailPolishScene::isBottleFull() {
    bool result = false;
    int number = BOTTLENUMBER;
    if (number == 5) {
        result = true;
    }
    return result;
}

//提示瓶子全部装满
void CreateNailPolishScene::showBottleFullNotice() {
#pragma mark 通知装满瓶子
}

//回调函数
void CreateNailPolishScene::clearSprite(Sprite* s, Button* btn) {
    this->removeChild(s);
    btn->setOpacity(255);
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
        log("左边没有选择");
    }
    if (noticeAreaR == true) {
        log("右边没有选择");
    }
    if (noticeAreaT == true) {
        log("上方没有选择");
    }
    if ((noticeAreaL == false && noticeAreaR == false) || specailCondition == true){
        log("可以点击确定按钮");
        canSelectedMixButton = true;
    } else {
        canSelectedMixButton = false;
    }
}

//创建精灵
Sprite* CreateNailPolishScene::createSpriteWithTagAndPosition(int tag, Vec2 position) {
    std::string textureName;
    switch (tag) {
        case lPurple:
            textureName = "btn-share.png";
            break;
        case lWhite:
            textureName = "btn-share.png";
            break;
        case lRed:
            textureName = "btn-share.png";
            break;
        case lBlack:
            textureName = "btn-share.png";
            break;
        case lYellow:
            textureName = "btn-share.png";
            break;
        case rYellow:
            textureName = "btn-share.png";
            break;
        case rPurple:
            textureName = "btn-share.png";
            break;
        case rBlue:
            textureName = "btn-share.png";
            break;
        case rGreen:
            textureName = "btn-share.png";
            break;
        case tBlue:
            textureName = "btn-share.png";
            break;
        case tGreen:
            textureName = "btn-share.png";
            break;
            
        default:
            textureName = "btn-share.png";
            break;
    }
    auto sprite = Sprite::create(textureName);
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
    //判断
//    switch () {
//        case colors.bottle1:
//            
//            break;
//            
//        default:
//            break;
//    }
    //保存
    
    
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
    
    //跳转
//    this->onClickNeilBtn();
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
}

//点击涂指甲界面
void CreateNailPolishScene::onClickNeilBtn() {
    auto paintScene = PaintingNailsScene::createScene();
    Director::getInstance()->pushScene(paintScene);
}
