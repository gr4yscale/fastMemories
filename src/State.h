//
//  State.h
//  fastMemories
//
//  Created by Tyler Powers on 10/8/15.
//
//

#ifndef fastMemories_State_h
#define fastMemories_State_h

struct State
{
    bool paused = 0;
    bool syphonEnabled = 0;
    bool oscEnabled = 1;
    bool updatingFrameRate = 0;
    float frameChangeDelta;
    double fileIndex = 0;
};

#endif
