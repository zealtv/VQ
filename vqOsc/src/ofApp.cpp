#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetFrameRate(60);
  //SET UP OSC
  oscSender.setup("192.168.1.255", 5050);

  //SET UP WIRINGPI
  if( wiringPiSetup() == -1 )
    cout << "WiringPiSetup Failed!" << endl;
  else
    cout << "WiringPiSetup() Succeeded!" << endl;

  //SETUP POTENTIOMETERS
  potController.setup();

  for(int i = 0; i < 8; i++){
    params[i] = 0.0;
    lastParams[i] = 0.0;
  }

  //SETUP LED
  pinMode( 0,OUTPUT );
  pinMode( 2,OUTPUT );
  pinMode( 3,OUTPUT );

  boolLedR = false;
  boolLedG = false;
  boolLedB = false;

  //turn off LED
  digitalWrite( 0, 1 );
  digitalWrite( 2, 1 );
  digitalWrite( 3, 1 );

  //SETUP BUTTONS
  pinMode( 4, INPUT );
  pullUpDnControl( 4, PUD_UP ); //switch on internal pull up resistor
  pinMode( 5, INPUT );
  pullUpDnControl( 5, PUD_UP ); //switch on internal pull up resistor
  pinMode( 6, INPUT );
  pullUpDnControl( 6, PUD_UP ); //switch on internal pull up resistor
  pinMode( 7, INPUT );
  pullUpDnControl( 7, PUD_UP ); //switch on internal pull up resistor
  pinMode( 8, INPUT );  // has built in pull up resistor
  pinMode( 9, INPUT );  // has built in pull up resistor


  for( int i = 0; i < 6; i++ ){
    buttonLastState[i] = false;
    buttonTimePressed[i] = 0.0;
    buttonTimeReleased[i] = 0.0;
    buttonCheckLongPress[i] = true;
  }

}


//------UPDATE-----------------------------------------------
void ofApp::update(){
  updateButtons();
  updateParams();
  potController.update();

  // bool change = false;
}

//--------------------------------------------------------------
void ofApp::updateParams(){
  //send pots as oscSender
  if(potController.hasNewValue){
    ofxOscMessage m;
    m.setAddress("/p");
    for(int i = 0; i < NUMPOTS; i++)
      m.addFloatArg(potController.potValues[i]);
    oscSender.sendMessage(m);
  }
}


//--------------------------------------------------------------
void ofApp::updateButtons(){

  bool change = false;

	//read buttons
	for( int i = 0; i < 6; i++ )
		buttonCurrentState[i] = digitalRead( i + 4 );

	//check for long presses
	for( int i = 0; i < 6; i++ ){
		if( buttonLastState[i] == 0 && buttonCurrentState[i] == 0 && buttonCheckLongPress[i] )
		    if( ofGetElapsedTimeMillis() - buttonTimePressed[i] > 1000.0 )  //compare current time and previous time
					buttonCheckLongPress[i] = false;

		//check for press and releases
		if( buttonCurrentState[i] != buttonLastState[i] ){
      change = true;
			if( buttonCurrentState[i] == 0 ) //press
				buttonTimePressed[i] = ofGetElapsedTimeMillis();  //start timer
			else
				buttonCheckLongPress[i] = true;  //release
			buttonLastState[i] = buttonCurrentState[i];
		}
	}

  //send buttons as osc
  if(change){
    ofxOscMessage m;
    m.setAddress("/b");
    //remap buttons and invert state
      m.addInt32Arg(1 - buttonCurrentState[0]);  //0
      m.addInt32Arg(1 - buttonCurrentState[4]);  //1
      m.addInt32Arg(1 - buttonCurrentState[3]);  //2
      m.addInt32Arg(1 - buttonCurrentState[5]);  //3
      m.addInt32Arg(1 - buttonCurrentState[2]);  //4
    oscSender.sendMessage(m);
  }
}



//--------------------------------------------------------------
void ofApp::exit(){
  cout << endl << "EXIT CALLED" << endl;
  setLed( 0, 0, 0 );
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

  if( key == '0' )
    setLed( 0, 0, 0 );

  if( key == '1' )
    setLed( 1, 0, 0 );

  if( key == '2' )
    setLed( 0, 1, 0 );

  if( key == '3' )
    setLed( 0, 0, 1 );

  if( key == '4' )
    setLed( 1, 1, 0 );

  if( key == '5' )
    setLed( 1, 0, 1 );

  if( key == '6' )
    setLed( 0, 1, 1 );

  if( key == '7' )
    setLed( 1, 1, 1 );

  if( key == 'q' || key =='Q' )
      ofExit();

}

//--------------------------------------------------------------
void ofApp::setLed( bool r, bool g, bool b){
		digitalWrite(0, !r);
    digitalWrite(2, !g);
    digitalWrite(3, !b);
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
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
