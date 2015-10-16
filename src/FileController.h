//
//  FileController.h
//  fastMemories
//
//  Created by Tyler Powers on 10/8/15.
//
//

#ifndef __fastMemories__FileController__
#define __fastMemories__FileController__

#include <stdio.h>
#include "State.h"
#include  "Config.h"



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


class FileController {
   
    public:
        FileController();
        void loadFilePaths();
        void loadDirectory(ofDirectory dir);
        vector<string> fileNames;
};






#endif
