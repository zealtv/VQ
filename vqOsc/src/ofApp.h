#pragma once
#include "ofMain.h"
#include "PotentiometerController.h"
#include "wiringPi.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp
{

	public:
		void setup();
		void update();

		void updateParams();
		void setLed( bool r, bool g, bool b );
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	private:
		float params[8];
		float lastParams[8];
		void exit();

		void updateButtons();

		bool boolLedR;
		bool boolLedG;
		bool boolLedB;

		bool buttonCurrentState[6];
		bool buttonLastState[6];
		float buttonTimePressed[6];
		float buttonTimeReleased[6];
		bool buttonCheckLongPress[6];

		PotentiometerController potController;
		bool isReady;

		ofxOscSender oscSender;
};
