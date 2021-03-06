#include "GameSceneBox.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
#define SCALE_RATIO 32

GameSceneBox::GameSceneBox()
{
//this->initPhysics();
//scheduleUpdate();
}

Scene* GameSceneBox::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameSceneBox::create();

    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameSceneBox::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("background.png"); //this 1920x1080
    backgroundSprite->setPosition( Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild ( backgroundSprite );
	
	initPhysics();

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameSceneBox::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	this->scheduleUpdate();

    return true;
}

void GameSceneBox::initPhysics() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	b2Vec2 gravity;
	gravity.Set(0.0f, -8.0f);
	world = new b2World(gravity);
// Do we want to let bodies sleep?
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);
	//b2ContactListener *contactListener;
	contactListener = new MyContactListener();
  	world->SetContactListener(contactListener);

//инициализация Земли

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0,0);
 
	b2Body *groundBody = world->CreateBody(&groundBodyDef);
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;
 
	//wall definitions
	groundEdge.Set(b2Vec2(0,0), b2Vec2(visibleSize.width/SCALE_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

//Конец инициализации земли

	bird = new Bird2(this, this->world);

	this->schedule( schedule_selector( GameSceneBox::SpawnPipe), PIPE_SPAWN_FREQUENCY*visibleSize.width);

	//пусть физические тела колонн не быдут касаться земли, тогда все будет работать корректно

	//pipebox и birdbox в отдельные конструкторы (позволит убрать лишние заголовки)
}

void GameSceneBox::update(float dt)
{
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
    	if (b->GetUserData() != NULL) {
        	// Synchronize the AtlasSprites position and rotation with the corresponding body
        	Sprite* sprActor = (Sprite*) b->GetUserData();
        	sprActor->setPosition(b->GetPosition().x * SCALE_RATIO, b->GetPosition().y * SCALE_RATIO);
        	sprActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
    	}
	} 
	world->Step(dt, 8, 1);
	 

if (contactListener->isContact){

	//здесь getTag и переход по нему, доступ к спарйту через тело
	Director::getInstance()->pause();
	auto scene = GameOverScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

	/*std::vector<b2Contact>::iterator pos;
for(pos = contactListener->_contacts.begin(); pos != contactListener->contacts.end(); ++pos) {
    b2Contact contact = *pos;
 
    if ((contact.fixtureA == _bottomFixture && contact.fixtureB == _ballFixture) ||
        (contact.fixtureA == _ballFixture && contact.fixtureB == _bottomFixture)) {
        NSLog(@"Ball hit bottom!");
    }
}*/


}

bool GameSceneBox::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
	bird->Fly();
	return true;
}

void GameSceneBox::SpawnPipe(float dt){
	pipe.SpawnPipe(this, this->world);
}

bool GameSceneBox::onContactBegin(){
	//for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
return true;
}


