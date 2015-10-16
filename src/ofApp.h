#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "State.h"
#include "FileController.h"
#include "OSCController.h"
#include "Config.h"

class ofApp : public ofBaseApp{

    private:
        long currentFileIndex();
        void updateTexture();
        void loadColorsTestData();
        void drawGUI();
    
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
    
        State state;
        FileController fileController;
        OSCController oscController;
        ofxSyphonServer outputSyphonServer;

        ofImage img;
        ofTexture texture;
		ofTrueTypeFont statusFont;
        ofTrueTypeFont indexFont;
 
        vector<ofColor> colors;
    
        // communication
};
