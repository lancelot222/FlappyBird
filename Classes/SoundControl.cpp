#include "SoundControl.h"
#include "SimpleAudioEngine.h"

using namespace std;

SoundControl* SoundControl::sharedSoundControl = nullptr;
bool SoundControl::hasEffect = true;

SoundControl* SoundControl::getInstance()
{
	if(sharedSoundControl == nullptr){
		sharedSoundControl = new SoundControl();
		if(!sharedSoundControl->init()){
			delete sharedSoundControl;
			sharedSoundControl = nullptr;
			CCLOG("ERROR: Could not init SoundControl");
		}
	}
	return sharedSoundControl;
}

void SoundControl::destroyInstance()
{
	CC_SAFE_DELETE(sharedSoundControl);
}

SoundControl::SoundControl()
{

}

bool SoundControl::init()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bg.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bg.mp3", true);

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_die.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_hit.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_point.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_swooshing.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_wing.mp3");

	return true;
}

void SoundControl::changeBgmState(bool hasBgm)
{
	if(!hasBgm){
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bg.mp3", true);
	}else{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
	}
}

void SoundControl::changeEffectState(bool bEffect)
{
	hasEffect = !bEffect;
}