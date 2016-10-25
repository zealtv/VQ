#pragma once
#include "VQListener.h"

class ofApp : public ofBaseApp{
public:
    // main
    void setup();
    void update();
    void draw();
    void exit();
    void drawValue(int x, int y, float w, float h, float value);

    VQListener vq;
};
