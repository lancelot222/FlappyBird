#include "GameWorld.h"
#include "ImageControl.h"
#include "AtlasLoader.h"
#include "Box2D/Box2D.h"
#include "cstdlib"
#include "ctime"
#include "SimpleAudioEngine.h"
#include "ScoreData.h"
#include "BoardScene.h"

Scene* GameWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	
	scene->getPhysicsWorld()->setGravity(Vect(0, -1500));

	auto layer = GameWorld::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->addChild(layer);


	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width/2, visibleSize.height/2+235));
	edgeNode->setPhysicsBody(body);
	edgeNode->getPhysicsBody()->setContactTestBitmask(1);
	scene->addChild(edgeNode);


	return scene;
}

bool GameWorld::init()
{
	if(!Layer::init()){
		return false;
	}

	srand(unsigned(time(0)));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	ImageControl::getInstance()->addSpriteFramesWithFile("flappy_packer.plist");

	//add background
	auto spBackground = Sprite::create("background.png");
	auto layerBackground = Layer::create();
	layerBackground->addChild(spBackground);
	layerBackground->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	addChild(layerBackground, 1);

	

	//ground
	spGorund = Sprite::create("ground.png");
	spGorund2 = Sprite::create("ground.png");

	spGorund->setPosition(Vec2(spGorund->getContentSize().width/2, spGorund->getContentSize().height/8*3));
	spGorund2->setPosition(Vec2(spGorund2->getContentSize().width, spGorund2->getContentSize().height/8*3));
	addChild(spGorund, 3);
	addChild(spGorund2, 3);

	auto movetogogo = MoveTo::create(3.0f, Vec2(0, spGorund->getContentSize().height/8*3));
	auto movetoback = MoveTo::create(0.0f, Vec2(spGorund->getContentSize().width/2, spGorund->getContentSize().height/8*3));
	auto moveground = Sequence::create(movetogogo, movetoback, nullptr);
	spGorund->runAction(RepeatForever::create(moveground));

	auto movetogogo2 = MoveTo::create(3.0f, Vec2(spGorund->getContentSize().width/2, spGorund->getContentSize().height/8*3));
	auto movetoback2 = MoveTo::create(0.0f, Vec2(spGorund->getContentSize().width, spGorund->getContentSize().height/8*3));
	auto moveground2 = Sequence::create(movetogogo2, movetoback2, nullptr);
	spGorund2->runAction(RepeatForever::create(moveground2));

	speed = (spGorund->getContentSize().width/2)  /60.0 / 3.0;

	auto cache = Director::getInstance()->getTextureCache();
	cache->addImageAsync("atlas.png", CC_CALLBACK_1(GameWorld::loadingCallBack, this));


	return true;
}

void GameWorld::loadingCallBack(Texture2D *texture)
{
	AtlasLoader::getInstance()->loadAtlas("atlas.txt", texture);


	

	beforeStart();

	
}

