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

	//refreshes highscores
	void refresh() {
		highscoreVector.clear();

		getHighScores();
		orderHighScores();
		manageScoresRect();
	}

private:
	//button that brings you back to the main menu
	Button * backbutton;

	//text colour
	SDL_Color c = { 255, 255, 255 }; //white

	//======================
	//default texts
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
	//======================

	//background
	Grid* background;

	//gets highscores
	void getHighScores();
	//orders highscores in order of big to small
	void orderHighScores();
	//makes sure highscores are displayed correctly
	void manageScoresRect();
	//puts the highscores on screen
	void displayHighScores();

	//vector highscorevector that holds all the highscores
	std::vector<int>highscoreVector;
	//vector rectvector, that holds all the rects for the text for the highscores.
	std::vector<SDL_Rect>rectVector;
};
