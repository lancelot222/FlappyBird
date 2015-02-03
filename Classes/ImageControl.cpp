#include "ImageControl.h"

ImageControl* ImageControl::sharedImageControl = nullptr;

ImageControl* ImageControl::getInstance()
{
	if(sharedImageControl == nullptr){
		sharedImageControl = new ImageControl();
		if(!sharedImageControl->init()){
			delete sharedImageControl;
			sharedImageControl = nullptr;
			CCLOG("ERROR: Could not init ImageControl");
		}
	}
	return sharedImageControl;
}

void ImageControl::destroyInstance()
{
	CC_SAFE_DELETE(sharedImageControl);
}

ImageControl::ImageControl()
{

}

bool ImageControl::init()
{
	return true;
}

void ImageControl::addSpriteFramesWithFile(const char * file)
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(file);
}

Sprite * ImageControl::getSprite(const char * pic)
{
	auto sprFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pic);
	auto sizeTmp  = sprFrame->getOriginalSize();
	auto sprite	  = Sprite::createWithSpriteFrame(sprFrame);
	return sprite;
}