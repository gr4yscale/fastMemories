//
//  OSCController.h
//  fastMemories
//
//  Created by Tyler Powers on 10/8/15.
//
//

#ifndef __fastMemories__OSCController__
#define __fastMemories__OSCController__

#include <stdio.h>
#include "ofxOsc.h"
#include "State.h"

class OSCController {

    ofxOscReceiver oscReceiver;
    State state;
    
    public:
        OSCController();
        ~OSCController();
        OSCController(int, State);
        
        void update();
};

#endif
