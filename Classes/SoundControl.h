#ifndef __SOUND_SCENE_H__
#define __SOUND_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
class SoundControl
{
public:
	static bool hasEffect;

	static SoundControl* getInstance();
	static void destroyInstance();
	
	void changeBgmState(bool hasBgm);
	void changeEffectState(bool hasBgm);

protected:
	bool init();
	SoundControl();
	static SoundControl* sharedSoundControl;
};

#endif