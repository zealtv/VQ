#include "ofMain.h"
#include "ofApp.h"
#include "ofAppNoWindow.h"

//========================================================================
int main( ){
	ofSetLogLevel(OF_LOG_ERROR);
	ofSetLogLevel("ofThread", OF_LOG_WARNING);

	ofAppNoWindow w;
	ofSetupOpenGL(&w,1024,768, OF_WINDOW);
	ofRunApp( new ofApp() );
}
