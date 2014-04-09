#ifndef H_MAIN_STATE
#define H_MAIN_STATE

#include "ofxState.h"
#include "sharedData.h"

class mainState : public itg::ofxState<sharedData>
{
public:
    void setup();
	void update();
	void draw();
	void mousePressed(int x, int y, int button);
	string getName(); // Every state has a unique name,
                      // this function has to return the name of the state
};

#endif