void GameWorld::beforeStart()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	animation->addSpriteFrame( AtlasLoader::getInstance()->getSpriteFrameByName("bird2_0") );
	animation->addSpriteFrame( AtlasLoader::getInstance()->getSpriteFrameByName("bird2_1") );
	animation->addSpriteFrame( AtlasLoader::getInstance()->getSpriteFrameByName("bird2_2") );
	auto animate = Animate::create(animation);

	bird = Sprite::createWithSpriteFrame( AtlasLoader::getInstance()->getSpriteFrameByName("bird2_0") );
	bird->runAction(RepeatForever::create(animate));
	bird->setPosition(Vec2(visibleSize.width/2 - 150, visibleSize.height/2+93));
	bird->setScale(2.0f);

	addChild(bird, 4);

	getReady = Sprite::createWithSpriteFrame( AtlasLoader::getInstance()->getSpriteFrameByName("text_ready"));
	getReady->setScale(2.0f);
	getReady->setPosition(visibleSize.width/2.0f, 700.0f);
	addChild(getReady, 4);

	reStart = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	reStart->setScale(2.0f);
	reStart->setPosition(visibleSize.width/4.0f + 50, 300.0f);
	reStart->setVisible(false);
	addChild(reStart, 4);

	scoreBoard = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_score"));
	scoreBoard->setScale(2.0f);
	scoreBoard->setPosition(visibleSize.width/4.0f * 3 - 50, 300.0f);
	scoreBoard->setVisible(false);
	addChild(scoreBoard, 4);

	gameOver = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("text_game_over"));
	gameOver->setScale(2.0f);
	gameOver->setPosition(visibleSize.width/2.0f, 700.0f);
	gameOver->setVisible(false);
	addChild(gameOver, 4);

	scorePanel = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("score_panel"));
	scorePanel->setScale(2.0f);
	scorePanel->setPosition(visibleSize.width/2.0f, 500.0f);
	scorePanel->setVisible(false);
	addChild(scorePanel, 4);

	spTutorial = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("tutorial"));
	spTutorial->setScale(2.0f);
	spTutorial->setPosition(visibleSize.width/2.0f, 500.0f);
	addChild(spTutorial, 4);

	GameState = 1;
	

	auto listener = EventListenerMouse::create();
	listener->onMouseDown = [=](Event* event){

		if(GameState == 1){
			GameState = 2;
			getReady->setVisible(false);
			spTutorial->setVisible(false);
			startGame();
		}else if(GameState == 3){
			return;
		}

		bird->getPhysicsBody()->setVelocity(Vec2(0, 500));

		auto curVelocity = bird->getPhysicsBody()->getVelocity();
		bird->setRotation(-curVelocity.y*0.1 - 20);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_wing.mp3");
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	m_iScore = 0;
	initNumber();



	//startGame();
}



void GameWorld::initNumber()
{
	std::string str("number_context_0");
	char tmp;

	for (int i = 0; i < 10; i++)
	{
		tmp = '0'+i-0;
		numbers[i] = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName((str + tmp).c_str()));
		//numbers[i]->setPosition(visibleSize.width/2 - numbers[i]->getContentSize().width/2 - 10, 800.0f);
		numbers2[i] = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName((str + tmp).c_str()));
		//numbers2[i]->setPosition(visibleSize.width/2 + numbers[i]->getContentSize().width/2 + 10, 800.0f);

		numbers[i]->setScale(2.0f); numbers2[i]->setScale(2.0f);
		numbers[i]->setVisible(false); numbers2[i]->setVisible(false);
		addChild(numbers[i], 5); addChild(numbers2[i], 5);
	}
	numbers[m_iScore]->setVisible(true);
	numbers[m_iScore]->setPosition(visibleSize.width/2, 800.0f);
}

