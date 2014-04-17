//
//  TriangleSurface.cpp
//  demoDayMapping
//
//  Created by Krisjanis Rijnieks on 16/12/13.
//
//

#include "TriangleSurface.h"

TriangleSurface::TriangleSurface()
{
    inited = false;
    mode = Presentation;
    offsetX = 0;
    offsetY = 0;
}

void TriangleSurface::setup( ofTexture* tex )
{
    texture = tex;
    offset+=40;
    
    b1.setup( offset, offset, 20, 20, ofColor(135,255,0), 0, "button1" );
    b2.setup( 100+offset, offset, 20, 20, ofColor(135,255,0), 0, "button2" );
    b3.setup( 100+offset, 100+offset, 20, 20, ofColor(135,255,0), 0, "button3" );
    b1.unregisterMouseEvents();
    b1.unregisterTouchEvents();
    b2.unregisterMouseEvents();
    b2.unregisterTouchEvents();
    b3.unregisterMouseEvents();
    b3.unregisterTouchEvents();
    
    m1.setup( offset, offset, 20, 20, ofColor(255,255,0), 0, "mapping1" );
    m2.setup( 100+offset, offset, 20, 20, ofColor(255,255,0), 0, "mapping2" );
    m3.setup( 100+offset, 100+offset, 20, 20, ofColor(255,255,0), 0, "mapping3" );
    m1.unregisterMouseEvents();
    m1.unregisterTouchEvents();
    m2.unregisterMouseEvents();
    m2.unregisterTouchEvents();
    m3.unregisterMouseEvents();
    m3.unregisterTouchEvents();
    
    mesh.addVertex( ofVec3f(m1.x,m1.y,0) );
    mesh.addVertex( ofVec3f(m2.x,m2.y,0) );
    mesh.addVertex( ofVec3f(m3.x,m3.y,0) );
    
    float tw = texture->getWidth();
    float th = texture->getHeight();
    mesh.addTexCoord( ofVec2f(b1.x/tw, b1.y/th) );
    mesh.addTexCoord( ofVec2f(b2.x/tw, b2.y/th) );
    mesh.addTexCoord( ofVec2f(b3.x/tw, b3.y/th) );
    
    inited = true;
}

void TriangleSurface::update()
{
    if ( !inited ) return;
    
    if ( mode == Surface ) {
        if ( b1.isBeingTouched() ) {
            b1.startDrag();
        } else {
            b1.stopDrag();
        }
        
        if ( b2.isBeingTouched() ) {
            b2.startDrag();
        } else {
            b2.stopDrag();
        }
        
        if ( b3.isBeingTouched() ) {
            b3.startDrag();
        } else {
            b3.stopDrag();
        }
        
        if ( b1.isBeingDragged() || b1.selected ) {
            mesh.setTexCoord(0, ofVec2f(b1.x/texture->getWidth(), b1.y/texture->getHeight()) );
        } else if ( b2.isBeingDragged() || b2.selected ) {
            mesh.setTexCoord(1, ofVec2f(b2.x/texture->getWidth(), b2.y/texture->getHeight()) );
        } else if ( b3.isBeingDragged() || b3.selected ) {
            mesh.setTexCoord(2, ofVec2f(b3.x/texture->getWidth(), b3.y/texture->getHeight()) );
        }
        
    } else if ( mode == Mapping ) {
        if ( m1.isBeingTouched() ) {
            m1.startDrag();
        } else {
            m1.stopDrag();
        }
        
        if ( m2.isBeingTouched() ) {
            m2.startDrag();
        } else {
            m2.stopDrag();
        }
        
        if ( m3.isBeingTouched() ) {
            m3.startDrag();
        } else {
            m3.stopDrag();
        }
        
        if ( m1.isBeingDragged() || m1.selected ) {
            mesh.setVertex(0, ofVec3f(m1.x,m1.y,0));
        } else if ( m2.isBeingDragged() || m2.selected ) {
            mesh.setVertex(1, ofVec3f(m2.x,m2.y,0));
        } else if ( m3.isBeingDragged() || m3.selected ) {
            mesh.setVertex(2, ofVec3f(m3.x,m3.y,0));
        }
    }
}

void TriangleSurface::draw()
{
    if ( !inited ) return;
    
    if ( mode == Surface ) {
        // draw surface
        ofPushStyle();
        ofSetColor(135, 255, 0, 100);
        ofTriangle(b1.x, b1.y, b2.x, b2.y, b3.x, b3.y);
        ofPopStyle();
        
        b1.draw();
        b2.draw();
        b3.draw();
    } else if ( mode == Presentation || mode == Mapping ) {
        texture->bind();
        mesh.draw();
        texture->unbind();
        
        if ( mode == Mapping ) {
            m1.draw();
            m2.draw();
            m3.draw();
        }
    }
}

