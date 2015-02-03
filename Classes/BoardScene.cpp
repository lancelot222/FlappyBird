#include "MenuScene.h"
#include "BoardScene.h"
#include "ScoreData.h"
#include "ui/UITextField.h"
#include "ui/UIText.h"
#include "ui/UITextAtlas.h"
#include "ui/UIListView.h"
#include "base/CCUserDefault.h"
#include <vector>

Scene* BoardScene::createScene()
{
	auto scene = Scene::create();
	auto layer = BoardScene::create();
	scene->addChild(layer);
	return scene;
}

bool BoardScene::init()
{
	if(!Layer::init()){
		return false;
	}

	auto node = CSLoader::createNode("BoardScene.csb");
	addChild(node);

	
	ScoreDate::getInstance()->getWanted();

	char str[20];
	/*ui::Text * tttf = dynamic_cast<ui::Text*>(node->getChildByName("text"));
	if(tttf == nullptr){
		CCLOG("NULL");
	}
	else{
		tttf->setText(std::string("AAAAAAAAAAAAA"));
		CCLOG("NOT NULL");
	}*/

	ui::Text * tttf = nullptr;
	ui::ListView *lview = dynamic_cast<ui::ListView*>(node->getChildByName("ListView_1"));

	for (int i = 1; i <= 12; i++)
	{
		sprintf(str, "ttt%d", i);
		CCLOG(str);
		tttf = dynamic_cast<ui::Text*>(lview->getChildByName(str));
		sprintf(str, "%d", ScoreDate::getInstance()->numbers[i-1]);
		std::string ss = ScoreDate::getInstance()->names[i-1] + "  " + std::string(str);
		CCLOG(ss.c_str());

		if(tttf == nullptr){
			CCLOG("NULL");
		}
		else{
			tttf->setText(ss);
			tttf->setFontSize(50);
			CCLOG("NOT NULL");
		}
		
	}


	return_btn = dynamic_cast<ui::Button*>(node->getChildByName("Return_btn"));
	

	return_btn->addClickEventListener([](Ref* sender){
		auto scene = MenuScene::createScene();
		auto trans = TransitionSlideInL::create(0.1f, scene);
		Director::getInstance()->replaceScene(trans);
	});

	return true;
}
