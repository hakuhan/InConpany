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
#include "Audio.hpp"
#include "IOSShareManager.h"

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
    //音乐
    Audio::getInstance()->playBgm(BGM);
    SETSOUND(true);
    SETEFFECT(true);
    //背景
    auto bg = (Layout *)(node->getChildByName("bg"));
    this->addChild(bg);
    //标题
    auto title = (Text *)bg->getChildByName("title");
    //play按钮
    auto playBtn = (Button *)(bg->getChildByName("startBtn"));
    playBtn->addClickEventListener(CC_CALLBACK_1(MainScene::onClick_play, this));
    //创建动态图片
    auto leftFoot = bg->getChildByName("leftFoot");
    auto rightFoot = bg->getChildByName("rightFoot");
    //移动
    auto leftMoveUp = MoveBy::create(1, Vec2(0, 100));
    auto leftMoveDown = MoveBy::create(1, Vec2(0, -100));
    auto rightMoveDown = MoveBy::create(1, Vec2(0, -100));
    auto rightMoveUp = MoveBy::create(1, Vec2(0, 100));
    //组合
    auto rightAction = RepeatForever::create(Sequence::create(DelayTime::create(1), rightMoveUp, DelayTime::create(1), rightMoveDown, rightMoveDown, DelayTime::create(1),rightMoveUp,NULL));
    auto leftAction = RepeatForever::create(Sequence::create(DelayTime::create(1), leftMoveDown, DelayTime::create(1), leftMoveUp, leftMoveUp, DelayTime::create(1),leftMoveDown, NULL));
    leftFoot->runAction(leftAction);
    rightFoot->runAction(rightAction);
    
    auto soundBtn = (Button *)(bg->getChildByName("soundBtn"));
    soundBtn->addClickEventListener([](Ref *p){
        //检查有没有开启声音
        if (ISSOUNDOPEN) {
            SETSOUND(false);
        } else {
            SETSOUND(true);
        }
        Audio::getInstance()->playBgm();
        //设置开关状态
    });
    //评论按钮
    auto commentBtn = (Button *)(bg->getChildByName("scoreBtn"));
    commentBtn->addClickEventListener([](Ref *p){
        //跳转评论
        Application::getInstance()->openURL("http://www.baidu.com");
    });
    //分享按钮
    auto shareBtn = (Button *)(bg->getChildByName("shareBtn"));
    shareBtn->addClickEventListener([](Ref *){
        //分享
        [[IOSShareManager getInstance] share];
    });
    auto moreGame = (Button *)(bg->getChildByName("moreGame"));
    moreGame->addClickEventListener([](Ref *p){
        //更多游戏
        Application::getInstance()->openURL("http://www.baidu.com");
    });
    //国际化
    if (Application::getInstance()->getCurrentLanguage() == LanguageType::CHINESE) {
        title->setString("美甲");
        playBtn->setTitleText("开始");
        soundBtn->setTitleText("声音");
        commentBtn->setTitleText("评论");
        shareBtn->setTitleText("分享");
        moreGame->setTitleText("更多");
    }
    return true;
}

void MainScene::onClick_play(Ref* p) {
    //跳转到开始游戏scene
    auto transition = TransitionFade::create(1, CreateNailPolishScene::createScene());
    Director::getInstance()->replaceScene(transition);
}