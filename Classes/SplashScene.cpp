#include "SplashScene.h"
#include "cocos2d.h"
#include "MenuScene.h"
#include "SoundControl.h"

USING_NS_CC;

Scene* SplashScene::createScene(){
	auto scene = Scene::create();
	auto layer = SplashScene::create();
	scene->addChild(layer);
	return scene;
}

bool SplashScene::init(){
	if(!Layer::init()){
		return false;
	}

	SoundControl::getInstance();


	auto node = CSLoader::createNode("SplashScene.csb");
	addChild(node);

	auto delay = DelayTime::create(1);
	auto callfunc = CallFunc::create([](){
		auto scene = MenuScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});

	//auto seq	= Sequence::create(delay, callfunc, nullptr);
	auto remove = RemoveSelf::create();
	auto seq	= Sequence::create(delay, remove, callfunc, nullptr);

	runAction(seq);

	return true;
}