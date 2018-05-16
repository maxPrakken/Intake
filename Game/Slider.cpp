#include "Slider.h"

Slider::Slider()
{
	sliderBody = new Entity();
	sliderBody->texturePath = "assets/slider/slider_body.png";		
	sliderBody->size = Vector2(350, 50);
	sliderBody->pos = this->pos;

	selectButton = new Button();
	selectButton->texturePath = "assets/slider/slider_Button.png";
	selectButton->size = Vector2(50, 50);
	selectButton->pos = sliderBody->pos;

	this->addchild(sliderBody);
	this->addchild(selectButton);
}

Slider::~Slider()
{
	delete sliderBody;
	sliderBody = NULL;

	delete selectButton;
	selectButton = NULL;
}

void Slider::update(double deltatime)
{
	Entity::update(deltatime);

	moveSlider();
	calcPrecentageFilled();
	setAudio();
}

void Slider::moveSlider()
{
	if (selectButton->isHold()) {
		selectButton->pos = Vector2(Input::getInstance()->getMouseToScreen().x - selectButton->size.x / 2, selectButton->pos.y);

		if (selectButton->pos.x < sliderBody->pos.x) {
			selectButton->pos = sliderBody->pos;
		}
		else if (selectButton->pos.x > sliderBody->pos.x + sliderBody->size.x - selectButton->size.x) {
			selectButton->pos = Vector2(sliderBody->pos.x + sliderBody->size.x - selectButton->size.x, sliderBody->pos.y);
		}
	}
}

void Slider::calcPrecentageFilled()
{
	int relativePosX = selectButton->pos.x - sliderBody->pos.x + 50;
	precentageFilled = (relativePosX / sliderBody->size.x) * 100;
}

void Slider::setAudio()
{
	Audio::getInstance()->volumeAudio(128 * (precentageFilled / 100));
}
