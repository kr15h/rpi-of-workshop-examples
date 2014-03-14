#pragma once

#include "ofMain.h"
#include "myParticle.h"
#include "ofxMidi.h"

class testApp : public ofBaseApp, public ofxMidiListener{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    int numParticles;
    vector<myParticle> particles;
    ofPoint speedMult, speedMultMax;
    float radiusMult, radiusMultMax;
    
    ofxMidiIn midiIn;
    ofxMidiMessage midiMessage;
    void newMidiMessage(ofxMidiMessage& eventArgs);
    
    std::string controllerName;
    bool controllerFound;
    
    void checkController();
};
