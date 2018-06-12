#pragma once

#include <math.h>
#include "vector2.h"
#include <iostream>

//singleton math class
class __declspec(dllexport) MathM {
public:
	//deconstructor
	virtual ~MathM();
	//get instance of the mathM class
	static MathM* getInstance();
	
	//gets the amount of digits in a int 
	//doesnt work on minus ints
	int getDigits(int i);
private:
	//default constructor
	MathM();
	//instance of the singelton
	static MathM* instance;
};
