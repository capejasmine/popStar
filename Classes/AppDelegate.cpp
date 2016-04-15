#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameController.hpp"
#include "Globle.hpp"
USING_NS_CC;
using namespace std;
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    glview->setDesignResolutionSize(720, 1280, ResolutionPolicy::NO_BORDER);
    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    DESIGN_SIZE =  Size(720, 1280);
    
    //set resource search path
    vector<string> searchPahts;
    searchPahts.push_back("background");
    searchPahts.push_back("config");
    searchPahts.push_back("fonts");
    searchPahts.push_back("particle");
    searchPahts.push_back("sounds");
    searchPahts.push_back("star");
    searchPahts.push_back("ui");
    searchPahts.push_back("cocos");
    searchPahts.push_back("animation");
    
    FileUtils::getInstance()->setSearchPaths(searchPahts);
    
    initDesignScale();
    
    // run
    GameController::getInstace()->enterLoading();

    return true;
}

void AppDelegate::initDesignScale() {
    REAL_SIZE = Director::getInstance()->getWinSize();
    
    float scalex = REAL_SIZE.width/DESIGN_SIZE.width;
    float scaley = REAL_SIZE.height/DESIGN_SIZE.height;
    
    DESIGN_SCALE = Point(scalex,scaley);
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