void TriangleSurface::mouseMoved(int x, int y)
{
    ofMouseEventArgs a; a.x = x; a.y = y;
    
    if ( mode == Surface ) {
        b1.mouseMoved(a);
        b2.mouseMoved(a);
        b3.mouseMoved(a);
    } else if ( mode == Mapping ) {
        m1.mouseMoved(a);
        m2.mouseMoved(a);
        m3.mouseMoved(a);
    }
}

void TriangleSurface::mouseDragged(int x, int y, int button)
{
    ofMouseEventArgs a; a.x = x; a.y = y; a.button = button;
    
    if ( mode == Surface ) {
        b1.mouseDragged(a);
        b2.mouseDragged(a);
        b3.mouseDragged(a);
    } else if ( mode == Mapping ) {
        m1.mouseDragged(a);
        m2.mouseDragged(a);
        m3.mouseDragged(a);
    }
}

void TriangleSurface::mousePressed(int x, int y, int button)
{
    ofMouseEventArgs a; a.x = x; a.y = y; a.button = button;
    
    deselectAll();
    
    if ( mode == Surface ) {
        b1.mousePressed(a);
        b2.mousePressed(a);
        b3.mousePressed(a);
    } else if ( mode == Mapping ) {
        m1.mousePressed(a);
        m2.mousePressed(a);
        m3.mousePressed(a);
    }
}

void TriangleSurface::mouseReleased(int x, int y, int button)
{
    ofMouseEventArgs a; a.x = x; a.y = y; a.button = button;
    
    if ( mode == Surface ) {
        b1.mouseReleased(a);
        b2.mouseReleased(a);
        b3.mouseReleased(a);
    } else if ( mode == Mapping ) {
        m1.mouseReleased(a);
        m2.mouseReleased(a);
        m3.mouseReleased(a);
    }
}

void TriangleSurface::setMode( Mode m )
{
    mode = m;
}

void TriangleSurface::setSurface( float x1, float y1, float x2, float y2, float x3, float y3 )
{
    b1.x = x1; b1.y = y1;
    b2.x = x2; b2.y = y2;
    b3.x = x3; b3.y = y3;
    
    mesh.setTexCoord(0, ofVec2f((b1.x+offsetX)/texture->getWidth(), (b1.y+offsetY)/texture->getHeight()) );
    mesh.setTexCoord(1, ofVec2f((b2.x+offsetX)/texture->getWidth(), (b2.y+offsetY)/texture->getHeight()) );
    mesh.setTexCoord(2, ofVec2f((b3.x+offsetX)/texture->getWidth(), (b3.y+offsetY)/texture->getHeight()) );
}

void TriangleSurface::setMapping( float x1, float y1, float x2, float y2, float x3, float y3 )
{
    m1.x = x1; m1.y = y1;
    m2.x = x2; m2.y = y2;
    m3.x = x3; m3.y = y3;
    
    mesh.setVertex(0, ofVec3f(m1.x,m1.y,0));
    mesh.setVertex(1, ofVec3f(m2.x,m2.y,0));
    mesh.setVertex(2, ofVec3f(m3.x,m3.y,0));
}

void TriangleSurface::keyPressed( int key )
{
    b1.keyPressed(key);
    b2.keyPressed(key);
    b3.keyPressed(key);
    
    m1.keyPressed(key);
    m2.keyPressed(key);
    m3.keyPressed(key);
}

void TriangleSurface::keyReleased(int key)
{
    b1.keyReleased(key);
    b2.keyReleased(key);
    b3.keyReleased(key);
    
    m1.keyReleased(key);
    m2.keyReleased(key);
    m3.keyReleased(key);
}

void TriangleSurface::deselectAll()
{
    b1.selected = false;
    b2.selected = false;
    b3.selected = false;
    
    m1.selected = false;
    m2.selected = false;
    m3.selected = false;
}

void TriangleSurface::setOffsetX(float off)
{
    offsetX = off;
    setSurface(b1.x, b1.y, b2.x, b2.y, b3.x, b3.y);
}

void TriangleSurface::setOffsetY(float off)
{
    offsetY = off;
    setSurface(b1.x, b1.y, b2.x, b2.y, b3.x, b3.y);
}