#pragma once

#include "ofMain.h"
#include "wiringPiSPI.h"


class PotentiometerController: public ofThread
{
public:
	PotentiometerController();
	//PotentiometerController( int input );
	bool setup( int i );
	void threadedFunction();
	

	
	int readAnalogDigitalConvertor();
	int potentiometerInput;
	
	
	int lastPotValue;
	int potValue;
	int changeAmount;
	bool didPotChange;
	
	static const int avgSize = 16;
	int lastPotValues[16];
	int lastPotAverageValue;
	int currentAverageIndex;

	int lastFilteredPotValue;

	bool didFilteredPotChange;	

	static const int filterSize = 1;


	bool doToleranceCheck;
	int tolerance;
	
	bool isReady;
	
};