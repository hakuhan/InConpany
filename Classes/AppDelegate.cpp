#include "AppDelegate.h"
#include "MainScene.hpp"
#include "DefaultHeader.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("meijia", Rect(0, 0, 1920, 1440));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(1920, 1440, ResolutionPolicy::FIXED_WIDTH);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");
    FileUtils::getInstance()->addSearchPath("res/firstSceneView");
    // create a scene. it's an autorelease object
    auto scene = MainScene::createScene();
    auto spriteFrameCatche = SpriteFrameCache::getInstance();
    spriteFrameCatche->addSpriteFramesWithFile("left.plist", "left.png");
    spriteFrameCatche->addSpriteFramesWithFile("rightFrameAction.plist", "rightFrameAction.png");
    spriteFrameCatche->addSpriteFramesWithFile("efectsImage.plist", "efectsImage.png");
    spriteFrameCatche->addSpriteFramesWithFile("commonViews/bottles1.plist", "commonViews/bottles1.png");
    spriteFrameCatche->addSpriteFramesWithFile("commonViews/bottles2.plist", "commonViews/bottles2.png");
    spriteFrameCatche->addSpriteFramesWithFile("commonViews/bottles3.plist", "commonViews/bottles3.png");
    spriteFrameCatche->addSpriteFramesWithFile("commonViews/bottles4.plist", "commonViews/bottles4.png");
    spriteFrameCatche->addSpriteFramesWithFile("commonViews/bottles5.plist", "commonViews/bottles5.png");
    // run
    director->runWithScene(scene);
    
    bool isAddExists = UD->getBoolForKey(ISADDEXITS, true);
    if (isAddExists) {
        //TODO
        //开启广告
        
    }
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
