#include "ofApp.h"

static FILE * sLogFile = stdout;

static XMP_Status DumpCallback ( void * refCon, XMP_StringPtr outStr, XMP_StringLen outLen )
{
    XMP_Status	status	= 0;
    size_t		count;
    FILE *		outFile	= static_cast < FILE * > ( refCon );
    
    count = fwrite ( outStr, 1, outLen, outFile );
    if ( count != outLen ) status = errno;
    return status;
    
}

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    
    outputSyphonServer.setName("fastMemories syphon server");
    
    statusFont.loadFont("Ubuntu Mono derivative Powerline Bold.ttf", 32);
    indexFont.loadFont("Ubuntu Mono derivative Powerline Bold.ttf", 200);
    
    loadFilePaths();
//    loadMetadata();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (paused) return;
    
    preciseFileIndex += frameChangeDelta;
    
    if (preciseFileIndex >= fileNames.size() - 1) {
        preciseFileIndex = fileNames.size() - 1;
    } else if (preciseFileIndex <= 0) {
        preciseFileIndex = 0;
    }
    
    updateTexture();
}

//--------------------------------------------------------------
void ofApp::draw(){

    if (syphonEnabled) {
        outputSyphonServer.publishTexture(&texture);
    } else {
        ofPushMatrix();
            ofTranslate((ofGetWidth() - texture.getWidth()) / 2.0, 0);
            texture.draw(0, 0);
        ofPopMatrix();
    }
    
    drawGUI();
}

void ofApp::loadDirectory(ofDirectory dir) {
    
    int size = dir.listDir();
    for(int i = 0; i < size; i++) {
        if (dir.getFile(i).isDirectory() == 1) {
            ofDirectory subDir(dir.getFile(i).getAbsolutePath());
            subDir.allowExt("jpg");
            subDir.allowExt("JPG");
            loadDirectory(subDir);
        } else {
            fileNames.push_back(dir.getPath(i));
        }
    }
}

void ofApp::loadColorsTestData() {
    // load table of random colors for testing without images
    for (int i = 0; i < 3000; i++) {
        colors.push_back(ofColor(ofRandom(255),ofRandom(255), ofRandom(255)));
    }
}

void ofApp::loadFilePaths() {
    string exportedDir = "/Volumes/1TB Ext SSD 2/[spazzyvideo]/2013-iphone";
    loadDirectory(exportedDir);
}

void ofApp::loadMetadata() {

    string originalDir = "/Users/gr4yscale/[fastMemoriesTest]/source";
    string exportedDir = "/Users/gr4yscale/[fastMemoriesTest]/exported";
    
    if(!SXMPMeta::Initialize()){
        ofLogError() << "Could not initialize XMP toolkit!";
        return;
    } else{
        ofLogVerbose() << "Initialised XMP toolkit";
    }
    
    XMP_OptionBits options = 0;
    
    // Must initialize SXMPFiles before we use it
    if(!SXMPFiles::Initialize(options)){
        ofLogError() << "Could not initialize XMP SXMPFiles.";
        return;
    } else{
        ofLogVerbose() << "Initialised XMP SXMPFiles";
    }
    
    // load xmp files and sort photos array by XMP
    
    for(int i = 0; i < fileNames.size(); i++) {
        string path = fileNames[i];
        size_t lastSlashIndex = path.find_last_of("/");
        string subPath = path.substr(exportedDir.length() + 1, lastSlashIndex - exportedDir.length() - 1);
        string originalFileName = path.substr(lastSlashIndex + 18, path.length() - lastSlashIndex);
        string sourceXMPFileName = originalFileName.replace(originalFileName.end() - 3, originalFileName.end(), "xmp");
        string xmpFileNameFullPath = originalDir + "/" + subPath + "/" + sourceXMPFileName;
        
        loadXMPTest(xmpFileNameFullPath.c_str());
        break;
    }
}

