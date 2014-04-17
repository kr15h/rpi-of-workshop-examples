//
//  touchButton.cpp
//  SK_iOS
//
//  Created by Krisjanis Rijnieks on 8/9/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "touchButton.h"

bool touchButton::shiftKeyDown = false;
bool touchButton::isAnyButtonTouched = false;

touchButton::touchButton()
{
	x = 0.0f;
	y = 0.0f;
	width = 50.0f;
	height = 50.0f;
	color = ofColor( 0, 255, 255, 100 );
	cornerRadius = 0.0f;
    name = "button_instance";
    
    _isBeingDragged = false;
    _isBeingTouched = false;
    selected = false;
    
    registerMouseEvents();
    registerTouchEvents();
}

touchButton::~touchButton()
{
    unregisterMouseEvents();
    unregisterTouchEvents();
}

void touchButton::setup( float _x, float _y, float _width, float _height, ofColor _color, float _cornerRadius, string _name )
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    color = _color;
    cornerRadius = _cornerRadius;
    name = _name;
}

void touchButton::draw()
{
    ofPushStyle();
        ofNoFill();
        if ( selected ) {
            ofSetColor(ofColor(255));
        } else {
            ofSetColor(color);
        }
        ofRectRounded(x-width/2.0f, y-height/2.0f, width, height, cornerRadius);
    ofPopStyle();
}

/* http://patorjk.com/software/taag/ (4max font)
 
 8b    d8  dP"Yb  88   88 .dP"Y8 888888     888888 Yb    dP 888888 88b 88 888888 .dP"Y8
 88b  d88 dP   Yb 88   88 `Ybo." 88__       88__    Yb  dP  88__   88Yb88   88   `Ybo."
 88YbdP88 Yb   dP Y8   8P o.`Y8b 88""       88""     YbdP   88""   88 Y88   88   o.`Y8b
 88 YY 88  YbodP  `YbodP' 8bodP' 888888     888888    YP    888888 88  Y8   88   8bodP'
*/

void touchButton::mousePressed( ofMouseEventArgs &e )
{
    if ( isAnyButtonTouched ) return;
    
    ofRectangle rect = ofRectangle( x-width/2.0f, y-height/2.0f, width, height );
    
    if ( rect.inside(e.x, e.y) && e.button == 0 ) { // left mouse button press
        isAnyButtonTouched = true;
        _isBeingTouched = true;
        touchPoint.x = e.x;
        touchPoint.y = e.y;
        selected = true;
    }
}

void touchButton::mouseReleased( ofMouseEventArgs &e )
{
    _isBeingTouched = false;
    isAnyButtonTouched = false;
}

void touchButton::mouseMoved( ofMouseEventArgs &e )
{
    
}

void touchButton::mouseDragged( ofMouseEventArgs &e )
{
    if ( _isBeingTouched && _isBeingDragged ) {
        x += e.x - touchPoint.x;
        y += e.y - touchPoint.y;
        touchPoint.x = e.x;
        touchPoint.y = e.y;
    }
}

void touchButton::registerMouseEvents()
{
    ofAddListener( ofEvents().mousePressed, this, &touchButton::mousePressed, OF_EVENT_ORDER_BEFORE_APP );
    ofAddListener( ofEvents().mouseReleased, this, &touchButton::mouseReleased, OF_EVENT_ORDER_BEFORE_APP );
    ofAddListener( ofEvents().mouseMoved, this, &touchButton::mouseMoved, OF_EVENT_ORDER_BEFORE_APP );
    ofAddListener( ofEvents().mouseDragged, this, &touchButton::mouseDragged, OF_EVENT_ORDER_BEFORE_APP );
}

void touchButton::unregisterMouseEvents()
{
    ofRemoveListener( ofEvents().mousePressed, this, &touchButton::mousePressed );
    ofRemoveListener( ofEvents().mouseReleased, this, &touchButton::mouseReleased );
    ofRemoveListener( ofEvents().mouseMoved, this, &touchButton::mouseMoved );
    ofRemoveListener( ofEvents().mouseDragged, this, &touchButton::mouseDragged );
}

/* http://patorjk.com/software/taag/ (4max font)
 
 888888  dP"Yb  88   88  dP""b8 88  88     888888 Yb    dP 888888 88b 88 888888 .dP"Y8
   88   dP   Yb 88   88 dP   `" 88  88     88__    Yb  dP  88__   88Yb88   88   `Ybo."
   88   Yb   dP Y8   8P Yb      888888     88""     YbdP   88""   88 Y88   88   o.`Y8b
   88    YbodP  `YbodP'  YboodP 88  88     888888    YP    888888 88  Y8   88   8bodP'
*/

