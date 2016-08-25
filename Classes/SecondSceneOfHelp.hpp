//
//  SecondSceneOfHelp.hpp
//  meijia
//
//  Created by xcode31 on 16/8/18.
//
//

#ifndef SecondSceneOfHelp_hpp
#define SecondSceneOfHelp_hpp

#include <cocos2d.h>
class SecondSceneOfHelp : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SecondSceneOfHelp);
    
private:
    void onClick_next();
};

#endif /* SecondSceneOfHelp_hpp */
