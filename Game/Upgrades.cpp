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
}

void RPM_Upgrade::use(void* pointer) {
	Player* p = (Player*)pointer;
	//do something with player here
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
}

void DoubleShot_Upgrade::use(void* pointer) {
	Player* p = (Player*)pointer;
	//do something with player here
}
