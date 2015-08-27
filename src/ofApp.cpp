#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    
    statusFont.loadFont("Ubuntu Mono derivative Powerline Bold.ttf", 32);
    
    string photosDirectory = "/Volumes/1TB Ext SSD 2/[spazzyvideo]/2014-iPhone";

    dir.open(photosDirectory);
    dir.allowExt("jpg");
    dir.listDir();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (paused) return;
    
    if (frameChangeDelta >= 0) {
        currentFileIndex++;
    } else {
        currentFileIndex--;
    }
    
    if (currentFileIndexWithinBounds()) {
        currentFileName = dir.getName(currentFileIndex);
        updateTexture();
    }
    
    ofSetFrameRate(abs(frameChangeDelta));
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofPushMatrix();
        ofTranslate((ofGetWidth() - texture.getWidth()) / 2.0, 0);
        texture.draw(0, 0);
    ofPopMatrix();
    
    statusFont.drawString(currentFileName + ", FPS: " + ofToString(frameChangeDelta), 10, 40);
}

void ofApp::updateTexture() {
    ofLoadImage(texture, dir.getPath(currentFileIndex));
}

bool ofApp::currentFileIndexWithinBounds() {
    if ((currentFileIndex < dir.numFiles() - 1) &&
        (currentFileIndex > 0)) return true;
    return false;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case OF_KEY_RIGHT:
            currentFileIndex++;
            updateTexture();
            break;
        case OF_KEY_LEFT:
            currentFileIndex--;
            updateTexture();
        case 'p':
            paused = !paused;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    frameChangeDelta = (x - (ofGetWidth() / 2)) * 0.1;
//    cout << val << endl;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    paused = !paused;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
