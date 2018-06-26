#pragma once

#include "../MXP3/include/agent.h"

class IEnemy : public Agent {

public:
	//enums for default enemies
	enum enemyTypes {
		BASIC,
		FAST,
		BOSS
	};

	//default constructor
	IEnemy() {}
	//deconstructor
	virtual ~IEnemy() {}
	//update function that takes deltatime double variable
	virtual void update(double deltatime);

	//gets movespeed
	float getSpeed() { return speed; }
	//sets movespeed
	void setSpeed(float speed) { this->speed = speed; }

	//gets the isdead variable
	bool getIsDead() { return isDead; }

	//function that lets the enemy shoot
	virtual void shoot() { }

	//function that, when called. lets the enemy run into cirkels
	void setGoCircles(bool yesno, int radiusSize, float speed);

	//vector2 direction
	Vector2 direction;

	//boolean canshoot
	bool canShoot;
	float shootTimer = 0;
	//start int, after first loop it gets randomized
	int randomMaxTimer = 1;

	//type according to enum
	int type;
	//amount of points the creature is worth
	int pointsWorth;

	//startposion in Vector2
	Vector2 startPosition;

	//vector with all the points he walks to
	std::vector<Vector2> pointVector;

private:
	//enemy walks towards position
	void goTo(double deltatime);
	//checks if the enemy vershoots the target
	void checkPoint();

	//lets enemy run in cirkels
	void goCircle(Vector2 startpoint, int radiusSize, float speed);

	//private startposition
	Vector2 startPos;
	//float circleangle
	float circleAngle = 0;
	//boolean gocirkels
	bool goCircles = false;
	//int radius of the cirkel
	int radiusSize = 0;
	//speed in which such enemy roams
	float circleSpeed = 0;

	//default speed
	float speed = 70;

	int index = 0;
	int vectorIndex = 0;
	Vector2 point;
	
	//isdead boolean that will turn false if enemy dies.
	bool isDead = false;

	//enemy bullet vector
	std::vector<Entity*>bullets;
};