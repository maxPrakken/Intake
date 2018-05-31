#pragma once

#include "entity.h"
#include "renderer.h"
#include "input.h"

#include "audio.h"

class __declspec(dllexport) Scene : public Entity {
public:
	//default constuctor
	Scene();

	//deconstructor
	virtual ~Scene();

	//update function. updates every frame
	void update(double deltatime);
	
	//places entity in the absolute middle of the window
	Vector2 placeCenter(Entity* entity);

	//a string that represents the scene that was on screen before this one
	std::string lastScene = "";

private:
	//update the children of the scene
	void updateChildren(float deltatime);
};
