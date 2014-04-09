#include "stateMachineApp.h"
#include "mainState.h"

void stateMachineApp::setup()
{
    // Setup state machine shared data.
    stateMachine.getSharedData().variable = 0;
    
    // Add states to the state machine.
    stateMachine.addState<mainState>();
    
    // Set default state.
    stateMachine.changeState("mainState");
}

void stateMachineApp::update()
{
    
}

void stateMachineApp::draw()
{
    
}

void stateMachineApp::keyPressed( int key )
{
    char keyChar = key;
    cout << "Key pressed: " << keyChar << endl;
}

void stateMachineApp::mousePressed( int x, int y, int button )
{
    cout << "Mouse pressed, x: " << x << ", y: " << y << ", button: " << button << endl;
}

