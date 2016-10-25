#include "ofApp.h"
 
//--------------------------------------------------------------
void ofApp::setup(){
  

  pui.setup();
  //pui.setControllable ( &effect );
  pui.setMasterControllable( this );

  guiMode = false;
  mode = 1;

  setMode( mode );

  for( int i = 0; i < 8; i++ )
  {
    sourceParams[i] = 0.0;
    effectParams[i] = 0.0;    
  }

  myFont.loadFont( "arial.ttf", 64 );


  debug = true;
  
  wWidth = ofGetWidth();
  wHeight = ofGetHeight();

  
  ofSetVerticalSync(true);
  ofEnableAlphaBlending();
  

  camSource.setup();
  cout << "SETTING UP VID SOURCE" << endl;
//  videoSource.setup();

	//set up fbos
	fboThisFrame.allocate( ofGetWidth(), ofGetHeight() );
	fboLastFrame.allocate( ofGetWidth(), ofGetHeight() );

	//clear fbos
	fboThisFrame.begin();
	ofClear( 255, 255, 255, 0 );
	fboThisFrame.end();

	fboLastFrame.begin();
	ofClear( 255, 255, 255, 0 );
	fboLastFrame.end();


}


//------UPDATE-----------------------------------------------
void ofApp::update(){

  ofBackground( 0, 0, 0 );

  pui.update();

  if(mode == 0 ) pui.getParams( sourceParams );
  if(mode == 1 ) pui.getParams( effectParams );  

  camSource.update();
  //videoSource.update();
	renderFrame();
}







// DRAW DRAW DRAW DRAW DRAW DRAW
//--------------------------------------------------------------
void ofApp::draw(){
  //ofSetHexColor(0xffffff);
	ofClear(0, 0, 0);	
	fboThisFrame.draw( 0, 0 );

  if( guiMode )
  {
    //draw gui
    ofSetColor( 50, 50, 50, 200 );
    ofRect( 30, 30, wWidth - 60, wHeight - 60 );
    ofSetColor( 255, 255, 255, 255 );
  }

}



void ofApp::renderFrame()
{
  effect.render( fboThisFrame, camSource.texture, fboLastFrame.getTextureReference(0), effectParams );
  //effect.render( fboThisFrame, videoSource.getTextureReference(), fboLastFrame.getTextureReference(0), effectParams );

  fboLastFrame.begin();
  fboThisFrame.draw( 0, 0 );
  fboLastFrame.end();	
}






//--------------------------------------------------------------
void ofApp::exit()
{
  cout << endl << "EXIT CALLED" << endl;
  camSource.close();
  //videoSource.close();
  pui.close();
}




//--------------------------------------------------------------
void ofApp::keyPressed(int key){ 

  if( key == '0' )
  {
    pui.setLed( 0, 0, 0 );
  }
  if( key == '1' )
  {
    pui.setLed( 1, 0, 0 );
  }
  if( key == '2' )
  {
    pui.setLed( 0, 1, 0 );
  }
  if( key == '3' )
  {
    pui.setLed( 0, 0, 1 );
  }
  if( key == '4' )
  {
    pui.setLed( 1, 1, 0 );
  }
  if( key == '5' )
  {
    pui.setLed( 1, 0, 1 );
  }
  if( key == '6' )
  {
    pui.setLed( 0, 1, 1 );
  }
  if( key == '7' )
  {
    pui.setLed( 1, 1, 1 );
  }


  if( key == 'X' )
  {

    cout << "EXIT!  SHUTTING DOWN!" << endl;
    system("shutdown -h now");
//    ofExit();
  }


  if( key == 'p' )
  {
    for( int i = 0; i < 8; i++ )
    {
      cout << "effect param[" << i <<"] = " << effectParams[i] << endl;
    }
  }

if( key == 'q' || key =='Q' )
  {
    ofExit();
  }
  
  
  
}



void ofApp::buttonPress(int i)
{

  if( i == 0 )
  {
    setMode( !mode );
  } 
  
}
void ofApp::buttonRelease(int i)
{}
void ofApp::buttonLongPress(int i)
{}




//--------------------------------------------------------------
void ofApp::setMode( int m )
{
  mode = m;
  pui.setLed(!mode, 0, mode);

  if( mode == 0 ) 
  {
    //pui.setControllable( &videoSource );
    pui.setControllable( &camSource );
  }
  else
  {
    pui.setControllable( &effect );
  }
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



