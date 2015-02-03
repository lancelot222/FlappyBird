#include "MenuScene.h"
#include "AboutScene.h"

Scene* AboutScene::createScene()
{
	auto scene = Scene::create();
	auto layer = AboutScene::create();
	scene->addChild(layer);
	return scene;
}

bool AboutScene::init()
{
	if(!Layer::init()){
		return false;
	}

	auto node = CSLoader::createNode("AboutScene.csb");
	addChild(node);

	return_btn = dynamic_cast<ui::Button*>(node->getChildByName("Return_btn"));

	return_btn->addClickEventListener([](Ref* sender){
		auto scene = MenuScene::createScene();
		auto trans = TransitionSlideInL::create(0.1f, scene);
		Director::getInstance()->replaceScene(trans);
	});

	return true;
}
