//
//  CommonView.hpp
//  meijia
//
//  Created by xcode31 on 16/9/5.
//
//

#ifndef CommonView_hpp
#define CommonView_hpp

#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "DefaultHeader.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace ui;

class CommonView {
public:
    static CommonView* getInstance();
    Layout* getCommentView();
private:
    CommonView();
    static CommonView *commonView;
};


#endif /* CommonView_hpp */
