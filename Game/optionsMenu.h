#pragma once

#include "../MXP3/include/scene.h"

#include <sceneManager.h>

#include "grid.h"
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

	//checks if buttons are being pressed
	void buttonClickCheck();
	//gets the private audio slider
	Slider* getAudioSlider() { return generalAudioSlider; }

private:
	//displays text
	void displayText();
	//makes sure texts stays in right place
	void calcTextPosition();

	//HUD buttons
	Button* backButton;
	Button* muteButton;
	Slider* generalAudioSlider;
	Slider* playerAudioSlider;
	Slider* enemyAudioSlider;
	//=================

	//default text colour
	SDL_Color c = { 255, 255, 255 };
	//text rects
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
	//==================
	//default texts for sliders
	std::string generalText = "General audio slider";
	std::string playerText = "Player audio slider";
	std::string enemyText = "Enemy audio slider";
	//==================

	//background 
	Grid* background;

	//checks if mute button has been clicked
	bool muteClicked = false;

	//holds all the buttons in a vector.
	std::vector<Button*>buttonVector;
};