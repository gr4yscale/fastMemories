#pragma once

#include "ofMain.h"

// Must be defined to instantiate template classes
#define TXMP_STRING_TYPE std::string

// Must be defined to give access to XMPFiles
#define XMP_INCLUDE_XMPFILES 1

#ifdef TARGET_OSX
#define MAC_ENV 1
#endif

// Ensure XMP templates are instantiated
#include "XMP.incl_cpp"

// Provide access to the API
#include "XMP.hpp"

struct Photo
{
    string fileName;
    double time_taken;
    string dateTimeTakenString;
};

class ofApp : public ofBaseApp{

    private:
        void loadDirectory(ofDirectory dir);
        void loadXMP(string path);
        bool currentFileIndexWithinBounds();
        void updateTexture();
        void loadImagesMetadata();
        void drawGUI();
        long currentFileIndex();
        void loadXMPTest(const char * fileName);
    
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
    
        ofDirectory photosDir;
		ofTrueTypeFont statusFont;
        ofTrueTypeFont indexFont;
 
        vector<ofColor> colors;
        vector<Photo> photos;
        vector<string> fileNames;
};
