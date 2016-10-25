#include "VQListener.h"
//--------------------------------------------------------------
void VQListener::setup(int port){
    cout << "listening for osc messages on port 5050\n";
    receiver.setup(port);
}

//--------------------------------------------------------------
void VQListener::update(){
    getOsc();
    //do any smoothing here
}

//--------------------------------------------------------------
Parameters& VQListener::getParameters(){
  return parameters;
}

//--------------------------------------------------------------
void VQListener::getOsc(){
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(m);

        //get potentiometers
        for(int i = 0; i < 8; i++)
            if(m.getAddress() == "/p")
                parameters.pots[i] = m.getArgAsFloat(i);

        //get buttons
        for(int i = 0; i < 5; i++)
            if(m.getAddress() == "/b")
                parameters.buttons[i] = m.getArgAsInt(i);
    }
}
