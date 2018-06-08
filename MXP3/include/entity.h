#pragma once

#include <iostream>
#include "vector2.h"
#include "animator.h"
#include <vector>
#include "audio.h"
#include "renderer.h"

class Renderer;

class __declspec(dllexport) Entity {
public:

	//default constructor en deconstructor
	Entity();
	virtual ~Entity();

	//update function that updates every frame
	virtual void update(double deltatime);

	//texture of the entity
	std::string texturePath;
	//spritesheet of the entity
	std::string spitesheetPath;

	//Animator of this entity
	Animator animator;

	//position and scale of the entity
	Vector2 pos;
	Vector2 size;
	double rot;

	//addchild function. add it to the window and parent
	void addchild(Entity* child);
	//removechild function, removes it from the window and parent
	void removechild(Entity* child);

	//gets children 
	Entity* getChildren();

	//calculates distance between entity's
	float distanceTo(Entity* other);

	//makes the child follow their parent around
	Vector2 getParentPosition();

	//checks if the entity is colliding with another entity
	bool isColliding(Entity* other);

	//checks if the entity is colliding with a vector2 point
	bool isColliding(Vector2 other);

	//checks if entity is outside of the canvas
	bool isOutOfCanvas();

	//gets parent of the entity
	Entity getParent() { return (*_parent); }

	//gets parent pointer of the entity
	Entity* getParentPointer() { return _parent; }

	//vector with chilren of entity
	std::vector<std::vector<Entity*>>ZLayers;

	//gets Zlayer
	int getZlayer() { return ZLayer; }
	//sets ZLayer amount int
	void setZLayer(int value) { 
		if (value >= 0) {
			ZLayer = value;
		}
		else {
			std::cout << "ZLayer can't be lower than 0";
		}
	}

	SDL_RendererFlip flip;
private:

	//parent entity
	Entity* _parent;

	//zlayer the entity will be placed at
	int ZLayer = 0;
	std::vector<Entity*>ZLayer_base;

	//current and next entity in list
	int _guid; 
	static int _nextGuid;
};