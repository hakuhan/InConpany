//
//  ThirdSceneOfHelp.cpp
//  meijia
//
//  Created by xcode31 on 16/8/19.
//

#include "ThirdSceneOfHelp.hpp"
#include "cocostudio/CocoStudio.h"
#include "DefaultHeader.h"
#include "ui/CocosGUI.h"
#include "CreateNailPolishScene.hpp"

USING_NS_CC;
using namespace ui;

Scene* ThirdSceneOfHelp::createScene() {
    auto* scene = Scene::create();
    auto* layer = ThirdSceneOfHelp::create();
    scene->addChild(layer);
    
    return scene;
}

bool ThirdSceneOfHelp::init() {
    if (!Layer::init()) {
        return false;
    }
    
    auto node = (Layer *)CSLoader::createNodeWithVisibleSize("Help/guidance_3.csb");
    //背景
    auto bg = node->getChildByName("bg");
    addChild(bg);
    //标题
    auto title = node->getChildByName("title");
    title->setPosition(TITLE_POSITION);
    addChild(title);
    //文字
    auto panel = node->getChildByName("Panel_1");
    panel->setContentSize(Size(SCREAN_SIZE.width/3, SCREAN_SIZE.height*0.8));
    addChild(panel);
    auto text = panel->getChildByName("Text_1");
    text->setContentSize(Size(panel->getContentSize().width, panel->getContentSize().height));
    text->setPosition(Vec2(30, panel->getContentSize().height*0.9));
    //动态图
    auto disk = node->getChildByName("disk");
    disk->setPosition(Vec2(SCREAN_SIZE.width, SCREAN_SIZE.height/2));
    addChild(disk);
    //下一步按钮
    auto nBtn = (Button *)(node->getChildByName("Button_1"));
    nBtn->setPosition(Vec2(SCREAN_SIZE.width-30, 30));
    nBtn->addClickEventListener(CC_CALLBACK_0(ThirdSceneOfHelp::onClick_next, this));
    nBtn->setVisible(true);
    addChild(nBtn);
    //跳转按钮
    auto nSceneB = (Button *)(node->getChildByName("Button_2"));
    nSceneB->setPosition(nBtn->getPosition());
    nSceneB->setVisible(false);
    nSceneB->addClickEventListener(CC_CALLBACK_0(ThirdSceneOfHelp::onClick_nextScene, this));
    addChild(nSceneB);
    //提示2
    auto panel2 = (Layout *)(node->getChildByName("Panel_2"));
    panel2->setContentSize(Size(SCREAN_SIZE.width/2, SCREAN_SIZE.height/4));
    panel2->setPosition(Vec2(SCREAN_SIZE.width-10, SCREAN_SIZE.height-10));
    addChild(panel2);
    panel2->setVisible(false);
    //脚
    auto leftFoot = node->getChildByName("leftFoot");
    auto rightFoot = node->getChildByName("rightFoot");
    leftFoot->setPosition(Vec2(leftFoot->getContentSize().width/2+30, -leftFoot->getContentSize().height/2));
    rightFoot->setPosition(Vec2(leftFoot->getContentSize().width*2+20, -rightFoot->getContentSize().height/2));
    addChild(leftFoot);
    addChild(rightFoot);
    //喷色说明
    auto info = Text::create();
    info->setString("拖动刷子到指甲上来涂上颜色吧");
    info->setFontSize(32);
    info->setColor(Color3B(255, 10, 10));
    info->setAnchorPoint(Vec2(0, 0));
    info->setPosition(Vec2(30, 60));
    info->setVisible(false);
#define INFO_TAG 10
    addChild(info, 5, INFO_TAG);
    
    return true;
}

void ThirdSceneOfHelp::onClick_next() {
    //显示提示
    auto panel2 = (Layout *)getChildByName("Panel_2");
    panel2->setVisible(true);
    //添加动画
    //云
    auto cloud = panel2->getChildByName("cloud");
    auto potHat = panel2->getChildByName("potHat");
    auto cMDistance = Vec2(potHat->getPositionX()-cloud->getPositionX()+potHat->getContentSize().width/2, potHat->getPositionY()-cloud->getPositionY());
    auto cMove = MoveBy::create(0.5, cMDistance);
    auto cMoveB = MoveBy::create(0.5, Vec2(-cMDistance.x, -cMDistance.y));
    auto cRepeat = RepeatForever::create(Sequence::create(cMove, DelayTime::create(0.5), cMoveB, DelayTime::create(1.5), NULL));
    cloud->runAction(cRepeat);
    //瓶盖
    auto hMoveD = MoveBy::create(0.1, Vec2(0, 10));
    auto hMoveU = MoveBy::create(0.1, Vec2(0, -10));
    auto hRepeat = RepeatForever::create(Sequence::create(DelayTime::create(0.5), hMoveD, hMoveU, hMoveD, hMoveU, hMoveD, hMoveU, DelayTime::create(1.9), NULL));
    potHat->runAction(hRepeat);
    //动态图
    auto disk = getChildByName("disk");
    auto dScale = ScaleBy::create(0.5, 0.5);
    auto dMove = MoveBy::create(0.5, Vec2(0, -SCREAN_SIZE.height/5));
    auto dSpawn = Spawn::create(dScale, dMove, NULL);
    disk->runAction(dSpawn);
    //隐藏按钮
    auto nBtn = (Button *)getChildByName("Button_1");
    auto nSceneB = (Button *)getChildByName("Button_2");
    nBtn->setVisible(false);
    nSceneB->setVisible(true);
    //隐藏提示1
    auto panel1 = (Layout *)getChildByName("Panel_1");
    panel1->setVisible(false);
    //显示脚
    auto leftFoot = getChildByName("leftFoot");
    auto rightFoot = getChildByName("rightFoot");
    auto lMoveIn = MoveBy::create(0.5, Vec2(0, leftFoot->getContentSize().height*1.5));
    auto rMoveIn = MoveBy::create(0.5, Vec2(0, rightFoot->getContentSize().height*1.5));
    leftFoot->runAction(lMoveIn);
    rightFoot->runAction(rMoveIn);
    //显示说明
    auto info = (Text *)getChildByTag(INFO_TAG);
    info->setVisible(true);
}

void ThirdSceneOfHelp::onClick_nextScene() {
    auto gameScene = CreateNailPolishScene::createScene();
    Director::getInstance()->replaceScene(gameScene);
}
