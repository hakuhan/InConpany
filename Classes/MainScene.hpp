//
//  MainScene.hpp
//  meijia
//
//  Created by xcode31 on 16/8/17.
//
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include <cocos2d.h>
USING_NS_CC;

class MainScene : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(MainScene);
    
private:
    void onClick_play(Ref* p);
    void onClick_help(Ref* p);
};

#endif /* MainScene_hpp */
