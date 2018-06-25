#pragma once

#include "../MXP3/include/entity.h"
#include "Player.h"

class Upgrade_Base : public Entity
{
public:
	//default constructor
	Upgrade_Base();

	//default deconstructor
	virtual ~Upgrade_Base() { return; };

	//update function
	virtual void update(double deltatime){ Entity::update(deltatime); }

	virtual void use(void* pointer) { return; }

	bool used = false;
};

class Health_Upgrade : public Upgrade_Base {
public:

	//default constructor
	Health_Upgrade();

	//default deconstructor
	virtual ~Health_Upgrade() { return; };

	//update function
	virtual void update(double deltatime) { return; };

	virtual void use(void* pointer);

private:
	int healthToHeal;
};

class RPM_Upgrade : public Upgrade_Base {
public:
	//default constructor
	RPM_Upgrade();

	//default deconstructor
	virtual ~RPM_Upgrade() { return; };

	//update function
	virtual void update(double deltatime);

	virtual void use(void* pointer);

private:
	bool timerStart;
	double timer = 0;
	double timeToWork = 5;

	Player* player;
};

class DoubleShot_Upgrade : public Upgrade_Base {
public:
	//default constructor
	DoubleShot_Upgrade();

	//default deconstructor
	virtual ~DoubleShot_Upgrade() { return; };

	//update function
	virtual void update(double deltatime);

	//use function
	virtual void use(void* pointer);

private:
	//timer variables
	bool timerStart;
	double timer = 0;
	double timeToWork = 5;
	//==============

	//player instance
	Player* player;
};
