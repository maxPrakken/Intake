#include "Button.h"

Button::Button()
{
	texturePath = "assets/INA.png";
	size = Vector2(200, 100);
}

Button::Button(buttonType type)
{
	this->type = type;
}

Button::~Button()
{
}

void Button::update(double deltatime)
{
	Entity::update(deltatime);

	isClicked();
}

bool Button::isClicked()
{
	if (Input::getInstance()->getMouseButtonDown(1) && this->isColliding(Input::getInstance()->getMouseToScreen()))
	{
		return true;
	}
	return false;
}
