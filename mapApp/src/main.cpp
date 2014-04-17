#include "ofMain.h"
#include "testApp.h"

//========================================================================
int main()
{
#ifdef TARGET_RASPBERRY_PI
    cout << "Target Raspberry Pi defined: launching in fullscreen." << endl;
    ofSetupOpenGL(720,576,OF_FULLSCREEN);
#else
    cout << "Target regular computer: launching in window" << endl;
    ofSetupOpenGL(720,576,OF_WINDOW);
#endif

	ofRunApp( new testApp());
}
