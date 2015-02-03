#include "MenuScene.h"
#include "BoardScene.h"
#include "AboutScene.h"
#include "Setting.h"
#include "GameWorld.h"
#include "AtlasLoader.h"
//#include "HelloWorldScene.h"
#include "ui/UIImageView.h"
USING_NS_CC;

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MenuScene::init()
{
	if(!Layer::init()){
		return false;
	}

	auto node = CSLoader::createNode("MenuScene.csb");
	addChild(node);

	auto visibleSize = Director::getInstance()->getVisibleSize();

	start_btn	= dynamic_cast<ui::Button*>(node->getChildByName("Start_btn"));
	score_btn	= dynamic_cast<ui::Button*>(node->getChildByName("Score_btn"));
	setting_btn = dynamic_cast<ui::Button*>(node->getChildByName("Setting_btn"));
	about_btn	= dynamic_cast<ui::Button*>(node->getChildByName("About_btn"));

	start_btn->addClickEventListener([](Ref* sender){
		auto scene = GameWorld::createScene();
		auto trans = TransitionCrossFade::create(0.1f, scene);
		Director::getInstance()->replaceScene(trans);
	});

	score_btn->addClickEventListener([](Ref* sender){
		auto scene = BoardScene::createScene();
		auto trans = TransitionSlideInR::create(0.1f, scene);
		Director::getInstance()->replaceScene(trans);
	});

	setting_btn->addClickEventListener([](Ref* sender){
		auto scene = SettingScene::createScene();
		auto trans = TransitionSlideInR::create(0.1f, scene);
		Director::getInstance()->replaceScene(trans);
	});

	about_btn->addClickEventListener([](Ref* sender){
		auto scene = AboutScene::createScene();
		auto trans = TransitionSlideInR::create(0.1f, scene);
		Director::getInstance()->replaceScene(trans);
	});

	title = Sprite::create("title.png");
	title->setPosition(visibleSize.width/2, 800);
	addChild(title, 4);

	return true;
}