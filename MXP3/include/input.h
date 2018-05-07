#pragma once

#include <SDL2\SDL.h>
#include "vector2.h"
#include <iostream>

//singleton input
class __declspec(dllexport) Input {
public:
	//deconstructor
	virtual ~Input();
	//get instance of input
	static Input *getInstance();
	//update function
	void update();
	//looks if key is pressed
	bool getKey(int keyCode);
	//looks if key goes up
	bool getKeyUp(int keyCode);
	//looks if key goes down
	bool getKeyDown(int keyCode);

	//looks if mouseButton is pressed
	bool getMouseButton(int number);
	//looks if mouseButton goes down
	bool getMouseButtonDown(int number);
	//looks if mouseButton goes up
	bool getMouseButtonUp(int number);

	//checks if the application is set to quit
	bool getMustQuit() { return mustquit; };

	//lets you quit the application if set to true
	void setMustQuit(bool truefalse) { mustquit = truefalse; }

	//mouseposition relative to the window
	Vector2 getMouseToScreen();
	
	//int window width and height
	int window_width, window_height;

private:
	//default constructor
	Input();
	//instance of singleton
	static Input *instance;

	//all possible keyboard and mouse combinations
	bool keys[282];
	bool keysUp[282];
	bool keysDown[282];

	bool keysalreadyUp[282];
	bool keysalreadyDown[282];

	bool mouseButton[20];
	bool mouseButtonUp[20];
	bool mouseButtonDown[20];

	bool mouseButtonAlreadyUp[20];
	bool mouseButtonAlreadyDown[20];

	//bool to check if the program must quit
	bool mustquit = false;

	//vector2 that keeps track of the mouse position
	Vector2 mousePos;
};