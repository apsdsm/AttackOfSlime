#include "AppDelegate.h"

// scenes
#include "scenes/StartMenuScene.h"
#include "scenes/GameScene.h"
#include "SceneManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;
using namespace AttackOfSlime;

AppDelegate::AppDelegate() 
{
}

AppDelegate::~AppDelegate() 
{
	// close the audio engine
	CocosDenshion::SimpleAudioEngine::getInstance()->end();
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
        glview = GLViewImpl::createWithRect("AttackOfSlime", Rect(0, 0, 640, 480));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(640, 480, ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	// add a search path for resources
    FileUtils::getInstance()->addSearchPath("res");

	// add sprite sheet to sprite cache
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile( "SpriteSheets/Characters.plist" );

	// precache music and sfx
	auto audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic( "Music/dungeon_bgm.wav" );
	audio->preloadBackgroundMusic( "Music/startmenu_bgm.wav" );

	audio->preloadEffect( "Sfx/dead_sfx.wav" );
	audio->preloadEffect( "Sfx/move_sfx.wav" );
	audio->preloadEffect( "Sfx/playerattack_sfx.wav" );
	audio->preloadEffect( "Sfx/slimeattack_sfx.wav" );

	// get reference to scene manager, then pass first scene
	sceneManager = SceneManager::getInstance();
	sceneManager->runWithScene( SceneManager::Scenes::StartMenu );

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
