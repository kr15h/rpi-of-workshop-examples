#ifndef H_TWEEN_APP
#define H_TWEEN_APP

/*
 Application that demonstrates the use of openFrameworks addons.
 In this case we are using the ofxTween addon.
 */

#include "ofMain.h"
#include "ofxTween.h" // Addon header file include:
                      // you have to add the addon name in
                      // the addons.make file as well. In
                      // this case the addons.make file should
                      // contain a line with ofxTween in it.
#include "ofxOsc.h"

class tweenApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    void onBeat();
    void addPoint();
    void removePoint();
    void adjustTweens();
    void toggleRandomFill();
    
    // Array/vector of points that will be used to draw a shape.
    vector<ofPoint> shapePoints;
    float shapeJointRadius;
    float shapeJointLineWidth;
    float shapeLineWidth;
    int numPoints; // Amount of points that will form our shape.
    int tweenDuration;
    int centerTweenDuration;
    bool bRandomShapeFill;
    
    // Colors for different components.
    ofColor bgColor;
    ofColor shapeStrokeColor;
    ofColor shapeFillColor;
    ofColor shapeJointStrokeColor;
    ofColor shapeJointFillColor;
    
    // Tweener
    vector<ofxTween> tweens; // Two tweens for each shape point parameter.
    ofxEasingElastic easingElastic; // We will use just this easing type here.
    
    // OSC comm
    ofxOscReceiver oscReceiver;
};

#endif