#include "ofMain.h"
#include "blankApp.h"

int main()
{
	ofSetupOpenGL(1024, 768, OF_WINDOW);
	ofRunApp( new blankApp() );
}
