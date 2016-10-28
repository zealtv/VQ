#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){


    //set up VQ listener
    vq.setup(5050);

    fbo.allocate(ofGetWidth(), ofGetHeight());
    fbo.begin();
    ofClear(0);
    fbo.end();

    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    // ofSetBackgroundAuto(false);

    numPoints = 200;
    points.resize(numPoints);
    for(int i = 0; i < numPoints; i++){
      points[i] = ofPoint( ofRandom(-ofGetWidth() * 2, ofGetWidth() * 3), ofRandom(-ofGetHeight() * 2, ofGetHeight() * 3), ofRandom(0.0, -10000.0 ) );
      //check for dots near center of camera
    }

    //TODO sort points by Z

    ofEnableAlphaBlending();

    icoSphere.setResolution(0);
    // ofSetLineWidth(4);
}

//--------------------------------------------------------------
void ofApp::update(){
    //update up VQ listener
    vq.update();

    //roll camera at n speed
    camera.roll( pow(vq.getParameters().pots[2], 3) * 180.0 );

    for(int i = 0; i < numPoints; i++){
      points[i].z += 10.0 + vq.getParameters().pots[0] * 100.0;
      if(points[i].z > 1000.0){
        points[i].x = ofRandom(-ofGetWidth() * 2, ofGetWidth() * 3);
        points[i].y = ofRandom(-ofGetHeight() * 2, ofGetHeight() * 3);
        points[i].z = -10000.0;
      }
    }

    if(vq.getParameters().buttons[1] == 1){
      camera.enableOrtho();
      cout << "es\n";
    }
    else
      camera.disableOrtho();
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofClear(0);

  ofSetLineWidth(vq.getParameters().pots[4] * 4 + 1);

  fbo.begin();

  int o = ofMap(vq.getParameters().pots[3], 0.0, 1.0, 50, 0);
  ofSetColor(0, o);
  ofDrawRectangle(0.0, 0.0, ofGetWidth(), ofGetHeight());

  camera.begin();
  

  for(int i = 0; i < numPoints; i++){

    ofPushMatrix();

    //create colour
    ofColor c1;    
    int h;    
    h = (int)((ofGetElapsedTimeMillis() * 0.005) + i * 10)% 255; // cycle colours
    c1 = ofColor::fromHsb(h, vq.getParameters().pots[1] * 255, 255);
    c1.a = ofMap(points[i].z, -10000.0, -8000.0, 0, 255, true); //fade in from background
    ofSetColor(c1);
    
    ofDrawLine(points[i], ofPoint(points[i].x, points[i].y, points[i].z -  (3000 * vq.getParameters().pots[0])));

    ofColor c2 = c1;
    c2.setHue((int)((ofGetElapsedTimeMillis() * 0.005) + i * 10 + (255/2))% 255); // rotate colours by 180
    ofSetColor(c2);


    ofPushMatrix();
    ofTranslate(points[i]);
    icoSphere.setRadius( vq.getParameters().pots[4] * 150 );
    icoSphere.draw();

    if(vq.getParameters().buttons[2]){
      ofSetColor(c1);
      icoSphere.drawWireframe();      
    }

    ofPopMatrix();
    ofPopMatrix();

  }

  camera.end();
  fbo.end();

  ofSetColor(255);
  fbo.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());

  ofSetColor(255);
  ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 50, 50);
}

//--------------------------------------------------------------
void ofApp::exit(){}
