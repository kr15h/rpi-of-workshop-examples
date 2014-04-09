#include "secondState.h"

void secondState::setup()
{
    
}

void secondState::update()
{
    
}

void secondState::draw()
{
    ofBackground(255, 0, 0);
    ofSetColor(255);
    ofDrawBitmapString(getName(), 10, 20);
}

string secondState::getName()
{
    return "secondState";
}