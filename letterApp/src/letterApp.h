#ifndef H_LETTER_APP
#define H_LETTER_APP

#include "ofMain.h"

class letterApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
    void mousePressed(int x, int y, int button);
    void keyPressed(int key);
    
    // These functions are here to do something on beat.
    // Now you can simulate beat by pressing the 'b' letter.
    // You can disable that or change the letter in the keyPressed() method definition.
    void onBeat();
    
    // This is called on each update() loop.
    // It makes the offsets ease out to 0.
    void onBeatUpdate();
    
    ofImage guideImage; // Container for object guide image
    bool bDrawGuideImage; // Do we need to draw the guide image?
    bool bConstructMode; // Enable this to add points by clicking on the screen,
                         // press p to get the saved locations
    
    vector<ofPoint> letterVertices; // Store joints here
    vector<ofPoint> letterVerticesOffsets; // Store the offsets of the joints here
    
    // Element colors
    ofColor connectLineColor;
    ofColor jointFillColor;
    ofColor jointStrokeColor;
    
    // Other properties
    float jointRadius;
    float maxVertexOffset;
    float vertexOffsetEasing;
};

#endif