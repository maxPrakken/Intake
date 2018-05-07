#pragma once

#include "../MXP3/include/scene.h"

#include <sceneManager.h>

#include "grid.h"
#include "Player.h"
#include "bullet.h"
#include "Button.h"

#include <typeinfo>
#include <iostream>

class MenuScene : public Scene {
public:
	//constructor
	MenuScene();

	//deconstructor
	virtual ~MenuScene();

	//update function
	virtual void update(double deltatime);

	void buttonClickCheck();

	void playerShoot();

private:
	Button* playButton;
	Button* optionsButton;
	Button* highscoresButton;
	Button* quitButton;

	Player* player;

	std::vector<Bullet*>bulletVector;
	std::vector<Button*>buttonVector;
};
