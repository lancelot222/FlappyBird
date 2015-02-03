#ifndef __ABOUT_SCENE_H__
#define __ABOUT_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCSSceneReader.h"
#include "cocostudio/CCSGUIReader.h"
#include "ui/UIButton.h"

USING_NS_CC;
class AboutScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(AboutScene);

private:
	ui::Button* return_btn;
};

#endif