#include "mainState.h"

void mainState::setup()
{
    
}

void mainState::update()
{
    
}

void mainState::draw()
{
    ofBackground(0);
    ofSetColor(255);
    ofDrawBitmapString(getName(), 10, 20);
}

void mainState::mousePressed( int x, int y, int button )
{
    
}

string mainState::getName()
{
    return "mainState";
}