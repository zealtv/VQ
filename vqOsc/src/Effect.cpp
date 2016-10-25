#include "Effect.h"

Effect::Effect()
{
	useShader = false;


  //this could break things if there are no shaders found
	currentShader = 1;

	createShaderList();
	loadShader();
}


//--------------------------------------------------------------
void Effect::render(ofFbo &fbo, ofTexture &thisFrame, ofTexture &lastFrame, float *params)
{

	fbo.begin();
	ofClear( 0, 0, 0 );

  shader.begin();
  shader.setUniformTexture( "tex0", thisFrame, 0 );
  shader.setUniformTexture( "tex1", lastFrame, 1 );
  shader.setUniform1f( "param0", params[0] );
  shader.setUniform1f( "param1", params[1] );
  shader.setUniform1f( "param2", params[2] );
  shader.setUniform1f( "param3", params[3] );
  shader.setUniform1f( "param4", params[4] );    
  shader.setUniform1f( "millis", ofGetElapsedTimeMillis() );    

	ofSetColor( 255, 255, 255 );
	thisFrame.draw( 0.0, 0.0, ofGetWidth(), ofGetHeight() );

  shader.end();

	fbo.end();


}


//--------------------------------------------------------------
void Effect::createShaderList()
{

  cout << endl << "creating shader list" << endl;

  ofDirectory dir( "effects" );
  dir.allowExt( "frag" );
  dir.listDir();
  numShaders = dir.numFiles();
  cout << "number of shaders: " << numShaders << endl;
  //currentShader = numShaders - 1;

  shaderList = dir.getFiles(); //returns vector<ofFile>
  for( vector<ofFile>::iterator it = shaderList.begin(); it != shaderList.end(); ++it )
  {
    cout << it->getFileName() << endl;
    cout << "path: " << it->path() << endl;
  }


}


//--------------------------------------------------------------
void Effect::loadShader()
{
  string fileName = shaderList[currentShader].getFileName();
  int lastindex = fileName.find_last_of( "." ); 
  string fileNameNoExt = fileName.substr( 0, lastindex ); 
  string shaderString = "effects/" + fileNameNoExt;
  shader.load( shaderString );
}


//--------------------------------------------------------------
void Effect::loadShader( int i )
{
  currentShader += i;
  if( currentShader < 0 ) currentShader = numShaders - 1;
  else if( currentShader > numShaders - 1 ) currentShader = 0;

  cout << endl << "loading " << shaderList[currentShader].getFileName() << "current shader = " << currentShader << endl;

  loadShader();
}



//--------------------------------------------------------------
void Effect::buttonPress(int i)
{

	switch( i )
	{
		case 0:
        break;

		case 1:
        break;

		case 2:
		    loadShader( 1 );
        break;

		case 3:
		    loadShader( -1 );
        break;

		case 4:
        break;

		case 5:
        break;                
	}

}


//--------------------------------------------------------------
void Effect::buttonRelease(int i){}

//--------------------------------------------------------------
void Effect::buttonLongPress(int i){}