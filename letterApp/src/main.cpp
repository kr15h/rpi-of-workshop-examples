#include "ofMain.h"
#include "letterApp.h"

int main()
{
#ifdef TARGET_RASPBERRY_PI
    ofSetupOpenGL(800,600, OF_FULLSCREEN);
#else
    ofSetupOpenGL(800,600, OF_WINDOW);
#endif
    
	ofRunApp( new letterApp());
}
