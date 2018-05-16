#pragma once

#include "Button.h"

#include <entity.h>
#include <sceneManager.h>
#include <renderer.h>

class Slider : public Entity {
public:
	Slider();
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
