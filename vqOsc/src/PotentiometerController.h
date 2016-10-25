#pragma once
#include "ofMain.h"
#include "Potentiometer.h"
#define NUMPOTS 8

class PotentiometerController: public ofThread{
public:
	void setup();
	void threadedFunction();
	void update();
	float potValues[NUMPOTS];
	bool hasNewValue;

private:
	Potentiometer pots[NUMPOTS];
};
