//
//  ThirdSceneOfHelp.hpp
//  meijia
//
//  Created by xcode31 on 16/8/19.
//
//

#ifndef ThirdSceneOfHelp_hpp
#define ThirdSceneOfHelp_hpp

#include <cocos2d.h>

class ThirdSceneOfHelp : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(ThirdSceneOfHelp);
    
private:
    void onClick_next();
    void onClick_nextScene();
};

#endif /* ThirdSceneOfHelp_hpp */
