//
//  CommonView.cpp
//  meijia
//
//  Created by xcode31 on 16/9/5.
//
//

#include "CommonView.hpp"
#include "IAPManager.h"
using namespace ui;

CommonView* CommonView::getInstance() {
    if (commonView == NULL) {
        commonView = new CommonView();
    }
    return commonView;
}

CommonView* CommonView::commonView = NULL;

CommonView::CommonView(){
    
}

Layout* CommonView::getCommentView() {
    auto layout = CSLoader::createNodeWithVisibleSize("commonViews/rmAds.csb");
    auto view = (Layout *)(layout->getChildByName("bg"));
    //按钮
    auto restoreBtn = (Button *)(view->getChildByName("restoreB"));
    auto removeBtn = (Button *)(view->getChildByName("removeBtn"));
    auto title = (Text *)(view->getChildByName("title"));
    //国际化
    if (Application::getInstance()->getCurrentLanguage() == LanguageType::CHINESE) {
        restoreBtn->setTitleText("恢复");
        removeBtn->setTitleText("购买");
        title->setString("广告很烦人吧？你可以选择去掉它");
    }
    
    view->setTouchEnabled(true);
    auto black_lay = Layout::create();
    black_lay->setContentSize(SCREAN_SIZE);
    black_lay->setAnchorPoint(Vec2(0.5, 0.5));
    black_lay->setPosition(Vec2(SCREAN_SIZE.width/2, SCREAN_SIZE.height/2));
    black_lay->setTouchEnabled(true);
    black_lay->addChild(view);
    black_lay->addClickEventListener([=](Ref* p){
        auto scaleS = Sequence::create(EaseIn::create(ScaleBy::create(1, 0.1), 10), CallFunc::create([black_lay](){
            black_lay->removeFromParent();
        }), NULL);
        black_lay->runAction(scaleS);
    });
    restoreBtn->addClickEventListener([black_lay](Ref *p){
        //恢复购买
        IAPManager *manager = [IAPManager getInstance];
        [manager restorePurchases];
        
        //界面消失
        auto scaleS = Sequence::create(EaseIn::create(ScaleBy::create(1, 0.1), 10), CallFunc::create([black_lay](){
            black_lay->removeFromParent();
        }), NULL);
        black_lay->runAction(scaleS);
    });
    removeBtn->addClickEventListener([black_lay](Ref *p){
        //购买商品
        int produceIndex = 0;   //商品
        IAPManager *manager = [IAPManager getInstance];
        [manager purchaseProduct:produceIndex];
        
        //界面消失
        auto scaleS = Sequence::create(EaseIn::create(ScaleBy::create(1, 0.1), 10), CallFunc::create([black_lay](){
            black_lay->removeFromParent();
        }), NULL);
        black_lay->runAction(scaleS);
    });
    return black_lay;
}