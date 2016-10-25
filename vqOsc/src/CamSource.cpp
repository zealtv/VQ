#include "CamSource.h"


//--------------------------------------------------------------
void CamSource::setup()
{
//SET UP CAMERA
  camWidth    = 640;  // try to grab at this size.
  camHeight   = 480;
  currentDevice = 0;
  
    //we can now get back a list of devices. 
  vector<ofVideoDevice> devices = grabber.listDevices();
  numDevices = devices.size();


  for( int i = 0; i < numDevices; i++ )
  {
    cout << devices[i].id << ": " << devices[i].deviceName; 
    if( devices[i].bAvailable )
    {
    	cout << endl;
    }
    else
    {
    	cout << " - unavailable " << endl; 
    }
  }
    
  grabber.setDeviceID( 0 );
  grabber.setDesiredFrameRate( 25 );
  grabber.initGrabber( camWidth, camHeight );
  texture = grabber.getTextureReference();
  
}


//--------------------------------------------------------------
void CamSource::update()
{
	grabber.update();
}

void CamSource::close()
{
  grabber.close();
}

void CamSource::changeSource( int i )
{
  grabber.close();
  loadSource( i );
}

void CamSource::loadSource( int i )
{
  grabber.setDeviceID( i );
  grabber.setDesiredFrameRate( 25 );
  grabber.initGrabber( camWidth, camHeight );
  texture = grabber.getTextureReference();
}


void CamSource::buttonPress(int i){
  switch( i )
  {
    case 2:

      //back one device
      --currentDevice;
      if( currentDevice < 0 ) currentDevice = numDevices - 1;

      changeSource( currentDevice );

    break;


    case 3:

      //forward one device
      ++currentDevice;
      if( currentDevice >= numDevices ) currentDevice = 0;

      changeSource( currentDevice );

    break;
  }
}

void CamSource::buttonRelease(int i){}
void CamSource::buttonLongPress(int i){}
