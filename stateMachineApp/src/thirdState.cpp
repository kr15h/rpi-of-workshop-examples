#include "thirdState.h"

void thirdState::setup()
{
    
}

void thirdState::update()
{
    
}

void thirdState::draw()
{
    ofBackground(0, 255, 255);
    ofSetColor(255);
    ofDrawBitmapString(getName(), 10, 20);
}

string thirdState::getName()
{
    return "thirdState";
}