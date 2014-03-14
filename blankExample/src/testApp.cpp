#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    //
    ofSetFrameRate( 60 );
    
    pos.x = 0.5f; // 0 - 1
    pos.y = 0.5f;
    posPix.x = pos.x * ofGetWidth();
    posPix.y = pos.y * ofGetHeight();
    
    radius = ofGetWidth() / 10.0f;
    
    size.x = ofGetWidth() / 3.0f;
    size.y = 0.1f;
    
    onOffSwitch = true;
    
    if ( onOffSwitch == true ) {
        col = ofColor( 255, 255, 255 );
    } else {
        col = ofColor( 0, 0, 0 );
    }
    
    midiIn.listPorts(); // via instance
    midiIn.openPort(0);
    midiIn.ignoreTypes(false, false, false);
    midiIn.addListener(this);
    midiIn.setVerbose(true);
}

//--------------------------------------------------------------
void testApp::update(){
    
    pos.x += 0.01f;
    
    size.x = ofGetWidth() / 3.0f;
    //size.y = ofGetHeight() / 3.0f;
    
    posPix.x = pos.x * ofGetWidth();
    posPix.y = pos.y * ofGetHeight();
    
    if ( posPix.x > ofGetWidth() + size.x ) {
        pos.x = -size.x/ofGetWidth();
    }
    
    if ( midiMessage.control == 2 ) {
        size.y = midiMessage.value / 127.0f;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    //ofCircle(pos, radius);
    //ofRect(pos.x-size.x/2.0f, pos.y-size.y/2.0f, size.x, size.y);
    
    ofSetColor( col );
    ofRect( posPix.x-size.x/2.0f, posPix.y-size.y*ofGetHeight()/2.0f, size.x, size.y*ofGetHeight() );
    
    stringstream text;
    text << "control: " << midiMessage.control << " yes no";
	ofDrawBitmapString(text.str(), 20, 144);
	text.str(""); // clear
	
	text << "value: " << midiMessage.value << " extra text";
	ofDrawBitmapString(text.str(), 20, 192);
	text.str(""); // clear
}

//--------------------------------------------------------------
void testApp::newMidiMessage(ofxMidiMessage& msg) {
    
	// make a copy of the latest message
	midiMessage = msg;
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    cout << key << endl;
    
    if ( key == 97 ) {
        pos.x = 0.5f;
    }
    
    if ( key == 'w' ) {
        col = ofColor( 255, 255, 255 );
    }
    
    if ( key == 'b' ) {
        col = ofColor( 0, 0, 0 );
    }
    
    if ( key == 'u' ) {
        onOffSwitch = !onOffSwitch;
        if ( onOffSwitch == true ) {
            col = ofColor( 255, 255, 255 );
        } else {
            col = ofColor( 0, 0, 0 );
        }
    }
    
    if ( key == 357 ) { // up
        size.y += 0.01f;
    }
    
    if ( key == 359 ) {
        size.y -= 0.01f;
    }
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
void testApp::mousePressed(int x, int y, int button){

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