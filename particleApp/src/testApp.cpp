#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    numParticles = 100;
    speedMult = ofPoint(1.0f,1.0f,1.0f);
    speedMultMax = ofPoint(100.0f,100.0f,100.0f);
    radiusMult = 1.0f;
    radiusMultMax = 10.0f;
    
    for ( int i = 0; i < numParticles; i++ ) {
        myParticle particle;
        particle.position = ofPoint( ofGetWidth()/2.0f, ofGetHeight()/2.0f );
        particle.radius = 10.0 + ofRandom(50.0f);
        particle.speed = ofPoint( ofRandom(1.0f)-0.5f, ofRandom(1.0f)-0.5f );
        particles.push_back(particle);
    }
    
    controllerName = "RPi Control";
    controllerFound = false;
    
    midiIn.listPorts();
    midiIn.setVerbose(true);
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
    
    ofSetCircleResolution(5);
}

//--------------------------------------------------------------
void testApp::update()
{
    for ( int i = 0; i < numParticles; i++ ) {
        particles[i].position += particles[i].speed * speedMult;
        
        if ( particles[i].position.x> ofGetWidth() + particles[i].radius*radiusMult ) {
            particles[i].position.x = -particles[i].radius*radiusMult;
        }
        
        if ( particles[i].position.y > ofGetHeight() + particles[i].radius*radiusMult ) {
            particles[i].position.y = -particles[i].radius*radiusMult;
        }
        
        if ( particles[i].position.x < - particles[i].radius*radiusMult ) {
            particles[i].position.x = ofGetWidth() + particles[i].radius*radiusMult;
        }
        
        if ( particles[i].position.y < - particles[i].radius*radiusMult ) {
            particles[i].position.y = ofGetHeight() + particles[i].radius*radiusMult;
        }
    }
    
    //particle.position.x += particle.speed.x;
    //particle.position.y += particle.speed.y
    
    //cout << midiMessage.control << endl;
    
    if ( midiMessage.control == 1 ) {
        speedMult.x = midiMessage.value / 127.0f * speedMultMax.x;
    }
    
    if ( midiMessage.control == 2 ) {
        speedMult.y = midiMessage.value / 127.0f * speedMultMax.y;
    }
    
    if ( midiMessage.control == 3 ) {
        ofSetCircleResolution( 3+midiMessage.value );
    }
    
    if ( midiMessage.control == 4 ) {
        radiusMult = midiMessage.value / 127.0f * radiusMultMax;
    }
    
    checkController();
}

//--------------------------------------------------------------
void testApp::draw()
{
    ofBackground(0, 0, 0);
    
    for ( int i = 0; i < numParticles; i++ ) {
        ofCircle(particles[i].position.x, particles[i].position.y, particles[i].radius*radiusMult);
    }
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
    int particleId = ofRandom( numParticles-1 );
    particles[particleId].radius = 10.0 + ofRandom(50.0f);
    particles[particleId].speed = ofPoint( ofRandom(1.0f)-0.5f, ofRandom(1.0f)-0.5f );
    
    
    //for ( int i = 0; i < numParticles; i++ ) {
        
    //}
    
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