#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"

#define HOST "localhost"
#define PORT 5050

//--------------------------------------------------------
class ofApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxOscSender sender;

		ofParameter<float> pots[8];
		ofParameter<bool> buttons[5];
		float potValues[8];
		int buttonValues[5];
		// ofxFloatSlider pots[8];
		// ofxColorSlider color;
		// ofxVec2Slider center;
		// ofxIntSlider circleResolution;
		// ofxToggle filled;
		// ofxButton buttons[5];
		// ofxButton ringButton;

		ofParameterGroup parameters;
		ofxPanel gui;
};

