#include "oscApp.h"

void oscApp::setup()
{
    p1 = ofPoint(50, 50);
    p2 = ofPoint(150, 200);
    p3 = ofPoint(300, 150);

    r1 = 50;
    r2 = 100;
    r3 = 75;

    system ("pd -nogui /home/pi/openFrameworks/apps/myApps/oscApp/soundApp.pd &");
    oscReceiver.setup(12345);

    ofBackground(0);
}

void oscApp::update()
{
    r1 -= 2;
    r2 -= 1;
    r3 -= 1.5;

    if ( r1 < 0 ) r1 = 0;
    if ( r2 < 0 ) r2 = 0;
    if ( r3 < 0 ) r3 = 0;

    while ( oscReceiver.hasWaitingMessages() ) {
    	ofxOscMessage msg;
    	oscReceiver.getNextMessage( &msg );
    	cout << "OSC: " << msg.getAddress() << endl;
    	if ( msg.getAddress() == "/sound1" ) {
    		r1 = 50;
    	} else if ( msg.getAddress() == "/sound2" ) {
    		r2 = 100;
    	} else if ( msg.getAddress() == "/sound3" ) {
    		r3 = 75;
    	}	
    }
}

void oscApp::draw()
{
    ofCircle(p1.x, p1.y, r1);
    ofCircle(p2.x, p2.y, r2);
    ofCircle(p3.x, p3.y, r3);
}

void oscApp::exit()
{
    system ("killall pd");
}