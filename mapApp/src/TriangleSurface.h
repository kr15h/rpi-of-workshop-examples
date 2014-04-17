//
//  TriangleSurface.h
//  demoDayMapping
//
//  Created by Krisjanis Rijnieks on 16/12/13.
//
//

#ifndef __demoDayMapping__TriangleSurface__
#define __demoDayMapping__TriangleSurface__

#include "ofMain.h"
#include "touchButton.h"

class TriangleSurface
{
public:
    static float offset;
    
    TriangleSurface();
    
    void setup( ofTexture* texture );
    void update();
    void draw();
    
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    touchButton b1, b2, b3;
    touchButton m1, m2, m3; // mapping buttons
    ofMesh mesh;
    ofTexture* texture;
    
    void setOffsetX( float off );
    void setOffsetY( float off );
    
    enum Mode{
        Surface,
        Mapping,
        Presentation
    } mode;
    
    void setMode( Mode m );
    
    void setSurface( float x1, float y1, float x2, float y2, float x3, float y3 );
    void setMapping( float x1, float y1, float x2, float y2, float x3, float y3 );
    
    void deselectAll();
    
private:
    bool inited;
    float offsetX;
    float offsetY;
    
};

#endif /* defined(__demoDayMapping__TriangleSurface__) */
