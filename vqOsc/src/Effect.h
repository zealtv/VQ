#pragma once
#include "Controllable.h"
#include "Pui.h"

class Effect : public Controllable
{
	public:
		Effect();

		void render(ofFbo &fbo, ofTexture &thisFrame, ofTexture &lastFrame, float *params);

		void buttonPress(int i);
		void buttonRelease(int i);
		void buttonLongPress(int i);

	private:
		void loadShader();
		void loadShader(int i);
		void createShaderList();	

		ofShader shader;
    	vector<ofFile> shaderList;
    	int numShaders;
    	int currentShader;
    	bool useShader;    	
    	float params[];
};