void ofApp::loadXMPTest(const char * fileName) {
    bool ok;
    char buffer [1000];
    
    SXMPMeta  xmpMeta;
    SXMPFiles xmpFile;
    XMP_FileFormat format;
    XMP_OptionBits openFlags, handlerFlags;
    XMP_PacketInfo xmpPacket;
    
    cout << "derpin";
    cout << fileName;
    
    sprintf ( buffer, "Dumping main XMP for %s", fileName );
//    WriteMinorLabel ( sLogFile, buffer );
    
    xmpFile.OpenFile ( fileName, kXMP_UnknownFile, kXMPFiles_OpenForRead );
    ok = xmpFile.GetFileInfo ( 0, &openFlags, &format, &handlerFlags );
    if ( ! ok ) return;
    
    fprintf ( sLogFile, "File info : format = \"%.4s\", handler flags = %.8X\n", &format, handlerFlags );
    fflush ( sLogFile );
    
    cout << " goin for it";
    
    ok = xmpFile.GetXMP ( &xmpMeta, 0, &xmpPacket );
    if ( ! ok ) return;
    
    
    cout << "here now";
    
    XMP_Int32 offset = (XMP_Int32)xmpPacket.offset;
    XMP_Int32 length = xmpPacket.length;
    fprintf ( sLogFile, "Packet info : offset = %d, length = %d\n", offset, length );
    fflush ( sLogFile );
    
    fprintf ( sLogFile, "\nInitial XMP from %s\n", fileName );
    xmpMeta.DumpObject ( DumpCallback, sLogFile );
    
    xmpFile.CloseFile();
}

void ofApp::loadXMP(string path){
    
    ofLogVerbose() << "Attempting to load XMP from: " << path;
    
    try {
        // Options to open the file with - read only and use a file handler
        XMP_OptionBits opts = kXMPFiles_OpenForRead | kXMPFiles_OpenUseSmartHandler;
        
        bool ok;
        
        SXMPMeta::Initialize();
        
        SXMPFiles myFile;
        std::string status = "";
        
        // First we try and open the file
        ok = myFile.OpenFile(path, kXMP_UnknownFile, opts);
        if (!ok) {
            status += "No smart handler available for " + path + "\n";
            status += "Trying packet scanning.\n";
            
            // Now try using packet scanning
            opts = kXMPFiles_OpenForRead | kXMPFiles_OpenUsePacketScanning;
            ok = myFile.OpenFile(path, kXMP_UnknownFile, opts);
        }
        
        // If the file is open then read the metadata
        if (ok) {
            ofLogVerbose() << status;
            ofLogVerbose() << path << " is opened successfully";
            
            // Create the xmp object and get the xmp data
            SXMPMeta meta;
            if (myFile.GetXMP(&meta, NULL, NULL)) {
                cout << "yup";
            } else {
                cout << "nah";
            }

//            string labelValue = "";
//            string labelPath = "Label";
//            meta.GetProperty(kXMP_NS_XMP, labelPath.c_str(), &labelValue, NULL);
//            cout << labelValue;
            
//            meta.DumpObject(dumpXMPObject, NULL);
            
            SXMPIterator iter(meta, kXMP_NS_RDF);
            string schemaNS="", propPath="", propVal="";
            while(iter.Next(&schemaNS, &propPath, &propVal)){
                cout << propPath << " = " << propVal << endl;
            }
            
        } else {
            ofLogError() << "Unable to open " << path;
        }

        myFile.CloseFile();
        
    } catch(XMP_Error & e) {
        ofLogError() << "ERROR: " << e.GetErrMsg();
    }
}



void ofApp::drawGUI() {

    ofSetColor(255, 255, 255, 255);
    
//    statusFont.drawString(ofToString(fileNames.getName(currentFileIndex())), 10, 40);
//    indexFont.drawString(ofToString(currentFileIndex()), ofGetWidth() / 2.0 - 160.0, ofGetHeight() / 2.0);
//    ofSetColor(255, 255, 255, 100);
    
    float markerWidth = (400.0 * frameChangeDelta);
    ofRect(ofGetWidth() / 2.0, ofGetHeight() - 20.0, markerWidth, 8);
}

void ofApp::updateTexture() {

    ofLoadImage(texture, fileNames[currentFileIndex()]);
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
        case 's':
            syphonEnabled = !syphonEnabled;
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
