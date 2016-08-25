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
#include "FirstSceneOfHelp.hpp"
#include "CreateNailPolishScene.hpp"

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
    
    //创建背景
    auto bg = Sprite::create("HelloWorld.png");
    bg->setPosition(SCREAN_SIZE.width/2, SCREAN_SIZE.height/2);
    addChild(bg);
    
    //创建标题
    auto title = Sprite::create("26.png");
    title->setAnchorPoint(Vec2(0, 1));
    title->setPosition(TITLE_POSITION);
    addChild(title);
    
    //创建play按钮
    auto playButton = Button::create("2(1).png");
    playButton->setAnchorPoint(Vec2(0, 0));
    playButton->setPosition(Vec2(30, SCREAN_SIZE.height*0.2));
    playButton->addClickEventListener(CC_CALLBACK_1(MainScene::onClick_play, this));
    addChild(playButton);
    
    //创建help按钮
    auto helpButton = Button::create("1(3).png");
    helpButton->setAnchorPoint(Vec2(0, 0));
    helpButton->setPosition(Vec2(SCREAN_SIZE.width*0.2, 30));
    helpButton->addClickEventListener(CC_CALLBACK_1(MainScene::onClick_help, this));
    addChild(helpButton);
    
    //创建动态图片
    auto leftFoot = Sprite::create("sdff.png");
    
    leftFoot->setPosition(Vec2(SCREAN_SIZE.width, SCREAN_SIZE.height/3));
    auto rightFoot = Sprite::create("bomb.png");
    rightFoot->setPosition(Vec2(SCREAN_SIZE.width, SCREAN_SIZE.height/3));
    addChild(leftFoot);
    addChild(rightFoot);
    //动作
    auto leftMoveIn = MoveTo::create(1, Point(SCREAN_SIZE.width*2/3, SCREAN_SIZE.height/3));
    auto leftEaseIn = EaseIn::create(leftMoveIn, 0.5);
    auto rightMoveIn = MoveTo::create(1, Point(SCREAN_SIZE.width-rightFoot->getContentSize().width-10, SCREAN_SIZE.height/3));
    auto rightEaseIn = EaseIn::create(rightMoveIn, 0.5);
    //移动
    auto leftMoveUp = MoveTo::create(1.5, Point(SCREAN_SIZE.width*2/3-10, SCREAN_SIZE.height/3+50));
    auto leftMoveDown = MoveTo::create(1.5, Point(SCREAN_SIZE.width*2/3+10, SCREAN_SIZE.height/3-50));
    auto rightMoveDown = MoveTo::create(1.5, Point(SCREAN_SIZE.width-rightFoot->getContentSize().width-20, SCREAN_SIZE.height/3-50));
    auto rightMoveUp = MoveTo::create(1.5, Point(SCREAN_SIZE.width-rightFoot->getContentSize().width, SCREAN_SIZE.height/3+50));
    //组合
    auto rightAction = RepeatForever::create(Sequence::create(DelayTime::create(1.5), rightMoveUp, DelayTime::create(2.5), rightMoveDown, NULL));
    auto leftAction = RepeatForever::create(Sequence::create(DelayTime::create(1.5), leftMoveDown, DelayTime::create(2.5), leftMoveUp, NULL));
    leftFoot->runAction(leftEaseIn);
    leftFoot->runAction(leftAction);
    rightFoot->runAction(rightEaseIn);
    rightFoot->runAction(rightAction);
    
    return true;
}

void MainScene::onClick_play(Ref* p) {
    //跳转到开始游戏scene
    Director::getInstance()->replaceScene(CreateNailPolishScene::createScene());
}

void MainScene::onClick_help(Ref* p) {
    //跳转到帮助scene
    Director::getInstance()->replaceScene(FirstSceneOfHelp::createScene());
}
