#ifndef H_STATE_MACHINE_APP
#define H_STATE_MACHINE_APP

#include "ofMain.h"

class stateMachineApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void keyPressed( int key );
    void mousePressed( int x, int y, int button );
    
};

#endif