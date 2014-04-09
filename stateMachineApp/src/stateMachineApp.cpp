#include "stateMachineApp.h"

// Include states.
#include "mainState.h"
#include "secondState.h"
#include "thirdState.h"

void stateMachineApp::setup()
{
    // Setup state machine shared data.
    stateMachine.getSharedData().variable = 0;
    
    // Add states to the state machine.
    stateMachine.addState<mainState>();
    stateMachine.addState<secondState>();
    stateMachine.addState<thirdState>();
    
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
    
    if ( key == '1' ) {
        stateMachine.changeState("mainState");
    } else if ( key == '2' ) {
        stateMachine.changeState("secondState");
    } else if ( key == '3' ) {
        stateMachine.changeState("thirdState");
    }
}

void stateMachineApp::mousePressed( int x, int y, int button )
{
    cout << "Mouse pressed, x: " << x << ", y: " << y << ", button: " << button << endl;
}

