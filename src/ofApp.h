#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

    private:
        bool currentFileIndexWithinBounds();
        void updateTexture();
        void drawGUI();
        long currentFileIndex();

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        // state
        bool paused = 0;
        bool updatingFrameRate = 0;
        float frameChangeDelta;
        double preciseFileIndex = 0;
    
        ofImage img;
        ofTexture texture;
    
        ofDirectory dir;
		ofTrueTypeFont statusFont;
        ofTrueTypeFont indexFont;
 
        vector<ofColor> colors;
};
