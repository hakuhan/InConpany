//
//  SecondSceneOfHelp.cpp
//  meijia
//
//  Created by xcode31 on 16/8/18.
//
//

#include "SecondSceneOfHelp.hpp"
#include "cocostudio/CocoStudio.h"
#include "DefaultHeader.h"
#include "ui/CocosGUI.h"
#include "ThirdSceneOfHelp.hpp"

USING_NS_CC;
using namespace ui;

Scene* SecondSceneOfHelp::createScene() {
    auto* scene = Scene::create();
    auto* layer = SecondSceneOfHelp::create();
    scene->addChild(layer);
    
    return scene;
}

bool SecondSceneOfHelp::init() {
    if (!Layer::init()) {
        return false;
    }
    //获取层
    auto node = CSLoader::createNodeWithVisibleSize("Help/guidance_2.csb");
    //背景
    auto bg = node->getChildByName("bg");
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(0, 0);
    addChild(bg);
    //描述文字
    auto textLayout = (Layout *)(node->getChildByName("text_Panel"));
    textLayout->setContentSize(cocos2d::Size(SCREAN_SIZE.width*0.4, SCREAN_SIZE.height*0.8));
    textLayout->setPosition(Vec2(20, 0));
    addChild(textLayout);
    auto text = (Text *)(textLayout->getChildByName("Text_1"));
    text->setAnchorPoint(Vec2(0, 1));
    text->setContentSize(textLayout->getContentSize());
    text->setPosition(Vec2(0, textLayout->getContentSize().height));
    //标题
    auto title = node->getChildByName("title");
    title->setAnchorPoint(Vec2(0, 1));
    title->setPosition(TITLE_POSITION);
    addChild(title);
    //添加云
    auto cloud = node->getChildByName("cloud");
    cloud->setAnchorPoint(Vec2(1, 0.5));
    cloud->setPosition(Vec2(SCREAN_SIZE.width, SCREAN_SIZE.height/2));
    addChild(cloud);
    //添加动画
    auto pod1 = cloud->getChildByName("pod1");
    auto pod2 = cloud->getChildByName("pod2");
    //缩放
    auto scaleS = ScaleBy::create(0.2, 1, 0.5);
    auto scaleB = ScaleBy::create(0.1, 1, 2);
    //位移
    auto moveDistance = Vec2(pod1->getPositionX()-pod2->getPositionX(), pod1->getPositionY()-pod2->getPositionY());
    auto pod2Move = MoveBy::create(0.5, moveDistance);
    auto moveB = MoveBy::create(0.5, Vec2(-moveDistance.x, -moveDistance.y));
    //旋转
    auto pod2Rotate = RotateBy::create(0.5, 90);
    auto rotateB = RotateBy::create(0.5, -90);
    //组合
    auto pod2Spawn1 = Spawn::create(pod2Move, pod2Rotate, NULL);
    auto pod2Spawn2 = Spawn::create(moveB, rotateB, NULL);
    auto pod2Sqnc = Sequence::create(scaleS, scaleB, pod2Spawn1, DelayTime::create(1), pod2Spawn2, DelayTime::create(0.5) ,NULL);
    auto pod2Repeat = RepeatForever::create(pod2Sqnc);
    pod2->runAction(pod2Repeat);
    //按钮
    auto nBtn = (Button* )(node->getChildByName("nextBtn"));
    nBtn->setAnchorPoint(Vec2(1, 0));
    nBtn->setPosition(Vec2(SCREAN_SIZE.width-30, 30));
    nBtn->addClickEventListener(CC_CALLBACK_0(SecondSceneOfHelp::onClick_next, this));
    addChild(nBtn);
    
    return true;
}

void SecondSceneOfHelp::onClick_next() {
    auto thirdScene = ThirdSceneOfHelp::createScene();
    Director::getInstance()->replaceScene(thirdScene);
}