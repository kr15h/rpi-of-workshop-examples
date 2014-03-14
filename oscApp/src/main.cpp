#include "ofMain.h"
#include "oscApp.h"

int main()
{
	ofSetupOpenGL(1024, 768, OF_WINDOW);
	ofRunApp( new oscApp() );
}
