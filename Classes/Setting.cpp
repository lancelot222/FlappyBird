#include "Setting.h"
#include "MenuScene.h"
#include "SoundControl.h"

Scene* SettingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SettingScene::create();
	scene->addChild(layer);
	return scene;
}

bool SettingScene::init()
{
	if(!Layer::init()){
		return false;
	}

	auto node = CSLoader::createNode("SettingScene.csb");
	addChild(node);

	return_btn = dynamic_cast<ui::Button*>(node->getChildByName("Return_btn"));

	return_btn->addClickEventListener([](Ref* sender){
		auto scene = MenuScene::createScene();
		auto trans = TransitionSlideInL::create(0.1f, scene);
		Director::getInstance()->replaceScene(trans);
	});

	bgm_box = dynamic_cast<ui::CheckBox*>(node->getChildByName("Music_cbox"));
	
	bgm_box->addClickEventListener([&](Ref* sender){
		SoundControl::getInstance()->changeBgmState(bgm_box->getSelectedState());
	});

	return true;
}
