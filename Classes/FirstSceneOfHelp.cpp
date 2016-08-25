//
//  FirstSceneOfHelp.cpp
//  meijia
//
//  Created by xcode31 on 16/8/17.
//
//

#include "FirstSceneOfHelp.hpp"
#include "ui/CocosGUI.h"
#include "DefaultHeader.h"
#include "cocostudio/CocoStudio.h"
#include "SecondSceneOfHelp.hpp"

USING_NS_CC;
using namespace ui;

Scene* FirstSceneOfHelp::createScene() {
    auto scene = Scene::create();
    auto layer = FirstSceneOfHelp::create();
    scene->addChild(layer);
    
    return scene;
}

bool FirstSceneOfHelp::init() {
    if (!Layer::init()) {
        return false;
    }
    //添加背景
    auto bg = Sprite::create("HelloWorld.png");
    bg->setPosition(SCREAN_SIZE.width/2, SCREAN_SIZE.height/2);
    addChild(bg);
    
    //标题
    auto node = CSLoader::createNodeWithVisibleSize("Help/discrib.csb");
    auto title = (Sprite *)(node->getChildByName("title"));
    title->setPosition(TITLE_POSITION);
    addChild(title);
    
    //创建描述层
    auto black_lay = Layout::create();
    black_lay->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    black_lay->setBackGroundColor(Color3B::BLACK);
    black_lay->setBackGroundColorOpacity(100);//255
    black_lay->setPosition(Vec2(20, 0));
    black_lay->setContentSize(Size(SCREAN_SIZE.width/3, SCREAN_SIZE.height*2/3));
    addChild(black_lay, 5);
    
    //创建文字
    auto text1 = (Text*)(node->getChildByName("Text_1"));
    text1->setFontSize(50);
    text1->setContentSize(cocos2d::Size(black_lay->getContentSize().width, 200));
    text1->setPosition(Vec2(text1->getContentSize().width/2, black_lay->getContentSize().height-text1->getContentSize().height/2));
    
    auto text2 = (Text*)(node->getChildByName("Text_2"));
    text2->setFontSize(50);
    text2->setContentSize(text1->getContentSize());
    text2->setPosition(Vec2(text2->getContentSize().width/2, text1->getPositionY()-text1->getContentSize().height/2));
    
    black_lay->addChild(text1);
    black_lay->addChild(text2);
    
    //演示
    auto panel_A = (Sprite *)(node->getChildByName("Panel_A"));
    panel_A->setAnchorPoint(Vec2(1, 1));
    panel_A->setPosition(Vec2(SCREAN_SIZE.width-10, SCREAN_SIZE.height-10));
    auto panel_B = (Sprite *)(node->getChildByName("Panel_B"));
    panel_B->setAnchorPoint(Vec2(1, 1));
    panel_B->setPosition(Vec2(SCREAN_SIZE.width-10, SCREAN_SIZE.height-panel_A->getContentSize().height/2-20));
    addChild(panel_A, 5);
    addChild(panel_B, 5);
    //A图
    auto podA = (Sprite *)(panel_A->getChildByName("little_pod_a"));
    auto podA_1 = panel_A->getChildByName("Pot_A");
    //放缩
    auto scaleX = ScaleTo::create(0.3, 1.5, 1);
    auto scaleX_2 = ScaleTo::create(0.1, 1, 1);
    //移动,旋转
    auto podAMove = Vec2(podA_1->getPositionX()-podA->getPositionX(), podA_1->getPositionY()-podA->getPositionY());
    auto podA_move = MoveBy::create(0.5, podAMove);
    auto podA_Rotate = RotateBy::create(0.5, 90);
    auto podA_rotateB = RotateBy::create(0.5, -90);
    auto podA_moveB = MoveBy::create(0.5, Vec2(-podAMove.x, -podAMove.y));
    //组合
    auto spawnA = Spawn::create(podA_rotateB, podA_moveB, NULL);
    auto podA_action = RepeatForever::create(Sequence::create(scaleX, scaleX_2, DelayTime::create(0.5), podA_move,  podA_Rotate, DelayTime::create(0.5), spawnA, DelayTime::create(0.5), NULL));
    podA->runAction(podA_action);
    
    //B图
    auto podB_1 = (Sprite *)(panel_B->getChildByName("little_pod_b"));
    auto podB_1_1 = (Sprite *)(panel_B->getChildByName("podB_1_1"));
    auto podB_2 = (Sprite *)
    (panel_B->getChildByName("little_pod_b2"));
    auto podB_3 = panel_B->getChildByName("Pot_B");
    //盖子移动
    auto b11Move = MoveBy::create(0.5, Vec2(0, 40));
    auto b11MoveB = MoveBy::create(0.1, Vec2(0, -40));
    auto b11FadeOut = FadeOut::create(0.1);
    auto b11FadeIn = FadeIn::create(0);
    auto b11Sqnc = RepeatForever::create(Sequence::create(b11Move, b11FadeOut, b11MoveB, DelayTime::create(1.6), b11FadeIn, DelayTime::create(2.1), NULL));
    podB_1_1->runAction(b11Sqnc);
    //瓶子1
    auto b1MDistance = Vec2(podB_3->getPositionX()-podB_1->getPositionX(), podB_3->getPositionY()-podB_1->getPositionY());
    auto b1Move = MoveBy::create(0.5, b1MDistance);
    auto b1Rotate = RotateBy::create(0.2, 90);
    auto b1Shake1 = MoveBy::create(0.1, Vec2(5, 0));
    auto b1Shake2 = MoveBy::create(0.1, Vec2(-5, 0));
    auto b1MoveB = MoveBy::create(0.5, Vec2(-b1MDistance.x, -b1MDistance.y));
    auto b1RotateB = RotateBy::create(0.5, -90);
    auto b1Spawn = Spawn::create(b1RotateB, b1MoveB, NULL);
    auto b1Sqnc = RepeatForever::create(Sequence::create(DelayTime::create(0.7) ,b1Move, b1Rotate, b1Shake1, b1Shake2, b1Shake1, b1Shake2, b1Spawn, DelayTime::create(2.1), NULL));
    podB_1->runAction(b1Sqnc);
    //瓶子2
    auto b2MDistance = Vec2(podB_3->getPositionX()-podB_2->getPositionX(), podB_3->getPositionY()-podB_2->getPositionY());
    auto b2MoveUp = MoveBy::create(0.1, Vec2(0, 10));
    auto b2Shake1 = RotateBy::create(0.1, 10);
    auto b2Shake2 = RotateBy::create(0.1, -10);
    auto b2Rotate = RotateBy::create(0.5, 90);
    auto b2Move = MoveBy::create(0.5, b2MDistance);
    auto b2MoveB = MoveBy::create(0.5, Vec2(-b2MDistance.x, -b2MDistance.y));
    auto b2RotateB = RotateBy::create(0.5, -90);
    auto b2Spawn1 = Spawn::create(b2Move, b2Rotate, NULL);
    auto b2Spawn2 = Spawn::create(b2MoveB, b2RotateB, NULL);
    auto b2Sqnc = RepeatForever::create(Sequence::create(DelayTime::create(2.4), b2MoveUp, b2Shake1, b2Shake2, b2Shake1, b2Shake2, b2Spawn1, DelayTime::create(0.5) ,b2Spawn2, NULL));
    podB_2->runAction(b2Sqnc);
    
    
    //按钮
    auto next_btn = (Button *)(node->getChildByName("next_button"));
    next_btn->setPosition(Vec2(SCREAN_SIZE.width-50, 50));
    next_btn->addClickEventListener(CC_CALLBACK_0(FirstSceneOfHelp::onClick_next, this));
    addChild(next_btn, 5);
    
    return true;
}

void FirstSceneOfHelp::onClick_next() {
    //跳转到第二个帮助页面
    auto seconScene = SecondSceneOfHelp::createScene();
    Director::getInstance()->replaceScene(seconScene);
}
