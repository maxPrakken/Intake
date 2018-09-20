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

class StoreScene : public Scene {
public:
	//default constructor
	StoreScene();
	//zlayer constructor
	StoreScene(int ZLayer_amount);
	//default deconstructor
	virtual ~StoreScene();
	//update function
	virtual void update(double deltatime);
private:
	//background grid
	Grid* background;
	//button that brings you back to the main menu
	Button * backbutton;

	SDL_Rect Score_rect{
		Score_rect.x = 450,
		Score_rect.y = 0,
		Score_rect.w = 100,
		Score_rect.h = 100
	};

	//default text color
	SDL_Color c = {255,255,255};

	int getSBAmount();
	void displayText();
	void saveSB();

	int totalSpaceBucks = 0;
};
