#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

    private:
        bool currentFileIndexWithinBounds();
        void updateTexture();

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
        float frameChangeDelta;
        long currentFileIndex = 0;
        string currentFileName;
    
        ofImage img;
        ofTexture texture;
    
        ofDirectory dir;
		ofTrueTypeFont statusFont;
    
    
    
};
