#ifndef __SET_SCENE_H__
#define __SET_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCSSceneReader.h"
#include "cocostudio/CCSGUIReader.h"
#include "ui/UIButton.h"
#include "ui/UICheckBox.h"

USING_NS_CC;
class SettingScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SettingScene);

private:
	ui::Button*		return_btn;
	ui::CheckBox*	bgm_box;
};

#endif