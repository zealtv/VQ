#pragma once
#include "ofxOsc.h"

struct Parameters{
    float pots[8];
    int buttons[5];
};

class VQListener{
public:
  void setup(int port);
  void update();
  Parameters& getParameters();
  void getOsc();
private:
  Parameters parameters;
  ofxOscReceiver receiver;
};
