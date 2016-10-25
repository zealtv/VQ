#include "ofMain.h"
#include "ofApp.h"
#include "ofGLProgrammableRenderer.h"

//========================================================================
int main( ){

	//typedef void(*FunctionPointer)();


	ofSetLogLevel(OF_LOG_VERBOSE);
	//ofSetLogLevel(OF_LOG_ERROR);	
	ofSetLogLevel("ofThread", OF_LOG_WARNING);


  	ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
	ofSetupOpenGL(640, 480, OF_FULLSCREEN);			// <-------- setup the GL context

	ofHideCursor();

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp() );

}
