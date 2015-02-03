#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#define DIS_PIPE 900

USING_NS_CC;


class GameWorld : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GameWorld);
	static Scene* createScene();
	virtual void update(float delta);

	void setPhyWorld(PhysicsWorld* m_world);

private:
	void loadingCallBack(Texture2D *texture);
	void initWithAtlas();
	void beforeStart();
	void startGame();
	void initNumber();
	bool onContactBegin(const PhysicsContact& contact);
	//bool onTouchBegan(Touch *touch, Event *event);

	PhysicsWorld* m_world;
	Sprite* bird, *spGorund, *spGorund2, *getReady, *spTutorial, *scorePanel, *gameOver, *reStart, *scoreBoard;
	Node* pipes[2], *numbers[10], *numbers2[10];
	float speed, pipeheight;
	Size pipeSize, visibleSize;
	//1 bef   2 gaming    3 die
	int GameState; 
	int m_iScore;
};


#endif