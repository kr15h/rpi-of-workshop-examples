#pragma once

#include "ofMain.h"
#include "TriangleSurface.h"
#include "ofxXmlSettings.h"
#include "ofxMidi.h"
#include "touchButton.h"

#define XML_SETTINGS_FILENAME "settings.xml"

class testApp : public ofBaseApp, public ofxMidiListener
{
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed( int key );
    void keyReleased( int key );
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void gotMessage(ofMessage msg);
    
    int stageWidth;
    int stageHeight;
    
    ofImage image;
    ofMesh mesh;
    TriangleSurface::Mode mode;
    float offsetX;
    float offsetY;
    float oscSpeedX;
    float oscSpeedY;
    int oscMultX;
    int oscMultY;
    
    vector<TriangleSurface> surfaces;
    
    ofxXmlSettings xml;
    
    
    void newMidiMessage(ofxMidiMessage& eventArgs);
    ofxMidiIn midiIn;
    ofxMidiMessage midiMessage;
    std::string controllerName;
    bool controllerFound;
    void checkController();
    
private:
    bool inited;
};