void touchButton::touchDown(ofTouchEventArgs &e)
{
	ofRectangle rect = ofRectangle( x, y, width, height );

	if ( rect.inside(e.x, e.y) ) {
        cout << "touchID: " << e.id << endl;
        touchID = e.id;
        _isBeingTouched = true;
        touchPoint.x = e.x;
        touchPoint.y = e.y;
	}
}

void touchButton::touchMoved(ofTouchEventArgs &e)
{
    if ( _isBeingDragged && e.id == touchID ) {
        x += e.x - touchPoint.x;
        y += e.y - touchPoint.y;
        touchPoint.x = e.x;
        touchPoint.y = e.y;
    }
}

void touchButton::touchUp(ofTouchEventArgs &e)
{
    if ( e.id == touchID ) {
        _isBeingTouched = false;
    }
}

void touchButton::touchCancelled(ofTouchEventArgs & e)
{
    
}

void touchButton::registerTouchEvents()
{
    ofAddListener( ofEvents().touchDown, this, &touchButton::touchDown, OF_EVENT_ORDER_BEFORE_APP );
    ofAddListener( ofEvents().touchUp, this, &touchButton::touchUp, OF_EVENT_ORDER_BEFORE_APP );
    ofAddListener( ofEvents().touchMoved, this, &touchButton::touchMoved, OF_EVENT_ORDER_BEFORE_APP );
    ofAddListener( ofEvents().touchCancelled, this, &touchButton::touchCancelled, OF_EVENT_ORDER_BEFORE_APP );
}

void touchButton::unregisterTouchEvents()
{
    ofRemoveListener( ofEvents().touchDown, this, &touchButton::touchDown );
    ofRemoveListener( ofEvents().touchUp, this, &touchButton::touchUp );
    ofRemoveListener( ofEvents().touchMoved, this, &touchButton::touchMoved );
    ofRemoveListener( ofEvents().touchCancelled, this, &touchButton::touchCancelled );
}

/* http://patorjk.com/software/taag/ (4max font)
 
 8888b.  88""Yb    db     dP""b8
  8I  Yb 88__dP   dPYb   dP   `"
  8I  dY 88"Yb   dP__Yb  Yb  "88
 8888Y"  88  Yb dP""""Yb  YboodP
*/

void touchButton::startDrag()
{
    _isBeingDragged = true;
}

void touchButton::stopDrag()
{
    _isBeingDragged = false;
}

/* http://patorjk.com/software/taag/ (4max font)
 
  dP""b8 88   88 88""Yb 88""Yb 888888 88b 88 888888     .dP"Y8 888888    db    888888 888888
 dP   `" 88   88 88__dP 88__dP 88__   88Yb88   88       `Ybo."   88     dPYb     88   88__
 Yb      Y8   8P 88"Yb  88"Yb  88""   88 Y88   88       o.`Y8b   88    dP__Yb    88   88""
  YboodP `YbodP' 88  Yb 88  Yb 888888 88  Y8   88       8bodP'   88   dP""""Yb   88   888888
*/

bool touchButton::isBeingDragged()
{
    return _isBeingDragged;
}

bool touchButton::isBeingTouched()
{
    return _isBeingTouched;
}

void touchButton::keyPressed(int key)
{
    if ( selected ) {
        
        float inc;
        if ( shiftKeyDown ) inc = 10;
        else inc = 1;
        
        if ( key == OF_KEY_LEFT ) {
            x-=inc;
        } else if ( key == OF_KEY_RIGHT ) {
            x+=inc;
        } else if ( key == OF_KEY_UP ) {
            y-=inc;
        } else if ( key == OF_KEY_DOWN ) {
            y+=inc;
        }
    }
    
    if ( key == 'i' ) { // i for inside
        // keep button inside the window
        if ( x <= 0 ) x = 10;
        if ( x >= ofGetWidth() ) x = ofGetWidth() - 10;
        if ( y <= 0 ) y = 10;
        if ( y >= ofGetHeight() ) y = ofGetHeight() - 10;
    }
    
    if ( key == OF_KEY_SHIFT || key == 0 || key == OF_KEY_ALT ) {
        shiftKeyDown = true;
    }
}

void touchButton::keyReleased(int key)
{
    if ( key == OF_KEY_SHIFT || key == 0 || key == OF_KEY_ALT ) {
        shiftKeyDown = false;
    }
}
