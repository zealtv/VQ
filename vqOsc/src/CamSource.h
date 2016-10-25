#pragma once
#include "ofMain.h"
#include "Controllable.h"

//CamSource class
class CamSource : public Controllable{
	
	public:
		void setup();
		void update();
		void close();
		ofTexture texture;

		void buttonPress(int i);
		void buttonRelease(int i);
		void buttonLongPress(int i);		

	private:
		ofVideoGrabber grabber;
		int camWidth;
		int camHeight;	
		int numDevices;	
		int currentDevice;
		void loadSource( int i );		
		void changeSource( int i );

};