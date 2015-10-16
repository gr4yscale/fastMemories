#include "ofApp.h"

void ofApp::setup(){

    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    
    cout << "setup" << endl;

//    oscController = new OSCController(config::oscReceiverPort, state);
    
    cout << "pre filecontroller";
    
    fileController = * new FileController();
    
    
    cout << "presyphon" << endl;
    
    outputSyphonServer.setName("fastMemories syphon server");
    
    statusFont.loadFont("Ubuntu Mono derivative Powerline Bold.ttf", 32);
    indexFont.loadFont("Ubuntu Mono derivative Powerline Bold.ttf", 200);
    
    cout << "about to load filepaths" << endl;
    fileController.loadFilePaths();
}

void ofApp::update(){
    
    oscController.update();
    
    if (state.paused) return;
    
    state.fileIndex += state.frameChangeDelta;
    
    if (state.fileIndex >= fileController.fileNames.size() - 1) {
        state.fileIndex = fileController.fileNames.size() - 1;
    } else if (state.fileIndex <= 0) {
        state.fileIndex = 0;
    }
    
    updateTexture();
}

void ofApp::draw(){

    if (state.syphonEnabled) {
        outputSyphonServer.publishTexture(&texture);
    } else {
        ofPushMatrix();
            ofTranslate((ofGetWidth() - texture.getWidth()) / 2.0, 0);
            texture.draw(0, 0);
        ofPopMatrix();
    }
    
    drawGUI();
}


void ofApp::loadColorsTestData() {

    // load table of random colors for testing without images
    for (int i = 0; i < 3000; i++) {
        colors.push_back(ofColor(ofRandom(255),ofRandom(255), ofRandom(255)));
    }
}
void ofApp::drawGUI() {

    ofSetColor(255, 255, 255, 255);
    
//    statusFont.drawString(ofToString(fileNames.getName(currentFileIndex())), 10, 40);
//    indexFont.drawString(ofToString(currentFileIndex()), ofGetWidth() / 2.0 - 160.0, ofGetHeight() / 2.0);
//    ofSetColor(255, 255, 255, 100);
    
    float markerWidth = (400.0 * state.frameChangeDelta);
    ofRect(ofGetWidth() / 2.0, ofGetHeight() - 20.0, markerWidth, 8);
}

void ofApp::updateTexture() {

    ofLoadImage(texture, fileController.fileNames[currentFileIndex()]);
}

long ofApp::currentFileIndex() {

    return floor(state.fileIndex);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key) {
        case OF_KEY_RIGHT:
            state.fileIndex++;
            updateTexture();
            break;
        case OF_KEY_LEFT:
            state.fileIndex--;
            updateTexture();
            break;
        case ' ':
            state.paused = !state.paused;
            break;
        case 'p':
            state.paused = !state.paused;
            break;
        case 's':
            state.syphonEnabled = !state.syphonEnabled;
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

    if (state.updatingFrameRate) {
        state.frameChangeDelta = ofMap(x, 0, ofGetWidth(), -1.1, 1.1);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    state.updatingFrameRate = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    state.updatingFrameRate = false;
}