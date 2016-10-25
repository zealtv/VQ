#pragma once
#include "ofMain.h"
#include "CamSource.h"
#include "VideoSource.h"
#include "Effect.h"
#include "Pui.h"
#include "Controllable.h"

class ofApp : public ofBaseApp, Controllable
{
	
	public:

		void setup();
		void update();
		void draw();
		void renderFrame();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		
		

		ofFbo fboThisFrame;
		ofFbo fboLastFrame;
    	ofTrueTypeFont myFont;

    	bool debug;

    	float wWidth;
    	float wHeight;
  		float effectParams[8];
		float sourceParams[8];  
		
		bool mode;		

  		bool guiMode;

	private:

		void updateButtons();
		void toggleBypass();
		void setMode( int m );	
		void exit();

		void buttonPress(int i);
		void buttonRelease(int i);
		void buttonLongPress(int i);

		CamSource camSource;
		VideoSource videoSource;
		Effect effect;
		Pui pui;

};
