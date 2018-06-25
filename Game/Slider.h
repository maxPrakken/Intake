#pragma once

#include "Button.h"

#include <entity.h>
#include <sceneManager.h>
#include <renderer.h>
#include <mathM.h>

class Slider : public Entity {
public:
	Slider();
	//use the position overloaded function if you want to put the slider
	//on a different position than (0, 0)
	Slider(Vector2 position, int channel);
	//use the position overloaded function if you want to put the slider
	//on a different position than (0, 0)
	//also gives the pointer to the gereral volume slider 
	Slider(Vector2 position, int channel, Slider* general);
	virtual ~Slider();
	virtual void update(double deltatime);

	float getProcentage() { return precentageFilled; }

	bool audioMuted = false;

	Vector2 getSliderBodyPosition() { return sliderBody->pos; }

private:
	void moveSlider();
	void calcPrecentageFilled();
	void setAudio();
	void showPrecentageFilled();

	Button * selectButton;
	Entity* sliderBody;

	SDL_Color c = { 255, 255, 255 };
	SDL_Rect rect{
		rect.x = 0,
		rect.y = 0,
		rect.w = 50,
		rect.h = 50
	};

	Slider* generalSlider = NULL;

	Vector2 range;

	int channel = -1;
	float precentageFilled;
};
