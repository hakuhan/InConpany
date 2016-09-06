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
#include "Audio.hpp"
#include "CommonView.hpp"

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
    //加载资源
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SecondSceneView/neils_1.plist", "SecondSceneView/neils_1.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SecondSceneView/neils_2.plist", "SecondSceneView/neils_2.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SecondSceneView/neils_3.plist", "SecondSceneView/neils_3.png");
    
    //设置界面
    auto node = CSLoader::createNodeWithVisibleSize("game/PaintingNails.csb");
    auto bg =(Layout *)(node->getChildByName("bg"));
    this->addChild(bg);
    //指甲位置
    for (int i = 0; i<10; i++) {
#pragma mark 设置脚趾坐标
        auto finger = (Sprite *)(bg->getChildByName("footBg")->getChildByName("foot")->getChildByName(StringUtils::format("%d", i+11)));
        neils.insert(i, finger);
        if (i<5) {
            names[i] = "";
        } else {
//            finger->setFlippedX(true);
        }
    }
    
    
    //根据数据设置瓶子
    Sprite* bottle;
    if (colors.bottle1 != "0") {
        //设置第一个瓶子
        bottle = (Sprite *)(bg->getChildByName("bottle1"));
        int strLen = (int)(colors.bottle1.length());
        names[0] = colors.bottle1;
        bottle->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(colors.bottle1.substr(0, strLen-1)));
        Sprite* brush = (Sprite* )(bottle->getChildByName("brush"));
        brush->setTag(10);
        this->setBrushWithBottle(bottle);
    }
    
    if (colors.bottle2 != "0") {
        //设置第二个瓶子
        bottle = (Sprite *)(bg->getChildByName("bottle2"));
        int strLen = (int)(colors.bottle2.length());
        names[1] = colors.bottle2;
        bottle->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(colors.bottle2.substr(0, strLen-1)));
        Sprite* brush = (Sprite* )(bottle->getChildByName("brush"));
        brush->setTag(11);
        this->setBrushWithBottle(bottle);
    }
    
    if (colors.bottle3 != "0") {
        //设置第三个瓶子
        bottle = (Sprite *)(bg->getChildByName("bottle3"));
        int strLen = (int)(colors.bottle3.length());
        names[2] = colors.bottle3;
        bottle->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(colors.bottle3.substr(0, strLen-1)));
        Sprite* brush = (Sprite* )(bottle->getChildByName("brush"));
        brush->setTag(12);
        this->setBrushWithBottle(bottle);
    }
    
    if (colors.bottle4 != "0") {
        //设置第四个瓶子
        bottle = (Sprite *)(bg->getChildByName("bottle4"));
        int strLen = (int)(colors.bottle4.length());
        names[3] = colors.bottle4;
        bottle->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(colors.bottle4.substr(0, strLen-1)));
        Sprite* brush = (Sprite* )(bottle->getChildByName("brush"));
        brush->setTag(13);
        this->setBrushWithBottle(bottle);
    }
    
    if (colors.bottle5 != "0") {
        //设置第五个瓶子
        bottle = (Sprite *)(bg->getChildByName("bottle5"));
        int strLen = (int)(colors.bottle5.length());
        names[4] = colors.bottle5;
        bottle->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(colors.bottle5.substr(0, strLen-1)));
        Sprite* brush = (Sprite* )(bottle->getChildByName("brush"));
        brush->setTag(14);
        this->setBrushWithBottle(bottle);
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
        auto bottom = bg->getChildByName(StringUtils::format("bottom%d", i));
        fileName = StringUtils::format("b%dBtn", i);
        auto crossB = (Button *)(bottom->getChildByName(fileName));
#define BASETAG 10
        crossB->addClickEventListener(CC_CALLBACK_0(PaintingNailsScene::onClickCrossBtnWithTag, this, BASETAG+i));
    }
    //清洁按钮
    auto cleanBtn = (Button *)(bg->getChildByName("cleanBottleBtn"));
    cleanBtn->addClickEventListener(CC_CALLBACK_0(PaintingNailsScene::onClickCleanBtn, this));
    //重置指甲按钮
    auto resetBtn = (Button *)(bg->getChildByName("resetBtn"));
    resetBtn->addClickEventListener(CC_CALLBACK_0(PaintingNailsScene::onClickResetBtn, this));
    //声音开关
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
    auto commentBtn = (Button *)(bg->getChildByName("scoreBtn"));
    commentBtn->addClickEventListener([](Ref *p){
        //评论
    });
    auto removeAddBtn = (Button *)(bg->getChildByName("rmBtn"));
    removeAddBtn->addClickEventListener([=](Ref *){
        //去广告
        auto view = CommonView::getInstance()->getCommentView();
#define ADSTAG 11
        this->addChild(view);
        view->setScale(0.1);
        auto scaleB = EaseInOut::create(ScaleBy::create(1, 10), 10);
        view->runAction(scaleB);
    });
    //国际化
    if (Application::getInstance()->getCurrentLanguage() == LanguageType::CHINESE) {
        soundBtn->setTitleText("声音");
        resetBtn->setTitleText("重置");
        commentBtn->setTitleText("评论");
        removeAddBtn->setTitleText("去广告");
    }
    
    return true;
}

