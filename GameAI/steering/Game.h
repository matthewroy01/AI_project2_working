#pragma once

#include "Trackable.h"
#include "PerformanceTracker.h"
#include "Defines.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <string>

class GraphicsSystem;
class GraphicsBuffer;
class GraphicsBufferManager;
class SpriteManager;
class KinematicUnit;
class GameMessageManager;
class Timer;
class Sprite;

// new stuff
class UnitManager;
class InputManager;
class UIManager;

const IDType BACKGROUND_SPRITE_ID = 0;
const IDType PLAYER_ICON_SPRITE_ID = 1;
const IDType AI_ICON_SPRITE_ID = 2;
const IDType WALL_SPRITE_ID = 3;

// initial values for modes
const float ALL_MAX_VELOCITY = 180.0f;
const float ALL_MAX_ANGULAR = 1.0f;
const float ALL_RADIUS = 100.0f;

// constants for collision
const int CHARACTER_SIDE = 32;
const int WALL_LONG = 1024;
const int WALL_SHORT = 100;

// pi for rotation
const float MY_PI = 3.14159265;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame

class Game:public Trackable
{
public:
	Game();
	~Game();

	bool init();//returns true if no errors, false otherwise
	void cleanup();

	//game loop
	void beginLoop();
	void processLoop();
	bool endLoop();

	inline GraphicsSystem* getGraphicsSystem() const { return mpGraphicsSystem; };
	inline GraphicsBufferManager* getGraphicsBufferManager() const { return mpGraphicsBufferManager; };
	inline SpriteManager* getSpriteManager() const { return mpSpriteManager; };
	inline GameMessageManager* getMessageManager() { return mpMessageManager; };
	inline InputManager* getInputManager() { return mpInputManager; };
	inline UIManager* getUIManager() { return mpUIManager; };
	inline Timer* getMasterTimer() const { return mpMasterTimer; };
	inline double getCurrentTime() const { return mpMasterTimer->getElapsedTime(); };

	// new stuff
	inline UnitManager* getUnitManager() const { return mpUnitManager; };
	static Game* getInstance();
	inline void setShouldExit(bool newVal) { mShouldExit = newVal; };
	void createArriveUnit();
	void createSeekUnit();
	void createWanderSOFUnit(bool shouldFlee);
	void deleteRandomUnit();

	// for setting up initial values for modes
	float getAllVelocity() { return ALL_MAX_VELOCITY; };
	float getAllAngular() { return ALL_MAX_ANGULAR; };
	float getAllRadius() { return ALL_RADIUS; };

private:
	GraphicsSystem* mpGraphicsSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	SpriteManager* mpSpriteManager;
	GameMessageManager* mpMessageManager;
	Timer* mpLoopTimer;
	Timer* mpMasterTimer;
	bool mShouldExit;
	Sprite* mpEnemyArrow;
	Sprite* mpWall;
	
	// new stuff
	UnitManager* mpUnitManager;
	InputManager* mpInputManager;
	UIManager* mpUIManager;

	// arbitrary distances
	const int SPAWN_DISTANCE_ARRIVE = 200,
			  SPAWN_DISTANCE_SEEK = 100,
			  SPAWN_DISTANCE_WANDERSEEK = 200,
			  SPAWN_DISTANCE_WANDERFLEE = 100;

	//should be somewhere else
	ALLEGRO_SAMPLE* mpSample;
	IDType mBackgroundBufferID;
	IDType mPlayerIconBufferID;
	IDType mEnemyIconBufferID;
	IDType mWallBufferID;
};

float genRandomBinomial();//range -1:1 from "Artificial Intelligence for Games", Millington and Funge
float genRandomFloat();//range 0:1 from "Artificial Intelligence for Games", Millington and Funge

extern Game* gpGame;
extern PerformanceTracker* gpPerformanceTracker;

