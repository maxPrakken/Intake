#pragma once

#include "../MXP3/include/scene.h"

#include <sceneManager.h>

#include "grid.h"
#include "Player.h"
#include "bullet.h"
#include "Button.h"
#include "MyScene.h"
#include "HighScoreMenu.h"

#include <typeinfo>
#include <iostream>

class MenuScene : public Scene {
public:
	//constructor
	MenuScene();

	//zlayer overloader
	MenuScene(int ZLayer_amount);

	//deconstructor
	virtual ~MenuScene();

	//update function
	virtual void update(double deltatime);

	//checks if button is being checked
	void buttonClickCheck();

	//player fires a bullet
	void playerShoot();

private:
	//adds zlayers to scene
	void addZLayers(int zlayerAmount);

	//HUD buttons
	Button* playButton;
	Button* optionsButton;
	Button* highscoresButton;
	Button* quitButton;
	//===============

	//background
	Grid* background;
	//player instance
	Player* player;

	//bullet vector
	std::vector<Bullet*>bulletVector;
	//button vector
	std::vector<Button*>buttonVector;
};
