#pragma once

#include "ofMain.h"
#include "myParticle.h"
#include "ofxMidi.h"

class testApp : public ofBaseApp, public ofxMidiListener
{
public:
	void setup();
	void update();
	void draw();
		
	void newMidiMessage(ofxMidiMessage& eventArgs);
	void checkController();
	
	int numParticles;
	bool controllerFound;
	float radiusMult, radiusMultMax;
	vector<myParticle> particles;
	ofPoint speedMult, speedMultMax;
	ofxMidiIn midiIn;
	ofxMidiMessage midiMessage;
	string controllerName;
};