#pragma mark 更新界面
void PaintingNailsScene::updateBottle() {
    auto bg =(Layout *)(this->getChildByName("bg"));
    //根据数据设置瓶子
    Sprite* bottle;
    if (colors.bottle1 == "0") {
        //设置第一个瓶子
        bottle = (Sprite *)(bg->getChildByName("bottle1"));
        bottle->setTexture("SecondSceneView/emptyB.png");
        names[0] = "";
        Sprite* brush = (Sprite* )(bottle->getChildByName("brush"));
        brush->setVisible(false);
    }
    
    if (colors.bottle2 == "0") {
        //设置第二个瓶子
        bottle = (Sprite *)(bg->getChildByName("bottle2"));
        bottle->setTexture("SecondSceneView/emptyB.png");
        names[1] = "";
        Sprite* brush = (Sprite* )(bottle->getChildByName("brush"));
        brush->setVisible(false);
    }
    
    if (colors.bottle3 == "0") {
        //设置第三个瓶子
        bottle = (Sprite *)(bg->getChildByName("bottle3"));
        bottle->setTexture("SecondSceneView/emptyB.png");
        names[2] = "";
        Sprite* brush = (Sprite* )(bottle->getChildByName("brush"));
        brush->setVisible(false);
    }
    
    if (colors.bottle4 == "0") {
        //设置第四个瓶子
        bottle = (Sprite *)(bg->getChildByName("bottle4"));
        bottle->setTexture("SecondSceneView/emptyB.png");
        names[3] = "";
        Sprite* brush = (Sprite* )(bottle->getChildByName("brush"));
        brush->setVisible(false);
    }
    
    if (colors.bottle5 == "0") {
        //设置第五个瓶子
        bottle = (Sprite *)(bg->getChildByName("bottle5"));
        bottle->setTexture("SecondSceneView/emptyB.png");
        names[4] = "";
        Sprite* brush = (Sprite* )(bottle->getChildByName("brush"));
        brush->setVisible(false);
    }
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
    auto dragLisener = EventListenerTouchOneByOne::create();
    dragLisener->setSwallowTouches(true);
    
    dragLisener->onTouchBegan = [](Touch *touch, Event *event)->bool {
        //获取绑定的taget
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
    
    dragLisener->onTouchMoved = [=](Touch *touch, Event *event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setPosition(target->getPosition() + touch->getDelta());

        //判断
        auto foot = this->getChildByName("bg")->getChildByName("footBg")->getChildByName("foot");
        Point location =foot->convertToNodeSpace(target->getParent()->convertToWorldSpace(target->getPosition()));
        //获取瓶子名字
        std::string potColor = names[target->getTag()-10];
        for (int i = 0; i<10; i++) {
            //判断是否拖上指甲
            if (neils.at(i)->getBoundingBox().containsPoint(location)) {
                //获取指甲名字
                std::string spriteName;
                if (i<5) {
                    //前五个
                    spriteName = StringUtils::format("SecondSceneView/%s-%d.png",potColor.substr(12, potColor.length()-17).c_str(),i+11);
                } /*else if (potColor.substr(12, potColor.length()-16) == "") {
                    
                
                } */else {
                    spriteName = StringUtils::format("SecondSceneView/%s-%d.png",potColor.substr(12, potColor.length()-17).c_str(),i+6);
                }
                //涂上颜色
                if (neils.at(i)->getSpriteFrame() != SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteName)) {
                    //清除闪光
                    if (neils.at(i)->getChildByTag(11) != NULL) {
                        neils.at(i)->removeChildByTag(11);
                    }
                    neils.at(i)->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteName));
                    auto blink = StringUtils::format("%s", potColor.substr(potColor.length()-1, 1).c_str());
                    Sprite *blinks;
                    if (blink == "1") {
                        //添加闪光
                        if (i<5) {
                            blinks = Sprite::createWithSpriteFrameName(StringUtils::format("SecondSceneView/%d-s.png", i+1));
                        } else {
                            blinks = Sprite::createWithSpriteFrameName(StringUtils::format("SecondSceneView/%d-s.png", i-4));
                        }
                    } else {
                        blinks = Sprite::create();
                    }
                    blinks->setTag(11);
                    neils.at(i)->addChild(blinks);
                    blinks->setPosition(Vec2(neils.at(i)->getContentSize().width/2, neils.at(i)->getContentSize().height/2));
                    //动画
                    Vector<SpriteFrame *> frames;
                    frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("SecondSceneView/effect1.png"));
                    frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("SecondSceneView/effect2.png"));
                    auto animation = Animation::createWithSpriteFrames(frames, 0.3, 1);
                    animation->setRestoreOriginalFrame(true);
                    auto animate = Animate::create(animation);
                    auto animateWithSound = Spawn::create(animate, CallFunc::create([=](){
                        //音效
                        Audio::getInstance()->playEffect(POP);
                    }), NULL);
                    blinks->runAction(animateWithSound);
                }
            }
        }
    };
    
    dragLisener->onTouchEnded = [brushPosition](Touch *touch, Event *event) {
        //还原刷子的位置
        auto target = static_cast<Sprite *>(event->getCurrentTarget());
        target->setPosition(brushPosition);
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(dragLisener, brush);
}

