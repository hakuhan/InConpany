//
//  MainScene.cpp
//  meijia
//
//  Created by xcode31 on 16/8/17.
//
//

#include "MainScene.hpp"
#include "DefaultHeader.h"
#include "ui/CocosGUI.h"
#include "CreateNailPolishScene.hpp"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;

Scene* MainScene::createScene(){
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool MainScene::init() {
    if (!Layer::init()) {
        return false;
    }
    auto node = CSLoader::createNodeWithVisibleSize("introScene/introScene.csb");
    
    //背景
    auto bg = (Layout *)(node->getChildByName("bg"));
    this->addChild(bg);
    //play按钮
    auto playBtn = (Button *)(bg->getChildByName("startBtn"));
    playBtn->addClickEventListener(CC_CALLBACK_1(MainScene::onClick_play, this));
    //创建动态图片
    auto leftFoot = Sprite::create("sdff.png");
    
    leftFoot->setPosition(Vec2(SCREAN_SIZE.width, SCREAN_SIZE.height/3));
    auto rightFoot = Sprite::create("bomb.png");
    rightFoot->setPosition(Vec2(SCREAN_SIZE.width, SCREAN_SIZE.height/3));
    bg->addChild(leftFoot);
    bg->addChild(rightFoot);
    //动作
    auto leftMoveIn = MoveTo::create(1, Point(SCREAN_SIZE.width/3, SCREAN_SIZE.height/3));
    auto leftEaseIn = EaseIn::create(leftMoveIn, 0.5);
    auto rightMoveIn = MoveTo::create(1, Point(SCREAN_SIZE.width*2/3, SCREAN_SIZE.height/3));
    auto rightEaseIn = EaseIn::create(rightMoveIn, 0.5);
    //移动
    auto leftMoveUp = MoveBy::create(1.5, Point(0, leftFoot->getContentSize().height/3));
    auto leftMoveDown = MoveBy::create(1.5, Point(0, -leftFoot->getContentSize().height/3));
    auto rightMoveDown = MoveBy::create(1.5, Point(0, -rightFoot->getContentSize().height/3));
    auto rightMoveUp = MoveBy::create(1.5, Point(0, rightFoot->getContentSize().height/3));
    //组合
    auto rightAction = RepeatForever::create(Sequence::create(DelayTime::create(1), rightMoveUp, DelayTime::create(1), rightMoveDown, NULL));
    auto leftAction = RepeatForever::create(Sequence::create(DelayTime::create(1), leftMoveDown, DelayTime::create(1), leftMoveUp, NULL));
    leftFoot->runAction(leftEaseIn);
    leftFoot->runAction(leftAction);
    rightFoot->runAction(rightEaseIn);
    rightFoot->runAction(rightAction);
    
    return true;
}

void MainScene::onClick_play(Ref* p) {
    //跳转到开始游戏scene
    auto transition = TransitionFade::create(1, CreateNailPolishScene::createScene());
    Director::getInstance()->replaceScene(transition);
}