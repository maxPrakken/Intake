#include "Button.h"

Button::Button()
{
	texturePath = "assets/INA.png";
	size = Vector2(200, 100);
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
		std::cout << "hello world" << std::endl;
		return true;
	}
	return false;
}
