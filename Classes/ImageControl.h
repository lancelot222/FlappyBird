#ifndef __IMAGE_SCENE_H__
#define __IMAGE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
class ImageControl
{
public:
	static ImageControl* getInstance();
	static void destroyInstance();

	void addSpriteFramesWithFile(const char *);
	Sprite * getSprite(const char *);


protected:
	bool init();
	ImageControl();
	static ImageControl* sharedImageControl;
};

#endif