#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetBackgroundAuto(false);

    //set up VQ listener
    vq.setup(5050);

    numPoints = 200;
    points.resize(numPoints);
    for(int i = 0; i < numPoints; i++){
      points[i].set( ofPoint( ofRandom(-ofGetWidth() * 2, ofGetWidth() * 3), ofRandom(-ofGetHeight() * 2, ofGetHeight() * 3), ofRandom(0.0, -10000.0 ) ) );
      //check for dots near center of camera
    }

    ofEnableAlphaBlending();
    ofClear(0);
    ofSetIcoSphereResolution(0);
    ofSetLineWidth(4);
}

//--------------------------------------------------------------
void ofApp::update(){
    //update up VQ listener
    vq.update();

    for(int i = 0; i < numPoints; i++){
      points[i].z += 10.0;
      if(points[i].z > 1000.0){
        points[i].x = ofRandom(-ofGetWidth() * 2, ofGetWidth() * 3);
        points[i].y = ofRandom(-ofGetHeight() * 2, ofGetHeight() * 3);
        points[i].z = -10000.0;
      }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
  // prevent build up of grey
  // glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);
  glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);

  ofSetColor(20, 10);
  ofDrawRectangle(0.0, 0.0, ofGetWidth(), ofGetHeight());

  // restores normal draw mode
  // glDisable(GL_BLEND);
  glBlendEquation(GL_FUNC_ADD_EXT);
  glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);


  for(int i = 0; i < numPoints; i++){
    ofPushMatrix();
    int h = 5;
    // int h = (int)((ofGetElapsedTimeMillis() * 0.005) + i * 10 )% 255;
    int b = ofMap(points[i].z, -10000.0, -8000.0, 0, 255, false); //fade in from background
    ofColor c = ofColor::fromHsb(h, 130, b);
    ofSetColor(c);
    ofDrawLine(points[i], ofPoint(points[i].x, points[i].y, points[i].z - (4000 * vq.getParameters().pots[0])));

    h = 80;
    h = (int)((ofGetElapsedTimeMillis() * 0.005) + i * 10 + (255/2))% 255;
    b = ofMap(points[i].z, -10000.0, -8000.0, 0, 100, false); //fade in from background
    c = ofColor::fromHsb(h, 255, b);
    ofSetColor(c);

    // ofRotateX(ofGetElapsedTimeMillis() * 0.02);
    // ofRotateZ(ofGetElapsedTimeMillis() * 0.1);
    ofDrawIcoSphere(points[i], ofRandom(16,20));
    ofPopMatrix();
  }

}

//--------------------------------------------------------------
void ofApp::exit(){}
