#ifndef __GAME_SCENE_BOX_H__
#define __GAME_SCENE_BOX_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "BirdBox.h"
#include "PipeBox.h"
#include "MyContactListener.h"
#include "GameOverScene.h"

class GameSceneBox : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	GameSceneBox();
	
    virtual bool init();

	void initPhysics();
	 float deltaTime;
    void update(float dt);
    // implement the "static create()" method manually
    CREATE_FUNC(GameSceneBox);
		b2World* world;

private:
	void SpawnPipe(float dt);
	Bird2 *bird;
	Pipe2 pipe;
	MyContactListener *contactListener;
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	bool onContactBegin();
	//cocos2d::CCSprite *ball
};

#endif // __GAME_SCENE_BOX_H__
