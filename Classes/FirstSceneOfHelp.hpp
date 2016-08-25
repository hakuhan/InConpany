//
//  FirstSceneOfHelp.hpp
//  meijia
//
//  Created by xcode31 on 16/8/17.
//
//

#ifndef FirstSceneOfHelp_hpp
#define FirstSceneOfHelp_hpp

#include "cocos2d.h"

class FirstSceneOfHelp : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(FirstSceneOfHelp);
    
private:
    void onClick_next();
};


#endif /* FirstSceneOfHelp_hpp */
