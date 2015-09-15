#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    
    statusFont.loadFont("Ubuntu Mono derivative Powerline Bold.ttf", 32);
    indexFont.loadFont("Ubuntu Mono derivative Powerline Bold.ttf", 200);
    
    // recurse subdirectories?
    
    string photosDirectory = "/Users/gr4yscale/Desktop/[fastMemoriesTest]";

    dir.open(photosDirectory);
    dir.allowExt("jpg");
    dir.allowExt("JPG");
    dir.listDir();
    
    // load table of random colors for testing without images
    for (int i = 0; i < 3000; i++) {
        colors.push_back(ofColor(ofRandom(255),ofRandom(255), ofRandom(255)));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (paused) return;
    
    preciseFileIndex += frameChangeDelta;
    
    if (preciseFileIndex >= colors.size()) {
        preciseFileIndex = colors.size();
    } else if (preciseFileIndex <= 0) {
        preciseFileIndex = 0;
    }
    
    //        updateTexture();
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofColor color = colors[currentFileIndex()];
    ofBackground(color);
    drawGUI();
}

void ofApp::drawGUI() {

    ofSetColor(255, 255, 255, 255);
    
//    statusFont.drawString(ofToString(dir.getName(currentFileIndex())), 10, 40);
    indexFont.drawString(ofToString(currentFileIndex()), ofGetWidth() / 2.0 - 160.0, ofGetHeight() / 2.0);
    
    ofSetColor(255, 255, 255, 100);
    
    float markerWidth = (400.0 * frameChangeDelta);
    ofRect(ofGetWidth() / 2.0, ofGetHeight() - 40.0, markerWidth, 20);
}

void ofApp::updateTexture() {

    ofLoadImage(texture, dir.getPath(currentFileIndex()));
}

long ofApp::currentFileIndex() {

    return floor(preciseFileIndex);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key) {
        case OF_KEY_RIGHT:
            preciseFileIndex++;
            updateTexture();
            break;
        case OF_KEY_LEFT:
            preciseFileIndex--;
            updateTexture();
            break;
        case ' ':
            paused = !paused;
            break;
        case 'p':
            paused = !paused;
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

    if (updatingFrameRate) {
        frameChangeDelta = ofMap(x, 0, ofGetWidth(), -1.1, 1.1);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    updatingFrameRate = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    updatingFrameRate = false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){ }

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ }

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
