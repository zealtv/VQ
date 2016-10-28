#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(230, 10, 230);
	sender.setup(HOST, PORT);

	gui.setup();
	for(int i = 0; i < 8; i++){
		gui.add(pots[i].set(ofToString(i),0.0,0.0,1.0));
		potValues[i] = 0;
	}
		
	for(int i = 0; i < 5; i++){
		gui.add(buttons[i].set(ofToString(i),false));
		buttonValues[i] = 0;
	}
		
}

//--------------------------------------------------------------
void ofApp::update(){
	bool newPotMessage = false;
	for(int i = 0; i < 8; i++){
		if(potValues[i] != pots[i].get()){
			potValues[i] = pots[i].get();
			newPotMessage = true;
		}
	}

	bool newButtonMessage = false;
	for(int i = 0; i < 5; i++){
		if(buttonValues[i] != (int)buttons[i].get()){
			buttonValues[i] = (int)buttons[i].get();
			newButtonMessage = true;
		}
	}

	if(newPotMessage){
		lastMessage = "";
		ofxOscMessage m;
		m.setAddress("/p");
		lastMessage += "/p";
		for(int i = 0; i < 8; i++){	
			m.addFloatArg(potValues[i]);
			lastMessage += " " + ofToString(potValues[i]);
			if(i == 3)
				lastMessage += "    \n";
		}	
	
		sender.sendMessage(m, false);
	}

	if(newButtonMessage){
		lastMessage = "";
		ofxOscMessage m;
		m.setAddress("/b");
		lastMessage += "/b";
		for(int i = 0; i < 5; i++){
			m.addIntArg(buttonValues[i]);	
			lastMessage += " " + ofToString(buttonValues[i]);
		}
	
		sender.sendMessage(m, false);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
   	gui.draw();
   	ofDrawBitmapString(lastMessage, 10, ofGetHeight() - 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	// ofxOscMessage m;
	// m.setAddress("/mouse/button");
	// m.addIntArg(button);
	// m.addStringArg("up");
	// sender.sendMessage(m, false);

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

