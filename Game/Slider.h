#pragma once

#include "Button.h"

#include <entity.h>
#include <sceneManager.h>
#include <renderer.h>

class Slider : public Entity {
public:
	Slider();
	//use the position overloaded function if you want to put the slider
	//on a different position than (0, 0)
	Slider(Vector2 position);
	virtual ~Slider();
	virtual void update(double deltatime);

	float getProcentage() { return precentageFilled; }

private:
	void moveSlider();
	void calcPrecentageFilled();
	void setAudio();

	Button * selectButton;
	Entity* sliderBody;

	Vector2 range;

	float precentageFilled;
};
