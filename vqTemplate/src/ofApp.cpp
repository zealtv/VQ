#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    //set up VQ listener
    vq.setup(5050);
}

//--------------------------------------------------------------
void ofApp::update(){
    //update up VQ listener
    vq.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    ofSetColor(0);

    //draw pots as sliders
    string pString = "pots ";
    for(int i = 0; i < 8; i++){
      int yPos = 50;
      if(i >= 4)
        yPos = 300;
      drawValue(50 + (i % 4) * 100, yPos, 50, 200, vq.getParameters().pots[i]);
      pString += ofToString(vq.getParameters().pots[i]) + " ";
    }

    //draw buttons as boxes
    string bString = "buttons ";
    for(int i = 0; i < 5; i++){
      drawValue(50 + i * 100, 600, 50, 50, vq.getParameters().buttons[i]);
      bString += ofToString(vq.getParameters().buttons[i]) + " ";
    }

    //print values as string
    ofDrawBitmapString(pString + "\n" + bString, 10, ofGetHeight()-30);
}

//--------------------------------------------------------------
void ofApp::exit(){}


//--------------------------------------------------------------
void ofApp::drawValue(int x, int y, float w, float h, float value){
  ofPushStyle();

  ofFill();
	ofSetColor(190, 90, 190);
	ofDrawRectangle(x, (1.0 - value) * h + y, w, value * h);

	ofNoFill();
	ofSetColor(60);
	ofDrawRectangle(x, y, w, h);

  ofPopStyle();
}
