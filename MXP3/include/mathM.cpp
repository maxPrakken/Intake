#include "mathM.h"

MathM *MathM::instance = NULL;
MathM::MathM()
{

}

MathM::~MathM() {
	if (instance != NULL) {
		delete instance;
	}
}

MathM *MathM::getInstance() {
	if (MathM::instance == NULL) {
		MathM::instance = new MathM();
	}
	return MathM::instance;
}

int MathM::getDigits(int i)
{
	int digits = 0;
	if (i < 0) digits = 1; // remove this line if '-' counts as a digit
	while (i) {
		i /= 10;
		digits++;
	}
	return digits;
}
