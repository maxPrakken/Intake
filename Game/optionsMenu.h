#pragma once

#include "../MXP3/include/scene.h"

#include <sceneManager.h>

#include "grid.h"
#include "Player.h"
#include "bullet.h"
#include "Button.h"
#include "Slider.h"

#include <typeinfo>
#include <iostream>

class optionsMenu : public Scene {
public:
	//constructor
	optionsMenu();
	
	//deconstructor
	virtual ~optionsMenu();

	//update function
	virtual void update(double deltatime);

	void buttonClickCheck();
	Slider* getAudioSlider() { return generalAudioSlider; }

private:
	void displayText();
	void calcTextPosition();

	Button* backButton;
	Button* muteButton;
	Slider* generalAudioSlider;
	Slider* playerAudioSlider;
	Slider* enemyAudioSlider;

	SDL_Color c = { 255, 255, 255 };
	SDL_Rect generalRect{
		generalRect.x = 0,
		generalRect.y = 0,
		generalRect.w = 0,
		generalRect.h = 50
	};
	SDL_Rect playerRect{
		playerRect.x = 0,
		playerRect.y = 0,
		playerRect.w = 0,
		playerRect.h = 50
	};
	SDL_Rect enemyRect{
		enemyRect.x = 0,
		enemyRect.y = 0,
		enemyRect.w = 0,
		enemyRect.h = 50
	};
	std::string generalText = "General audio slider";
	std::string playerText = "Player audio slider";
	std::string enemyText = "Enemy audio slider";

	Grid* background;

	bool muteClicked = false;

	std::vector<Button*>buttonVector;
};