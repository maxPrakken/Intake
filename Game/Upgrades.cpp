#include "Upgrades.h"

//base upgrade class
Upgrade_Base::Upgrade_Base() {
	size = Vector2(50, 50);
	texturePath = "assets/INA.png";
}

/*
======================================================
======================================================
*/

//rpm upgrade functions
RPM_Upgrade::RPM_Upgrade() {
	texturePath = "assets/upgrade_RPM.png";
	timerStart = false;
}

void RPM_Upgrade::update(double deltatime)
{
	if (timerStart) {
		timer += deltatime;
		
		if (timer > timeToWork) {
			player->setRPM(player->getDefaultRPM());
			timerStart = false;
		}
	}
}

void RPM_Upgrade::use(void* pointer) {
	timerStart = true;
	Player* p = (Player*)pointer;
	player = p;
	p->setRPM(p->getDefaultRPM() * 2);
}

/*
======================================================
======================================================
*/

//health upgrade functions
Health_Upgrade::Health_Upgrade() {
	texturePath = "assets/upgrade_Health.png";
	healthToHeal = 2;
}

void Health_Upgrade::use(void* pointer) {
	Player* p = (Player*)pointer;
	p->health++;
}

/*
======================================================
======================================================
*/

//double shot upgrade functions
DoubleShot_Upgrade::DoubleShot_Upgrade() {
	texturePath = "assets/upgrade_DoubleShot.png";
	timerStart = false;
}

void DoubleShot_Upgrade::update(double deltatime)
{
	if (timerStart) {
		timer += deltatime;

		if (timer > timeToWork) {
			player->doubleShot = false;
			timerStart = false;
		}
	}
}

void DoubleShot_Upgrade::use(void* pointer) {
	timerStart = true;
	Player* p = (Player*)pointer;
	player = p;
	p->doubleShot = true;
}
