#ifndef H_OSC_APP
#define H_OSC_APP

#include "ofMain.h"
#include "ofxOsc.h"
#include <stdlib.h>

class oscApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	void exit();

	ofPoint p1, p2, p3;
	float r1, r2, r3;
	ofxOscReceiver oscReceiver;
};

#endif
