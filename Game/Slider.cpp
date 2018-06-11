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

Slider::Slider(Vector2 position, int channel) {
	this->pos = Vector2(0, 0);

	this->channel = channel;

	sliderBody = new Entity();
	sliderBody->texturePath = "assets/slider/slider_body.png";
	sliderBody->size = Vector2(350, 50);
	sliderBody->pos = position;

	selectButton = new Button();
	selectButton->texturePath = "assets/slider/slider_Button.png";
	selectButton->size = Vector2(50, 50);
	selectButton->pos = position + Vector2(sliderBody->size.x / 2 - selectButton->size.x / 2, 0);

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
	if(!audioMuted)
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
	int relativePosX = selectButton->pos.x - sliderBody->pos.x;
	precentageFilled = (relativePosX / (sliderBody->size.x - selectButton->size.x)) * 100;
}

void Slider::setAudio()
{
	Audio::getInstance()->volumeAudio(channel, 128 * (precentageFilled / 100));
}
