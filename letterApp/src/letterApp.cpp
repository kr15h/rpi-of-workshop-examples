#include "letterApp.h"

void letterApp::setup()
{
    ofSetFrameRate(60.0f);
    
    // Load guide image.
    guideImage.loadImage("a.png");
    
    // Set modes
    bDrawGuideImage = false;
    bConstructMode = false;
    
    // Fill letter vertices vector with points.
    letterVertices.push_back( ofPoint(0.46, 0.133333) );
    letterVertices.push_back( ofPoint(0.5425, 0.133333) );
    letterVertices.push_back( ofPoint(0.745, 0.87) );
    letterVertices.push_back( ofPoint(0.6325, 0.871667) );
    letterVertices.push_back( ofPoint(0.6, 0.74) );
    letterVertices.push_back( ofPoint(0.40125, 0.741667) );
    letterVertices.push_back( ofPoint(0.36625, 0.868333) );
    letterVertices.push_back( ofPoint(0.2575, 0.868333) );
    letterVertices.push_back( ofPoint(0.4325, 0.618333) );
    letterVertices.push_back( ofPoint(0.5025, 0.351667) );
    letterVertices.push_back( ofPoint(0.5725, 0.621667) );
    
    // Add the same amount of values to the vertex offset vector
    letterVerticesOffsets.resize( letterVertices.size() );
    
    // Set colors for the drawable components
    connectLineColor = ofColor(255, 255, 255, 100);
    jointFillColor = ofColor(255, 255, 255, 150);
    jointStrokeColor = ofColor(255, 255, 255, 200);
    
    // Set joint radius and other properties.
    jointRadius = 10.0f;
    maxVertexOffset = 50.0f;
    vertexOffsetEasing = 0.95f;
    
    // Enable alpha blending as we are using the alpha component in the colors.
    ofEnableAlphaBlending();
}

void letterApp::update()
{
    onBeatUpdate();
}

void letterApp::draw()
{
    // draw background
    ofBackground(0);
    
    // draw guide image if the boolean variable is set to true
    if ( bDrawGuideImage ) {
        glColor4f(1, 1, 1, 0.5f);
        guideImage.draw(0, 0, ofGetWidth(), ofGetHeight());
        glColor4f(1, 1, 1, 1);
    }
    
    // Draw lines between letter vertices.
    // One line from each vertex to each of the other vertices.
    // Set line color.
    ofSetColor( connectLineColor );
    for ( int i=0; i<letterVertices.size(); i++ ) {
        // Get start point.
        ofPoint& startPoint = letterVertices[i];
        for ( int j=0; j<letterVertices.size(); j++ ) {
            // Assign and draw end point only if the end point is not current point.
            if ( i != j ) {
                ofPoint& endPoint = letterVertices[j];
                // Draw the line.
                ofLine( startPoint.x * (float)ofGetWidth() + letterVerticesOffsets[i].x,
                       startPoint.y * (float)ofGetHeight() + letterVerticesOffsets[i].y,
                       endPoint.x * (float)ofGetWidth() + letterVerticesOffsets[j].x,
                       endPoint.y * (float)ofGetHeight() + letterVerticesOffsets[j].y );
            }
        }
    }
    
    // Draw joints.
    for ( int i=0; i<letterVertices.size(); i++ ) {
        // Draw the inside of the joint.
        ofSetColor( jointFillColor );
        ofCircle( letterVertices[i].x * (float)ofGetWidth() + letterVerticesOffsets[i].x,
                 letterVertices[i].y * (float)ofGetHeight() + letterVerticesOffsets[i].y,
                 jointRadius);
        // Draw joint stroke (outline).
        ofNoFill(); // Set the renderer to outline-only mode.
        ofSetColor( jointStrokeColor );
        ofCircle( letterVertices[i].x * (float)ofGetWidth() + letterVerticesOffsets[i].x,
                 letterVertices[i].y * (float)ofGetHeight() + letterVerticesOffsets[i].y,
                 jointRadius);
        ofFill(); // Reset the renderer to fill-only mode as it was before.
    }
}

void letterApp::mousePressed(int x,int y,int button)
{
    if ( bConstructMode ) {
        // add point on click
        float relX = (float)x / (float)ofGetWidth();
        float relY = (float)y / (float)ofGetHeight();
        letterVertices.push_back( ofPoint(relX, relY) );
        letterVerticesOffsets.push_back( ofPoint(0,0) );
    }
}

void letterApp::keyPressed(int key)
{
    if ( key == 'p' ) {
        if ( bConstructMode ) {
            // print all positions from the vertices vector
            for ( int i=0; i<letterVertices.size(); i++ ) {
                // the output is adjusted for easy copy/paste to the setup() part
                cout << "letterVertices.push_back( ofPoint(" << letterVertices[i].x << ", " << letterVertices[i].y << ") );" << endl;
            }
        }
    } else if ( key == OF_KEY_BACKSPACE ) {
        if ( bConstructMode ) {
            // remove last point from the vertices vector when backspace is pressed
            if ( letterVertices.size() >= 1 ) {
                letterVertices.pop_back();
                letterVerticesOffsets.pop_back();
            } else {
                // notify user that there are no points left
                cout << "No points left." << endl;
            }
        }
    } else if ( key == 'b' ) {
        // Simulate beat by calling the onBeat() function
        onBeat();
    }
}

void letterApp::onBeat()
{
    // Calcullate random offsets for each vertex in the letter vertex vector
    for ( int i=0; i<letterVerticesOffsets.size(); i++ ) {
        letterVerticesOffsets[i].x = ofRandomf() * maxVertexOffset;
        letterVerticesOffsets[i].y = ofRandomf() * maxVertexOffset;
    }
}

void letterApp::onBeatUpdate()
{
    // Decrease vertex offsets
    for ( int i=0; i<letterVerticesOffsets.size(); i++ ) {
        // Decrease the vertex x and y offset by multiplying them
        // with the same easing value.
        letterVerticesOffsets[i] *= vertexOffsetEasing;
    }
}