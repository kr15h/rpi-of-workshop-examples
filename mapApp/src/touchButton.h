//
//  touchButton.h
//  SK_iOS
//
//  Created by Krisjanis Rijnieks on 8/9/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef SK_iOS_touchButton_h
#define SK_iOS_touchButton_h

#include "ofMain.h"
#include "ofEvents.h"

class touchButton
{
public:
    static bool shiftKeyDown;
    static bool isAnyButtonTouched;
    
	touchButton();
    ~touchButton();
	
    void setup( float _x, float _y, float _width, float _height, ofColor _color, float _cornerRadius, string _name );
    
	void draw();
    
    void mouseMoved( ofMouseEventArgs &e );
    void mouseDragged( ofMouseEventArgs &e );
    void mousePressed( ofMouseEventArgs &e );
    void mouseReleased( ofMouseEventArgs &e );
    void registerMouseEvents();
    void unregisterMouseEvents();
    
	void touchDown( ofTouchEventArgs &e );
    void touchMoved( ofTouchEventArgs &e );
    void touchUp( ofTouchEventArgs &e );
    void touchCancelled( ofTouchEventArgs &e );
    void registerTouchEvents();
    void unregisterTouchEvents();
    
    void keyPressed( int key );
    void keyReleased( int key );
    
    void startDrag();
    void stopDrag();
    
    bool isBeingDragged();
	bool isBeingTouched();
    
	// events
	ofEvent<string> buttonTouched;
	
	float x;
	float y;
	float width;
	float height;
	ofColor color;
	float cornerRadius;
    string name;
    int touchID;
    
    bool selected;
    
private:
    bool _isBeingDragged;
    bool _isBeingTouched;
    ofPoint touchPoint;
    
    
};

#endif
