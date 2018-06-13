#pragma once

#include "../MXP3/include/scene.h"

#include <sceneManager.h>

#include "grid.h"
#include "Button.h"

#include <typeinfo>
#include <iostream>

class HighScoreMenu : public Scene {
public:
	//default constructor
	HighScoreMenu();
	//deconstructor
	virtual ~HighScoreMenu();
	//update function
	virtual void update(double deltatime);

private:
	Button * backbutton;

	SDL_Rect score1{
		score1.x = 450,
		score1.y = 0,
		score1.w = 20,
		score1.h = 100
	};
	SDL_Rect score2{
		score1.x = 450,
		score1.y = 0,
		score1.w = 100,
		score1.h = 100
	};
	SDL_Rect score3{
		score1.x = 450,
		score1.y = 0,
		score1.w = 100,
		score1.h = 100
	};
	SDL_Rect score4{
		score1.x = 450,
		score1.y = 0,
		score1.w = 100,
		score1.h = 100
	};
	SDL_Rect score5{
		score1.x = 450,
		score1.y = 0,
		score1.w = 100,
		score1.h = 100
	};
};
