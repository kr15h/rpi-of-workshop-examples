#include "testApp.h"

float TriangleSurface::offset = 0;

//--------------------------------------------------------------
void testApp::setup()
{
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableNormalizedTexCoords();
    
    stageWidth = ofGetWidth();
    stageHeight = ofGetHeight();
    
    image.loadImage("image.jpg");
    
    if ( xml.load( XML_SETTINGS_FILENAME ) ) {
        xml.pushTag("surfaces");
        
        unsigned numSurfaces = xml.getNumTags("surface");
        for ( unsigned i = 0; i < numSurfaces; i++ ) {
            xml.pushTag("surface", i);
            
            surfaces.push_back( TriangleSurface() );
            surfaces.back().setup( &image.getTextureReference() );
            surfaces.back().setSurface( xml.getValue("b1.x",0.0f), xml.getValue("b1.y",0.0f),
                                       xml.getValue("b2.x",0.0f), xml.getValue("b2.y",0.0f),
                                       xml.getValue("b3.x",0.0f), xml.getValue("b3.y",0.0f) );
            surfaces.back().setMapping( xml.getValue("m1.x",0.0f), xml.getValue("m1.y",0.0f),
                                       xml.getValue("m2.x",0.0f), xml.getValue("m2.y",0.0f),
                                       xml.getValue("m3.x",0.0f), xml.getValue("m3.y",0.0f) );
            
            xml.popTag();
        }
        
        xml.popTag();
    } else {
        surfaces.push_back( TriangleSurface() );
        surfaces.back().setup( &image.getTextureReference() );
    }
    
    mesh.addVertex( ofVec3f(0,0,0) );
    mesh.addVertex( ofVec3f(image.width,0,0) );
    mesh.addVertex( ofVec3f(image.width,image.height,0) );
    mesh.addVertex( ofVec3f(0,image.height,0) );
    
    mesh.addTexCoord( ofVec2f(0,0) );
    mesh.addTexCoord( ofVec2f(1,0) );
    mesh.addTexCoord( ofVec2f(1,1) );
    mesh.addTexCoord( ofVec2f(0,1) );
    
    mesh.addTriangle( 0,1,2 );
    mesh.addTriangle( 2,3,0 );
    
    mode = TriangleSurface::Presentation;
    ofHideCursor();
    
    controllerName = "nanoKONTROL2";
    controllerFound = false;
    
    midiIn.setVerbose(true);
    midiIn.listPorts();
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
    
    offsetX = 0;
    offsetY = 0;
    oscSpeedX = 0.1f;
    oscSpeedY = 0.2f;
    oscMultX = 1.0f;
    oscMultY = 1.0f;
    
    inited = true;
    
} // END: setup

//--------------------------------------------------------------
void testApp::update()
{
    for ( unsigned i = 0; i < surfaces.size(); i++ ) {
        surfaces[i].update();
    }
    
    float oscX = sinf(ofGetElapsedTimef()*oscSpeedX)*45.0f;
    float oscY = cosf(ofGetElapsedTimef()*oscSpeedY)*45.0f;
    
    for ( unsigned i = 0; i < surfaces.size(); i++ ) {
        surfaces[i].setOffsetX(offsetX+oscX);
        surfaces[i].setOffsetY(offsetY+oscY);
    }
    
    checkController();
    
    /*
    oscSpeedX += 0.01f * oscMultX;
    oscSpeedY += 0.005f * oscMultY;
    if ( oscSpeedX > 1.0f ) {
        oscSpeedX = 1.0f;
        oscMultX = -1.0f;
    }
    if ( oscSpeedY > 1.0f ) {
        oscSpeedY = 1.0f;
        oscMultY = -1.0f;
    }
    if ( oscSpeedX < 0.0f ) {
        oscSpeedX = 0.0f;
        oscMultX = 1.0f;
    }
    if ( oscSpeedY < 0.0f ) {
        oscSpeedY = 0.0f;
        oscMultY = 1.0f;
    }
    
    cout << "oscSpeedX: " << oscSpeedX << endl;
     */
} // END: update

//--------------------------------------------------------------
void testApp::draw()
{
    if (mode == TriangleSurface::Surface) {
        image.getTextureReference().bind();
        mesh.draw();
        image.getTextureReference().unbind();
    }
    
    for ( unsigned i = 0; i < surfaces.size(); i++ ) {
        surfaces[i].draw();
    }
} // END: draw

