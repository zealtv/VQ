#pragma once
#include "VQListener.h"

class ofApp : public ofBaseApp{
public:
    // main
    void setup();
    void update();
    void draw();
    void exit();

    VQListener vq;
    vector<ofPoint> points;

    int numPoints;
};
