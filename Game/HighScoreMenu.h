#pragma once

#include "../MXP3/include/scene.h"

#include <sceneManager.h>
#include <fstream>
#include <algorithm>
#include <mathM.h>

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

	void refresh() {
		highscoreVector.clear();

		getHighScores();
		orderHighScores();
		manageScoresRect();
	}

private:
	Button * backbutton;

	SDL_Color c = { 255, 255, 255 }; //white

	SDL_Rect score1{
		score1.x = 0,
		score1.y = 0,
		score1.w = 0,
		score1.h = 100
	};
	SDL_Rect score2{
		score1.x = 0,
		score1.y = 0,
		score1.w = 0,
		score1.h = 100
	};
	SDL_Rect score3{
		score1.x = 0,
		score1.y = 0,
		score1.w = 0,
		score1.h = 100
	};
	SDL_Rect score4{
		score1.x = 0,
		score1.y = 0,
		score1.w = 0,
		score1.h = 100
	};
	SDL_Rect score5{
		score1.x = 0,
		score1.y = 0,
		score1.w = 0,
		score1.h = 100
	};

	Grid* background;

	void getHighScores();
	void orderHighScores();
	void manageScoresRect();
	void displayHighScores();

	std::vector<int>highscoreVector;
	std::vector<SDL_Rect>rectVector;
};