//--------------------------------------------------------------
void testApp::exit()
{
    xml.clear();
    
    xml.addTag("surfaces");
    xml.pushTag("surfaces");
    
    // loop through surfaces
    for ( unsigned i = 0; i < surfaces.size(); i++ ) {
        xml.addTag("surface");
        xml.pushTag("surface", i);
        
        xml.addTag("b1.x"); xml.setValue("b1.x", surfaces[i].b1.x);
        xml.addTag("b1.y"); xml.setValue("b1.y", surfaces[i].b1.y);
        xml.addTag("b2.x"); xml.setValue("b2.x", surfaces[i].b2.x);
        xml.addTag("b2.y"); xml.setValue("b2.y", surfaces[i].b2.y);
        xml.addTag("b3.x"); xml.setValue("b3.x", surfaces[i].b3.x);
        xml.addTag("b3.y"); xml.setValue("b3.y", surfaces[i].b3.y);
        
        xml.addTag("m1.x"); xml.setValue("m1.x", surfaces[i].m1.x);
        xml.addTag("m1.y"); xml.setValue("m1.y", surfaces[i].m1.y);
        xml.addTag("m2.x"); xml.setValue("m2.x", surfaces[i].m2.x);
        xml.addTag("m2.y"); xml.setValue("m2.y", surfaces[i].m2.y);
        xml.addTag("m3.x"); xml.setValue("m3.x", surfaces[i].m3.x);
        xml.addTag("m3.y"); xml.setValue("m3.y", surfaces[i].m3.y);
        
        xml.popTag();
    }
    
    xml.popTag();
    
    xml.save( XML_SETTINGS_FILENAME );

    
} // END: draw

void testApp::keyPressed( int key )
{
    //cout << key << endl;
    touchButton::isAnyButtonTouched = false;
    
    if ( key == '1' ) {
        mode = TriangleSurface::Surface;
        ofShowCursor();
    } else if ( key == '2' ) {
        mode = TriangleSurface::Mapping;
        ofShowCursor();
    } else if ( key == '3' ) {
        mode = TriangleSurface::Presentation;
        ofHideCursor();
    }
    
    for ( unsigned i = 0; i < surfaces.size(); i++ ) {
        surfaces[i].setMode( mode );
        surfaces[i].keyPressed(key);
    }
    
    if ( key == 'n' ) { // n for new
        surfaces.push_back( TriangleSurface() );
        surfaces.back().setup( &image.getTextureReference() );
        surfaces.back().setMode(mode);
    } else if ( key == OF_KEY_BACKSPACE ) {
        surfaces.pop_back();
    }
}

void testApp::keyReleased( int key )
{
    for ( unsigned i = 0; i < surfaces.size(); i++ ) {
        surfaces[i].keyReleased(key);
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
    for ( unsigned i = 0; i < surfaces.size(); i++ ) {
        surfaces[i].mouseMoved(x,y);
    }
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
    for ( unsigned i = 0; i < surfaces.size(); i++ ) {
        surfaces[i].mouseDragged(x,y,button);
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
    for ( unsigned i = 0; i < surfaces.size(); i++ ) {
        surfaces[i].mousePressed(x,y,button);
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
    for ( unsigned i = 0; i < surfaces.size(); i++ ) {
        surfaces[i].mouseReleased(x,y,button);
    }
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{
    
}

void testApp::newMidiMessage(ofxMidiMessage& msg)
{
    midiMessage = msg;
    cout << msg.control << ", " << msg.value << endl;
    
    if ( msg.control == 0 ) {
        for ( unsigned i = 0; i < surfaces.size(); i++ ) {
            offsetX = msg.value;
            surfaces[i].setOffsetX(msg.value);
        }
    }
    
    if ( msg.control == 1 ) {
        for ( unsigned i = 0; i < surfaces.size(); i++ ) {
            offsetY = msg.value;
            surfaces[i].setOffsetY(msg.value);
        }
    }
    
    if ( msg.control == 2 ) {
        oscSpeedX = (float)msg.value / 10.0f;
    }
    
    if ( msg.control == 3 ) {
        oscSpeedY = (float)msg.value / 10.0f;
    }
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