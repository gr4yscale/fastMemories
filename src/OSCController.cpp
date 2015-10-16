//
//  OSCController.cpp
//  fastMemories
//
//  Created by Tyler Powers on 10/8/15.
//
//

#include "OSCController.h"
#include "Config.h"

OSCController::OSCController() {
    oscReceiver.setup(config::oscReceiverPort);
    cout << "osc constructor" << endl;
}

OSCController::OSCController(int port, State state) {
    // assign state reference
}

void OSCController::update() {
    cout << "update" << endl;
    if (state.oscEnabled) {
        while (oscReceiver.hasWaitingMessages()){
            ofxOscMessage m;
            oscReceiver.getNextMessage(&m);
            
            if (m.getAddress() == "/frameChangeDelta") {
                state.frameChangeDelta = m.getArgAsFloat(0);
            }
            else if (m.getAddress() == "/pauseToggle") {
                state.paused = m.getArgAsInt32(0);
            }
            else if (m.getAddress() == "/syphonToggle") {
                state.syphonEnabled = m.getArgAsInt32(0);
            }
        }
    }

}

OSCController::~OSCController() {
    cout << "~~~~~" << endl;
}