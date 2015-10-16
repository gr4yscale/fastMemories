//
//  FileController.cpp
//  fastMemories
//
//  Created by Tyler Powers on 10/8/15.
//
//

#include "ofMain.h"
#include "FileController.h"

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

FileController::FileController() {
    
}

void FileController::loadFilePaths() {
    cout << "whut" << endl;
    loadDirectory(config::exportedDirectory);
}

void FileController::loadDirectory(ofDirectory dir) {
    
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

void FileController::writeMetadataPick() {
    string shPath;
    shPath = ofToDataPath( "openChildApp.sh", true );
    
    char *shPathChar;
    shPathChar = new char[ shPath.length() + 1 ];
    
    strcpy( shPathChar, shPath.c_str() );
    
    //--
    
    int pid = fork();
    
    cout << "pid :: " << pid << endl;
    
    switch ( pid )
    {
        case -1 :
            
            cout << "Uh-Oh! fork() failed.\n" << endl;
            
        case  0 :
            
            execl( shPathChar, shPathChar, NULL );
            
        default :
            
            return;
    }
}


//
//    string originalDir = "/Users/gr4yscale/[fastMemoriesTest]/source";
//    string exportedDir = "/Users/gr4yscale/[fastMemoriesTest]/exported";
//    
//    if(!SXMPMeta::Initialize()){
//        ofLogError() << "Could not initialize XMP toolkit!";
//        return;
//    } else{
//        ofLogVerbose() << "Initialised XMP toolkit";
//    }
//    
//    XMP_OptionBits options = 0;
//    
//    // Must initialize SXMPFiles before we use it
//    if(!SXMPFiles::Initialize(options)){
//        ofLogError() << "Could not initialize XMP SXMPFiles.";
//        return;
//    } else{
//        ofLogVerbose() << "Initialised XMP SXMPFiles";
//    }
//    
//    // load xmp files and sort photos array by XMP
//    
//    for(int i = 0; i < fileNames.size(); i++) {
//        string path = fileNames[i];
//        size_t lastSlashIndex = path.find_last_of("/");
//        string subPath = path.substr(exportedDir.length() + 1, lastSlashIndex - exportedDir.length() - 1);
//        string originalFileName = path.substr(lastSlashIndex + 18, path.length() - lastSlashIndex);
//        string sourceXMPFileName = originalFileName.replace(originalFileName.end() - 3, originalFileName.end(), "xmp");
//        string xmpFileNameFullPath = originalDir + "/" + subPath + "/" + sourceXMPFileName;
//        
//        loadXMPTest(xmpFileNameFullPath.c_str());
//        break;
//    }
//}
//
//void ofApp::loadXMPTest(const char * fileName) {
//    bool ok;
//    char buffer [1000];
//    
//    SXMPMeta  xmpMeta;
//    SXMPFiles xmpFile;
//    XMP_FileFormat format;
//    XMP_OptionBits openFlags, handlerFlags;
//    XMP_PacketInfo xmpPacket;
//    
//    cout << "derpin";
//    cout << fileName;
//    
//    sprintf ( buffer, "Dumping main XMP for %s", fileName );
//    //    WriteMinorLabel ( sLogFile, buffer );
//    
//    xmpFile.OpenFile ( fileName, kXMP_UnknownFile, kXMPFiles_OpenForRead );
//    ok = xmpFile.GetFileInfo ( 0, &openFlags, &format, &handlerFlags );
//    if ( ! ok ) return;
//    
//    fprintf ( sLogFile, "File info : format = \"%.4s\", handler flags = %.8X\n", &format, handlerFlags );
//    fflush ( sLogFile );
//    
//    cout << " goin for it";
//    
//    ok = xmpFile.GetXMP ( &xmpMeta, 0, &xmpPacket );
//    if ( ! ok ) return;
//    
//    
//    cout << "here now";
//    
//    XMP_Int32 offset = (XMP_Int32)xmpPacket.offset;
//    XMP_Int32 length = xmpPacket.length;
//    fprintf ( sLogFile, "Packet info : offset = %d, length = %d\n", offset, length );
//    fflush ( sLogFile );
//    
//    fprintf ( sLogFile, "\nInitial XMP from %s\n", fileName );
//    xmpMeta.DumpObject ( DumpCallback, sLogFile );
//    
//    xmpFile.CloseFile();
//}
//
//void ofApp::loadXMP(string path){
//    
//    ofLogVerbose() << "Attempting to load XMP from: " << path;
//    
//    try {
//        // Options to open the file with - read only and use a file handler
//        XMP_OptionBits opts = kXMPFiles_OpenForRead | kXMPFiles_OpenUseSmartHandler;
//        
//        bool ok;
//        
//        SXMPMeta::Initialize();
//        
//        SXMPFiles myFile;
//        std::string status = "";
//        
//        // First we try and open the file
//        ok = myFile.OpenFile(path, kXMP_UnknownFile, opts);
//        if (!ok) {
//            status += "No smart handler available for " + path + "\n";
//            status += "Trying packet scanning.\n";
//            
//            // Now try using packet scanning
//            opts = kXMPFiles_OpenForRead | kXMPFiles_OpenUsePacketScanning;
//            ok = myFile.OpenFile(path, kXMP_UnknownFile, opts);
//        }
//        
//        // If the file is open then read the metadata
//        if (ok) {
//            ofLogVerbose() << status;
//            ofLogVerbose() << path << " is opened successfully";
//            
//            // Create the xmp object and get the xmp data
//            SXMPMeta meta;
//            if (myFile.GetXMP(&meta, NULL, NULL)) {
//                cout << "yup";
//            } else {
//                cout << "nah";
//            }
//            
//            //            string labelValue = "";
//            //            string labelPath = "Label";
//            //            meta.GetProperty(kXMP_NS_XMP, labelPath.c_str(), &labelValue, NULL);
//            //            cout << labelValue;
//            
//            //            meta.DumpObject(dumpXMPObject, NULL);
//            
//            SXMPIterator iter(meta, kXMP_NS_RDF);
//            string schemaNS="", propPath="", propVal="";
//            while(iter.Next(&schemaNS, &propPath, &propVal)){
//                cout << propPath << " = " << propVal << endl;
//            }
//            
//        } else {
//            ofLogError() << "Unable to open " << path;
//        }
//        
//        myFile.CloseFile();
//        
//    } catch(XMP_Error & e) {
//        ofLogError() << "ERROR: " << e.GetErrMsg();
//    }
//}