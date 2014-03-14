#ifndef H_STROBO_APP
#define H_STROBO_APP

#include "ofMain.h"
#include "ofxMidi.h"

class stroboApp : public ofBaseApp, public ofxMidiListener
{
public:
	void setup();
	void update();
	void draw();
		
	void newMidiMessage(ofxMidiMessage& eventArgs);
	void checkController();
	void triggerStrobe();
	
	bool controllerFound;
	bool lightOn;
	
	float freq, freqMax;
	float prevUpdateTime;

	ofPoint size;
	ofxMidiIn midiIn;
	ofxMidiMessage midiMessage;
	std::string controllerName;
};

#endif