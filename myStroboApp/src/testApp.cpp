#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofSetFrameRate(60);
    
    freq = 2;
    freqMax = ofGetFrameRate();
    prevUpdateTime = ofGetElapsedTimef();
    lightOn = false;
    size = ofPoint( 400, 300 );
    
    /////
    controllerName = "RPi Control";
    controllerFound = false;
    
    
    midiIn.setVerbose(true);
    midiIn.listPorts();
    midiIn.ignoreTypes(false, false, false);
    midiIn.addListener(this);
    
    if ( midiIn.getNumPorts() > 0 ) {
        for ( int i = 0; i < midiIn.getNumPorts(); i++ ){
            if ( midiIn.getPortName(i).substr( 0,controllerName.length() ) == controllerName ) {
                controllerFound = true;
                midiIn.openPort( midiIn.getPortName(i) );
                cout << "controller found: " << midiIn.getPortName(i) << endl;
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::update()
{
    if ( midiMessage.control == 1 ) {
        freq = midiMessage.value / 127.0f * freqMax;
    }
    
    if ( midiMessage.control == 2 ) {
        size.x = midiMessage.value / 127.0f * ofGetWidth();
    }
    
    if ( midiMessage.control == 3 ) {
        size.y = midiMessage.value / 127.0f * ofGetHeight();
    }
    
    
    float frameDuration = 1.0f / freq;
    float diffTime = ofGetElapsedTimef() - prevUpdateTime;
    if ( diffTime >= frameDuration ) {
        triggerStrobe();
        prevUpdateTime = ofGetElapsedTimef();
    }
    
    checkController();
}

//--------------------------------------------------------------
void testApp::draw()
{
    ofBackground(0, 0, 0);
    
    if ( lightOn == true ) {
        ofSetColor(255, 255, 255);
    } else {
        ofSetColor(0, 0, 0);
    }
    
    ofRect((ofGetWidth()-size.x)/2.0f, (ofGetHeight()-size.y)/2.0f, size.x, size.y);
}

void testApp::triggerStrobe()
{
    lightOn = !lightOn;
}

void testApp::newMidiMessage(ofxMidiMessage& msg)
{
    midiMessage = msg;
}

// automatically check if the MIDI controller is connected or not
void testApp::checkController()
{
    if ( controllerFound == false ) {
        if ( midiIn.getNumPorts() > 0 ) {
            for ( int i = 0; i < midiIn.getNumPorts(); i++ ){
                if ( midiIn.getPortName(i).substr( 0,controllerName.length() ) == controllerName ) {
                    controllerFound = true;
                    midiIn.openPort( midiIn.getPortName(i) );
                    cout << "controller found: " << midiIn.getPortName(i) << endl;
                }
            }
        }
    } else {
        bool found = false;
        
        if ( midiIn.getNumPorts() ) {
            for ( int i = 0; i < midiIn.getNumPorts(); i++ ) {
                if ( midiIn.getPortName(i).substr( 0,controllerName.length() ) == controllerName ) {
                    found = true;
                    break;
                }
            }
        }
        
        if ( found == false ) {
            midiIn.closePort();
            controllerFound = false;
        }
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}