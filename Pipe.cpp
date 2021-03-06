#include "Pipe.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;

Pipe::Pipe()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Pipe::SpawnPipe(cocos2d::Layer *layer)
{
	CCLOG("SPAWN PIPE");
	auto topPipe = Sprite::create("toppipe.png");
	auto bottomPipe = Sprite::create("bottompipe.png");
	//topPipe->setScale(0.1);
	//bottomPipe->setScale(0.1);

	auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());
	auto bottomPipeBody = PhysicsBody::createBox(bottomPipe->getContentSize());
	auto random = CCRANDOM_0_1();
	/*if (random<LOWER_SCREEN_PIPE_THRESHOLD)
		random = LOWER_SCREEN_PIPE_THRESHOLD;
	else if (random>UPPER_SCREEN_PIPE_THRESHOLD)
		random = UPPER_SCREEN_PIPE_THRESHOLD;*/
	auto topPipePosition = visibleSize.height- topPipe->getContentSize().height/4+3*topPipe->getContentSize().height*random/4;
	//std::cout<<random * visibleSize.height<<std::endl;
	//std::cout<<topPipe->getContentSize().height/4<<std::endl;

	//std::cout<<topPipePosition<<std::endl;
	topPipeBody->setDynamic(false);
	bottomPipeBody->setDynamic(false);
	
	topPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	bottomPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	topPipeBody->setContactTestBitmask(true);
	bottomPipeBody->setContactTestBitmask(true);


	topPipe->setPhysicsBody(topPipeBody);
	bottomPipe->setPhysicsBody(bottomPipeBody);
	auto topPipePositionWidth = visibleSize.width +topPipe->getContentSize().width+origin.x;
	topPipe->setPosition(topPipePositionWidth, topPipePosition);
	bottomPipe->setPosition(Point(topPipe->getPositionX(), topPipePosition - 1.5*topPipe->getContentSize().height/*(Sprite::create("Ball.jpg")->getContentSize().height*PIPE_GAP)-topPipe->getContentSize().height*/));
	//bottomPipe->setPosition(Point(100,100));
	layer->addChild(topPipe);
	layer->addChild(bottomPipe);
	auto topPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED*visibleSize.width, Point(-visibleSize.width*1.5,0));
	auto bottomPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED*visibleSize.width, Point(-visibleSize.width*1.5,0));
	topPipe->runAction(topPipeAction);
	bottomPipe->runAction(bottomPipeAction);

	//auto bird = Sprite::create("ball2.png");
	//bird->setPosition( Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	//layer->addChild ( bird );
	//std::cout<<topPipePosition<<"  "<<topPipePositionWidth;



}
