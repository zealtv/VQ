#pragma once
#include "ofMain.h"
#include "Controllable.h"

#define MAX_NUM_VIDEOS 12

class VideoSource : public Controllable
{
	//typedef ofPtr<ofVideoPlayer> vpPtr;
	public:
		void setup();
		void update();
		void close();
		ofTexture& getTextureReference();



	private:
		void createVideoList();
		void loadVideo();		


		ofVideoPlayer videoPlayers[MAX_NUM_VIDEOS];
		vector<ofFile> videoList;
		int numVideos;
		int currentVideo;

		void buttonPress(int i);
		void buttonRelease(int i);
		void buttonLongPress(int i);
};