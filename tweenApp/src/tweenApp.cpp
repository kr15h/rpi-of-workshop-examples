#include "tweenApp.h"

void tweenApp::setup()
{
    // Set openFrameworks application settings
    ofSetFrameRate(60.0f);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    
    // Define component colors.
    bgColor = ofColor(0);
    shapeJointStrokeColor = ofColor(255,255,255,150);
    shapeJointFillColor = ofColor(255,255,255,100);
    shapeStrokeColor = ofColor(255,255,255,40);
    shapeFillColor = ofColor(255,255,255,20);
    
    // Other parameters...
    shapeJointRadius = 15.0f;
    numPoints = 5;
    
    // Create 3 random points within the window.
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
    keyPressed('t');
}

void tweenApp::update()
{
    // Update all tweens and assign updated values to shape point positions.
    for ( int i=0; i<shapePoints.size(); i++ ) {
        shapePoints[i].x = tweens[i*2].update();
        shapePoints[i].y = tweens[i*2+1].update();
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
        ofSetColor( shapeJointFillColor );
        ofCircle(shapePoints[i], shapeJointRadius);
        // Draw joint stroke.
        ofNoFill();
        ofSetColor( shapeJointStrokeColor );
        ofCircle(shapePoints[i], shapeJointRadius);
    }
}

void tweenApp::keyPressed(int key)
{
    if ( key == 't' ) {
        // Set new positions for all shape points.
        for ( int i=0; i<shapePoints.size(); i++ ) {
            float randX = ofRandomuf()*(float)ofGetWidth();
            float randY = ofRandomuf()*(float)ofGetHeight();
            cout << "randX: " << randX << ", randY: " << randY << endl;
            tweens[i*2].setParameters(easingElastic, ofxTween::easeOut, shapePoints[i].x, randX, 500, 0);
            tweens[i*2+1].setParameters(easingElastic, ofxTween::easeOut, shapePoints[i].y, randY, 500, 0);
        }
    }
}