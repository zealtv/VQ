#pragma once
#include "PotentiometerController.h"
#include "wiringPi.h"
#include "Controllable.h"


class Pui
{
	public:
		void setup();
		void update();
		void close();
		void getParams(float params[]);
		void setLed( bool r, bool g, bool b );
		void setButtonFunction(int button, void (*function)());
		void setControllable( Controllable *c );
		void setMasterControllable( Controllable *c );		

	private:
		void updateButtons();

  		bool boolLedR;
		bool boolLedG;
		bool boolLedB;		

		bool buttonCurrentState[6];
		bool buttonLastState[6];
		float buttonTimePressed[6];
		float buttonTimeReleased[6];
		bool buttonCheckLongPress[6];

		PotentiometerController potController[8];
		bool isReady;

		Controllable *controllable;
		Controllable *masterControllable;

		//invert potentiometer values?
		static const bool doInvertPots = true;
};