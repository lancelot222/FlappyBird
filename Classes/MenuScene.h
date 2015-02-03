#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCSSceneReader.h"
#include "cocostudio/CCSGUIReader.h"
#include "ui/UIButton.h"

USING_NS_CC;

class MenuScene : public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MenuScene);

private:
	ui::Button* start_btn;
	ui::Button* score_btn;
	ui::Button* setting_btn;
	ui::Button* about_btn;

	Sprite * title;
};

#endif