#include "tweenApp.h"

void tweenApp::setup()
{
    // Set openFrameworks application settings
    ofSetFrameRate(60.0f);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    
    // Define component colors.
    bgColor = ofColor(0);
    shapeJointStrokeColor = ofColor(255,255,0,150);
    shapeJointFillColor = ofColor(0,255,255,100);
    shapeStrokeColor = ofColor(255,255,255,40);
    shapeFillColor = ofColor(255,255,255,20);
    
    // Other parameters...
    shapeJointRadius = 15.0f;
    shapeJointLineWidth = 1.5f;
    shapeLineWidth = 1.0f;
    numPoints = 5;
    tweenDuration = 1000;
    bRandomShapeFill = true;
    
    // Create random points within the window.
    for ( int i=0; i<numPoints; i++ ) {
        float xPos = ofRandomuf() * (float)ofGetWidth();
        float yPos = ofRandomuf() * (float)ofGetHeight();
        shapePoints.push_back( ofPoint(xPos, yPos) );
    }
    
    // Add 2 tweens for each of the points.
    tweens.resize( shapePoints.size() * 2 );
    
    // Start all tweens
    for ( int i=0; i<tweens.size(); i++ ) {
        tweens[i].start();
    }
    
    // Trigger the keyPressed() function to get initial point locations.
    onBeat();
    
    oscReceiver.setup(12345);
}

void tweenApp::update()
{
    // Update all tweens and assign updated values to shape point positions.
    for ( int i=0; i<shapePoints.size(); i++ ) {
        if ( tweens[i*2].isRunning() ) {
            shapePoints[i].x = tweens[i*2].update();
        }
        if ( tweens[i*2+1].isRunning() ) {
            shapePoints[i].y = tweens[i*2+1].update();
        }
        
        if ( tweens[i*2+1].isCompleted() ) {
            tweens[i*2].setParameters(easingElastic, ofxTween::easeInOut, shapePoints[i].x, ofGetWidth()/2.0f, 5000+(int)ofRandom(5000), 0);
        }
        
        if ( tweens[i*2+1].isCompleted() ) {
            tweens[i*2+1].setParameters(easingElastic, ofxTween::easeInOut, shapePoints[i].y, ofGetHeight()/2.0f, 5000+(int)ofRandom(5000), 0);
        }
    }
    
    if ( bRandomShapeFill ) {
        shapeFillColor = ofColor( 0, ofRandom(255), ofRandom(255), 50 );
    }
    
    // get OSC
    while ( oscReceiver.hasWaitingMessages() ) {
        ofxOscMessage msg;
        oscReceiver.getNextMessage(&msg);
        if ( msg.getAddress() == "beat" ) {
            onBeat();
        } else if ( msg.getAddress() == "addPoint" ) {
            addPoint();
        } else if ( msg.getAddress() == "removePoint" ) {
            removePoint();
        } else if ( msg.getAddress() == "tweenDuration" ) {
            tweenDuration = msg.getArgAsInt32(0);
        } else if ( msg.getAddress() == "jointLineWidth" ) {
            shapeJointLineWidth = msg.getArgAsFloat(0);
        } else if ( msg.getAddress() == "shapeLineWidth" ) {
            shapeLineWidth = msg.getArgAsFloat(0);
        } else if ( msg.getAddress() == "toggleRandomFill" ) {
            toggleRandomFill();
        }
    }
}

void tweenApp::draw()
{
    ofBackground( bgColor );
    
    // Draw shape fill.
    ofFill();
    ofSetColor(shapeFillColor);
    ofBeginShape();
    for ( int i=0; i<shapePoints.size(); i++ ) {
        ofVertex(shapePoints[i].x, shapePoints[i].y);
    }
    ofEndShape(true);
    
    // Draw shape stroke (outline).
    ofNoFill();
    ofSetLineWidth(shapeLineWidth);
    ofSetColor(shapeStrokeColor);
    ofBeginShape();
    for ( int i=0; i<shapePoints.size(); i++ ) {
        ofVertex(shapePoints[i].x, shapePoints[i].y);
    }
    ofEndShape(true);
    
    // Draw shape joints.
    for ( int i=0; i<shapePoints.size(); i++ ) {
        // Draw joint fill.
        ofFill();
        ofSetColor(shapeJointFillColor);
        ofCircle(shapePoints[i], shapeJointRadius);
        // Draw joint stroke.
        ofNoFill();
        ofSetLineWidth(shapeJointLineWidth);
        ofSetColor( shapeJointStrokeColor );
        ofCircle(shapePoints[i], shapeJointRadius);
    }
}

void tweenApp::keyPressed(int key)
{
    if ( key == 'b' ) {
        onBeat();
    } else if ( key == ']' ) {
        addPoint();
    } else if ( key == '[' ) {
        removePoint();
    } else if ( key == 'r' ) {
        toggleRandomFill();
    }
}

void tweenApp::onBeat()
{
    // Set new positions for all shape points.
    for ( int i=0; i<shapePoints.size(); i++ ) {
        float randX = ofRandomuf()*(float)ofGetWidth();
        float randY = ofRandomuf()*(float)ofGetHeight();
        //cout << "randX: " << randX << ", randY: " << randY << endl;
        tweens[i*2].setParameters(easingElastic, ofxTween::easeOut, shapePoints[i].x, randX, tweenDuration, 0);
        tweens[i*2+1].setParameters(easingElastic, ofxTween::easeOut, shapePoints[i].y, randY, tweenDuration, 0);
    }
}

void tweenApp::addPoint()
{
    // add random point and execute onBeat
    shapePoints.push_back( ofPoint( ofRandomWidth(), ofRandomHeight() ) );
    adjustTweens();
    onBeat();
}

void tweenApp::removePoint()
{
    shapePoints.pop_back();
    adjustTweens();
    onBeat();
}

void tweenApp::adjustTweens()
{
    // clear all tweens
    tweens.clear();
    
    // Add 2 tweens for each of the points.
    tweens.resize( shapePoints.size() * 2 );
    
    // Start all tweens
    for ( int i=0; i<tweens.size(); i++ ) {
        tweens[i].start();
    }
}

void tweenApp::toggleRandomFill()
{
    bRandomShapeFill = !bRandomShapeFill;
}
