#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(230, 10, 230);
	sender.setup(HOST, PORT);

	gui.setup();
	for(int i = 0; i < 8; i++){
		gui.add(pots[i].set(ofToString(i + 1),0.0,0.0,1.0));
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
			newPotMessage = true;
		}
	}

	if(newPotMessage){
		ofxOscMessage m;
		m.setAddress("/p");
		for(int i = 0; i < 8; i++)	
			m.addFloatArg(pots[i].get());	
	
		sender.sendMessage(m, false);
	}

	if(newButtonMessage){
		ofxOscMessage m;
		m.setAddress("/b");
		for(int i = 0; i < 5; i++)	
			m.addIntArg((int)buttons[i].get());	
	
		sender.sendMessage(m, false);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
   	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == 'a' || key == 'A'){
		ofxOscMessage m;
		m.setAddress("/test");
		m.addIntArg(1);
		m.addFloatArg(3.5f);
		m.addStringArg("hello");
		m.addFloatArg(ofGetElapsedTimef());
		sender.sendMessage(m, false);
	}
    

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

