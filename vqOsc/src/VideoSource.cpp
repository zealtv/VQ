#include  "VideoSource.h"

//--------------------------------------------------------------
void VideoSource::setup()
{

	currentVideo = 0;
	createVideoList();

	for(int i = 0; i < numVideos; i++ )
	{
		cout << "loading " << videoList[i].path() << endl;
		videoPlayers[i].loadMovie( videoList[i].path() );
		videoPlayers[i].play();
		videoPlayers[i].setPaused(true);
	}

	loadVideo();
}


//--------------------------------------------------------------
void VideoSource::createVideoList()
{

	cout << "creating video list" << endl;
	ofDirectory dir("/media/usb/videos");
	dir.allowExt( "mov" );
	dir.allowExt( "mp4" );	
	dir.listDir();
	numVideos = dir.numFiles();

	cout << "number of videos: " << numVideos << endl;

	if( numVideos > MAX_NUM_VIDEOS )
	{
		cout << "too many vids.  limiting to " << MAX_NUM_VIDEOS << endl;
		numVideos = MAX_NUM_VIDEOS;
	}

	videoList = dir.getFiles();
	/*for( vector<ofFile>::iterator it = videoList.begin(); it != videoList.end(); ++it )
	{
		cout << it->getFileName() << endl;
		cout << "path: " << it->path() << endl;
	}*/

}





//--------------------------------------------------------------
void VideoSource::loadVideo()
{
	videoPlayers[ currentVideo ].setPaused(false);
}



//--------------------------------------------------------------
void VideoSource::update()
{
	videoPlayers[ currentVideo ].update();
}



//--------------------------------------------------------------
void VideoSource::close()
{
	for( int i = 0; i < numVideos; i++ )
	{
		videoPlayers[i].close();	
	}
}




//--------------------------------------------------------------
ofTexture& VideoSource::getTextureReference()
{
	return videoPlayers[ currentVideo ].getTextureReference();
}



//--------------------------------------------------------------
void VideoSource::buttonPress(int i){
	switch( i )
	{
		case 0:
        break;

		case 1:
        break;

		case 2:
			videoPlayers[ currentVideo ].setPaused(true);
			if( ++currentVideo >= numVideos ) currentVideo = 0;
		    loadVideo();
        break;

		case 3:
			videoPlayers[ currentVideo ].setPaused(true);
			if( --currentVideo < 0 ) currentVideo = numVideos - 1;
		    loadVideo();
        break;

		case 4:
        break;

		case 5:
        break;                
	}
}

//--------------------------------------------------------------
void VideoSource::buttonRelease(int i){}

//--------------------------------------------------------------
void VideoSource::buttonLongPress(int i){}