void GameWorld::startGame()
{
	bird->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	auto body = PhysicsBody::createCircle(bird->getContentSize().width/2+5);
	bird->setPhysicsBody(body);
	bird->getPhysicsBody()->setContactTestBitmask(1);
	scheduleUpdate();


	pipes[0] = Node::create();
	pipes[1] = Node::create();
	for (int i = 0; i < 2; i++)
	{
		auto pipeUp		= Sprite::createWithSpriteFrame( AtlasLoader::getInstance()->getSpriteFrameByName("pipe_up"));
		auto pipeDown	= Sprite::createWithSpriteFrame( AtlasLoader::getInstance()->getSpriteFrameByName("pipe_down"));

		
		
		//pipeUpBody->setContactTestBitmask(1);
		pipeUp->setScale(2.0f);
		pipeUp->setPosition(0, 200);

		auto pipeUpBody = PhysicsBody::createBox(pipeUp->getContentSize()*2);
		pipeUpBody->setDynamic(false);
		pipeUp->setPhysicsBody(pipeUpBody);
		pipeUp->getPhysicsBody()->setContactTestBitmask(1);

		//addChild(pipeUp, 3);
		

		
		//pipeUpBody->setContactTestBitmask(1);
		pipeDown->setPosition(0, 200+DIS_PIPE);
		pipeDown->setScale(2.0f);

		auto pipeDownBody = PhysicsBody::createBox(pipeUp->getContentSize()*2);
		pipeDownBody->setDynamic(false);

		//addChild(pipeDown, 3);
		pipeDown->setPhysicsBody(pipeDownBody);
		pipeDown->getPhysicsBody()->setContactTestBitmask(1);
			
		
		pipes[i]->addChild(pipeUp);
		pipes[i]->addChild(pipeDown);

		addChild(pipes[i], 2);
	}

	pipeheight = pipes[0]->getPositionY();
	pipes[0]->setPositionX(visibleSize.width + 110);
	pipes[0]->setPositionY(pipeheight + random(-200, 200));
	pipes[1]->setPositionX(pipes[0]->getPositionX() + visibleSize.width/2 + 110);
	pipes[1]->setPositionY(pipeheight + random(-200, 200));

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameWorld::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool GameWorld::onContactBegin(const PhysicsContact& contact)
{
	if (GameState == 3)
	{
		return true;
	}

	if (m_iScore > 0)
		ScoreDate::getInstance()->addScore(m_iScore, std::string("Lanthree "));

	GameState = 3; //Die
	bird->stopAllActions();
	spGorund->stopAllActions();
	spGorund2->stopAllActions();

	//bird->getPhysicsBody()->removeFromWorld();

	//bird->setRotation(90);
	//auto downAction = MoveTo::create(0.5f, Vec2(visibleSize.width/2, 275));
	//bird->runAction(downAction);

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_hit.mp3");

	gameOver->setVisible(true);
	scorePanel->setVisible(true);
	reStart->setVisible(true);
	scoreBoard->setVisible(true);

	auto bigBang1 = CCParticleExplosion::create();
	bigBang1->setPosition(320, 700);
	auto bigBang2 = CCParticleExplosion::create();
	bigBang2->setPosition(100, 600);
	auto bigBang3 = CCParticleExplosion::create();
	bigBang3->setPosition(420, 500);
	auto bigBang4 = CCParticleExplosion::create();
	bigBang4->setColor(Color3B(0, 0, 0));
	bigBang4->setPosition(400, 650);

	addChild(bigBang1, 4); addChild(bigBang2, 4); addChild(bigBang3, 4); addChild(bigBang4, 4);


	auto listenerRestart = EventListenerTouchOneByOne::create();
	listenerRestart->onTouchBegan = [=](Touch* touch, Event* event){

		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point location = target->convertToNodeSpace(touch->getLocation());
		auto s = target->getContentSize();
		auto rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(location))
		{
			Director::getInstance()->replaceScene(GameWorld::createScene());
			return true;
		}

		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerRestart, reStart);

	auto listenerBoard = EventListenerTouchOneByOne::create();
	listenerBoard->onTouchBegan = [=](Touch* touch, Event* event){

		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point location = target->convertToNodeSpace(touch->getLocation());
		auto s = target->getContentSize();
		auto rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(location))
		{
			Director::getInstance()->replaceScene(BoardScene::createScene());
			return true;
		}

		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerBoard, scoreBoard);

	return true;
}

void GameWorld::update(float delta)
{

	if (GameState == 3)
	{
		return;
	}

	auto curVelocity = bird->getPhysicsBody()->getVelocity();
	bird->setRotation(-curVelocity.y*0.1 - 20);


	for(auto &pipe : pipes)
	{
		pipe->setPositionX(pipe->getPositionX() - speed);
		if (pipe->getPositionX() < visibleSize.width/2 &&
			pipe->getPositionX() + speed > visibleSize.width/2)
		{
			m_iScore++;

			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_point.mp3");

			for (int i = 0; i < 10; i++)
			{
				numbers[i]->setVisible(false);
				numbers2[i]->setVisible(false);
			}

			if(m_iScore < 10){
				numbers[m_iScore]->setVisible(true);
				numbers[m_iScore]->setPosition(visibleSize.width/2, 800.0f);
			}else{
				numbers[m_iScore/10]->setVisible(true);
				numbers2[m_iScore%10]->setVisible(true);
				numbers[m_iScore/10]->setPosition(visibleSize.width/2 - numbers[0]->getContentSize().width/2 - 10, 800.0f);
				numbers2[m_iScore%10]->setPosition(visibleSize.width/2 + numbers[0]->getContentSize().width/2 + 10, 800.0f);
			}
		}

		if (pipe->getPositionX() < -110)
		{
			pipe->setPositionX(visibleSize.width + 110);
			pipe->setPositionY(pipeheight + random(-200, 200));
		}
	}
}


void GameWorld::setPhyWorld(PhysicsWorld* m_world)
{
	m_world = m_world;
}