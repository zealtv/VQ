#pragma once
#include "ofMain.h"
#include "wiringPiSPI.h"
#define NUMREADS 16

class Potentiometer{
public:
	Potentiometer();

	bool setup( int i );
	void update();
	int readAnalogDigitalConvertor();

	int potentiometerInput;

	int lastPotValue;
	int potValue;
	int changeAmount;
	bool didPotChange;

	static const int avgSize = NUMREADS -2;
	int lastPotValues[NUMREADS];
	int lastPotAverageValue;
	int currentAverageIndex;

	int lastFilteredPotValue;
	bool didFilteredPotChange;

	static const int filterSize = 1;

	bool doToleranceCheck;
	int tolerance;

	bool isReady;

};
