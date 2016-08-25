//
//  PaintingNailsScene.cpp
//  meijia
//
//  Created by xcode31 on 16/8/24.
//
//

#include "PaintingNailsScene.hpp"
#include "ui/CocosGUI.h"
#include "DefaultHeader.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;

Scene* PaintingNailsScene::createScene() {
    auto scene = Scene::create();
    auto layer = PaintingNailsScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool PaintingNailsScene::init() {
    if (!Layer::init()) {
        return false;
    }
    
    //初始化数据
    colors.bottle1 = UD->getStringForKey("b1Color", "0");
    colors.bottle2 = UD->getStringForKey("b2Color", "0");
    colors.bottle3 = UD->getStringForKey("b3Color", "0");
    colors.bottle4 = UD->getStringForKey("b4Color", "0");
    colors.bottle5 = UD->getStringForKey("b5Color", "0");
    isCleanBtnClicked = false;
    
    //设置界面
    auto node = CSLoader::createNodeWithVisibleSize("game/PaintingNails.csb");
    auto bg =(Layout *)(node->getChildByName("bg"));
    this->addChild(bg);
    //根据数据设置瓶子
    Sprite* bottle;
    int numberOfNullBttl = 0;
    if (colors.bottle1 != "0") {
        //设置第一个瓶子
        bottle = (Sprite *)(bg->getChildByName("bottle1"));
        bottle->setTexture(colors.bottle1);
        this->setBrushWithBottle(bottle);
    } else {
        numberOfNullBttl++;
    }
    
    if (colors.bottle2 != "0") {
        //设置第二个瓶子
        bottle = (Sprite *)(bg->getChildByName("bottle2"));
        bottle->setTexture(colors.bottle2);
        this->setBrushWithBottle(bottle);
    } else {
        numberOfNullBttl++;
    }
    
    if (colors.bottle3 != "0") {
        //设置第三个瓶子
        bottle = (Sprite *)(bg->getChildByName("bottle3"));
        bottle->setTexture(colors.bottle3);
        this->setBrushWithBottle(bottle);
    } else {
        numberOfNullBttl++;
    }
    
    if (colors.bottle4 != "0") {
        //设置第四个瓶子
        bottle = (Sprite *)(bg->getChildByName("bottle4"));
        bottle->setTexture(colors.bottle4);
        this->setBrushWithBottle(bottle);
    } else {
        numberOfNullBttl++;
    }
    
    if (colors.bottle5 != "0") {
        //设置第五个瓶子
        bottle = (Sprite *)(bg->getChildByName("bottle5"));
        bottle->setTexture(colors.bottle5);
        this->setBrushWithBottle(bottle);
    } else {
        numberOfNullBttl++;
    }
    
    //添加通知界面
    if (numberOfNullBttl == 5) {
        auto layout = Layout::create();
        layout->setBackGroundColor(Color3B(138, 43, 226));  //紫色
        layout->setContentSize(Size(SCREAN_SIZE.width*0.5, SCREAN_SIZE.height*0.5));
        layout->setAnchorPoint(Vec2(0.5, 0.5));
        layout->setPosition(Vec2(SCREAN_SIZE.width/2, SCREAN_SIZE.height/2));
        layout->setVisible(false);
        auto text = Text::create();
        text->setString("先创建第一瓶指甲油再试吧");
        text->setFontSize(36);
        text->setTextColor(Color4B(0, 0, 0, 255));
        text->setContentSize(Size(layout->getContentSize().width*0.5, layout->getContentSize().height*0.5));
        text->setPosition(Vec2(layout->getPosition().x*0.5, layout->getPosition().y*0.5));
        layout->addChild(text);
        this->addChild(layout);
        //动画
        auto scaleS = ScaleBy::create(0.1, 0.1);
        auto show = Show::create();
        auto scale = ScaleBy::create(0.3, 10);
        auto hide = Hide::create();
        layout->runAction(Sequence::create(scaleS, show, scale, DelayTime::create(1), scaleS->clone(), hide, NULL));
    }
    
    //其他界面
    auto polishBtn = (Button *)(node->getChildByName("polishBtn"));
    polishBtn->addClickEventListener(CC_CALLBACK_0(PaintingNailsScene::onClickPolishBtn, this));
    auto paintBtn = (Button *)(node->getChildByName("paintBtn"));
    this->addChild(paintBtn);
    this->addChild(polishBtn);
    //删除按钮
    std::string name;
    std::string fileName;
    for (int i = 1; i<6; i++) {
        fileName = StringUtils::format("b%dBtn", i);
        auto crossB = (Button *)(bg->getChildByName(fileName));
#define BASETAG 10
        crossB->addClickEventListener(CC_CALLBACK_0(PaintingNailsScene::onClickCrossBtnWithTag, this, BASETAG+i));
    }
    //清洁按钮
    auto cleanBtn = (Button *)(bg->getChildByName("cleanBottleBtn"));
    cleanBtn->addClickEventListener(CC_CALLBACK_0(PaintingNailsScene::onClickCleanBtn, this));
    //重置指甲按钮
    auto resetBtn = (Button *)(bg->getChildByName("resetBtn"));
    resetBtn->addClickEventListener(CC_CALLBACK_0(PaintingNailsScene::onClickResetBtn, this));
    
    return true;
}

//设置刷子
void PaintingNailsScene::setBrushWithBottle(Sprite *bottle) {
    //创建动画
    auto scaleS = ScaleBy::create(0.1, 1, 0.5);
    auto scaleB = ScaleBy::create(0.3, 1, 2);
    bottle->runAction(Sequence::create(scaleS, scaleB, NULL));
    
    Sprite* brush = (Sprite* )(bottle->getChildByName("brush"));
    Vec2 brushPosition = brush->getPosition();
    brush->setVisible(true);
#pragma mark 设置拖动刷子
    auto dragLisener = EventListenerTouchOneByOne::create();
    dragLisener->setSwallowTouches(true);
    
    dragLisener->onTouchBegan = [](Touch *touch, Event *event)->bool {
        //获取书简绑定的taget
        auto target = static_cast<Sprite *>(event->getCurrentTarget());
        //获取当前点击所在位置的坐标
        Point locationInNode = target->convertToNodeSpace((touch->getLocation()));
        Size s = target->getContentSize();
        Rect rect = Rect(0,0,s.width, s.height);
        
        if (rect.containsPoint(locationInNode)) {
            return true;
        }
        return false;
    };
    
    dragLisener->onTouchMoved = [](Touch *touch, Event *event) {
        //得到target
        auto target = static_cast<Sprite *>(event->getCurrentTarget());
        target->setPosition(target->getPosition() + touch->getDelta());
#pragma mark 碰撞检测
    };
    
    dragLisener->onTouchEnded = [brushPosition](Touch *touch, Event *event) {
        //还原刷子的位置
        auto target = static_cast<Sprite *>(event->getCurrentTarget());
        target->setPosition(brushPosition);
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(dragLisener, brush);
}

void PaintingNailsScene::onClickPolishBtn() {
    //返回材料界面
    Director::getInstance()->popScene();
}

//点击删除按钮
#pragma mark 删除按钮
void PaintingNailsScene::onClickCrossBtnWithTag(int tag) {
    //删除瓶子
    switch (tag) {
        case 11:
            //第1个
            break;
            
        case 12:
            //第2个
            break;
            
        case 13:
            //第3个
            break;
            
        case 14:
            //第4个
            break;
            
        case 15:
            //第5个
            break;

        default:
            break;
    }
}

//点击清理按钮
void PaintingNailsScene::onClickCleanBtn() {
#pragma mark 清理刷子的实现
    if (isCleanBtnClicked) {
        return;
    }
    isCleanBtnClicked = true;
    //弹出清理刷子
    auto bg = this->getChildByName("bg");
    auto conttonBall = bg->getChildByName("conttonBall");
    Vec2 positionOfConttonBall = conttonBall->getPosition();
    
    auto scaleS = ScaleBy::create(0.2, 0.5);
    auto scaleB = ScaleBy::create(0.3, 2);
    auto moveDown = MoveBy::create(0.2, Vec2(0, -conttonBall->getContentSize().height*0.5));
    auto moveUp = MoveBy::create(0.3, Vec2(0, conttonBall->getContentSize().height));
    auto spawn1 = Spawn::create(scaleS, moveDown, NULL);
    auto spawn2 = Spawn::create(scaleB, moveUp, NULL);
    conttonBall->runAction(Sequence::create(spawn1, DelayTime::create(0.3), spawn2, NULL));
    
    //设置触摸事件
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    
    listener1->onTouchBegan = [](Touch *touch, Event *event){
        // 获取事件所绑定的 target
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        
        // 获取当前点击点所在相对按钮的位置坐标
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        
        // 点击范围判断检测
        if (rect.containsPoint(locationInNode))
        {
            return true;
        }
        
        return false;
    };
    
    listener1->onTouchMoved = [](Touch *touch, Event *event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setPosition(target->getPosition() + touch->getDelta());
    };
    
    listener1->onTouchEnded = [positionOfConttonBall, this, listener1](Touch *touch, Event *event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setPosition(positionOfConttonBall);
        //移除监听
        this->_eventDispatcher->removeEventListener(listener1);
        this->isCleanBtnClicked = false;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, conttonBall);
}

//点击重置按钮
void PaintingNailsScene::onClickResetBtn() {
#pragma mark 重置按钮的实现
    //清空所有指甲上的指甲油
    log("重置指甲");
}