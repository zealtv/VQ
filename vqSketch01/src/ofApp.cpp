#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){

    //set up VQ listener
    vq.setup(5050);

    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetBackgroundAuto(false);
    fbo.allocate(ofGetWidth(), ofGetHeight());

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
  fbo.begin();

  ofSetColor(20, 10);
  ofDrawRectangle(0.0, 0.0, ofGetWidth(), ofGetHeight());

  for(int i = 0; i < numPoints; i++){
    ofPushMatrix();
    int h = 5;
    // int h = (int)((ofGetElapsedTimeMillis() * 0.005) + i * 10 )% 255;
    int b = ofMap(points[i].z, -10000.0, -8000.0, 0, 255, false); //fade in from background
    ofColor c = ofColor::fromHsb(h, 0, b);
    ofSetColor(c);
    ofDrawLine(points[i], ofPoint(points[i].x, points[i].y, points[i].z - (4000 * vq.getParameters().pots[0])));

    h = 80;
    h = (int)((ofGetElapsedTimeMillis() * 0.005) + i * 10 + (255/2))% 255;
    b = ofMap(points[i].z, -10000.0, -8000.0, 0, 100, false); //fade in from background
    c = ofColor::fromHsb(h, 255, b);
    c.a = 100;
    ofSetColor(c);

    ofDrawIcoSphere(points[i], ofRandom(16,20));
    ofPopMatrix();
  }
  fbo.end();
  
  ofSetColor(255);
  fbo.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::exit(){}
