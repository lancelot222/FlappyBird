#ifndef __BOARD_SCENE_H__
#define __BOARD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCSSceneReader.h"
#include "cocostudio/CCSGUIReader.h"
#include "ui/UIButton.h"

USING_NS_CC;
class BoardScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(BoardScene);

private:
	ui::Button* return_btn;
};

#endif