void PaintingNailsScene::onClickPolishBtn() {
    auto transition = TransitionFade::create(1, CreateNailPolishScene::createScene());
    //返回材料界面
    Director::getInstance()->replaceScene(transition);
}

//点击删除按钮
#pragma mark 删除按钮
void PaintingNailsScene::onClickCrossBtnWithTag(int tag) {
    //判断是否存在瓶子
    //删除瓶子
    switch (tag) {
        case 11:
            if (colors.bottle1 != "0") {
                colors.bottle1 = "0";
                UD->setStringForKey("b1Color", "0");
                this->updateBottle();
            }
            break;
            
        case 12:
            if (colors.bottle2 != "0") {
                colors.bottle2 = "0";
                UD->setStringForKey("b2Color", "0");
                this->updateBottle();
            }
            break;
            
        case 13:
            if (colors.bottle3 != "0") {
                colors.bottle3 = "0";
                UD->setStringForKey("b3Color", "0");
                this->updateBottle();
            }
            break;
            
        case 14:
            if (colors.bottle4 != "0") {
                colors.bottle4 = "0";
                UD->setStringForKey("b4Color", "0");
                this->updateBottle();
            }
            break;
            
        default:
            if (colors.bottle5 != "0") {
                colors.bottle5 = "0";
                UD->setStringForKey("b5Color", "0");
                this->updateBottle();
            }
            break;
    }
    
}

//点击清理按钮
void PaintingNailsScene::onClickCleanBtn() {
#pragma mark 清理刷子的实现
    //音效
    Audio::getInstance()->playEffect(POP);
    if (isCleanBtnClicked) {
        return;
    }
    isCleanBtnClicked = true;
    //弹出清理刷子
    auto bg = this->getChildByName("bg");
    auto conttonBall = bg->getChildByName("conttonBall");
    Vec2 positionOfConttonBall = conttonBall->getPosition();
    
    auto scaleS = ScaleBy::create(0.2, 0.5);
    auto scaleB = EaseBackInOut::create(ScaleBy::create(0.3, 2));
    auto moveDown = MoveBy::create(0.2, Vec2(0, -conttonBall->getContentSize().height/3));
    auto moveUp = MoveBy::create(0.3, Vec2(0, conttonBall->getContentSize().height));
    auto spawn1 = Spawn::create(scaleS, moveDown, NULL);
    auto spawn2 = Spawn::create(scaleB, CallFunc::create([](){
        //音效
        Audio::getInstance()->playEffect(MOVE);
    }), moveUp, NULL);
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
    
    listener1->onTouchMoved = [=](Touch *touch, Event *event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setPosition(target->getPosition() + touch->getDelta());
        //判断
        auto foot = this->getChildByName("bg")->getChildByName("footBg")->getChildByName("foot");
        Point location =foot->convertToNodeSpace(target->getPosition());
        //清除指甲
        for (int i = 0; i<10; i++) {
            if (neils.at(i)->getBoundingBox().containsPoint(location)) {
                //判断是否已经涂上
                SpriteFrame *originalSprite;
                if (i <= 4) {
                    originalSprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("SecondSceneView/L%d.png",i+1));
                } else {
                    originalSprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("SecondSceneView/L%d.png",i-4));
                }
                if (neils.at(i)->getSpriteFrame() != originalSprite) {
                    neils.at(i)->setSpriteFrame(originalSprite);
                    //清除闪光
                    auto t = neils.at(i)->getChildByTag(11);
                    if (t != NULL) {
                        
                        t->removeFromParent();
                    }
                    //音效
                    Audio::getInstance()->playEffect(POP);
                }
            }
        }
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
    for (int i = 1; i <= 10; i++) {
        SpriteFrame *originalSprite;
        if (i <= 5) {
            originalSprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("SecondSceneView/L%d.png",i));
        } else {
            originalSprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("SecondSceneView/L%d.png",i-5));
        }
        neils.at(i-1)->setSpriteFrame(originalSprite);
        if (neils.at(i-1)->getChildByTag(11) != NULL) {
            neils.at(i-1)->removeChildByTag(11);
        }
    }
}