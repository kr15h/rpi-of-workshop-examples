#include "ofMain.h"
#include "stroboApp.h"

int main( )
{
	ofSetupOpenGL(1024,768, OF_FULLSCREEN);
	ofRunApp( new stroboApp());
}
