#ifndef H_THIRD_STATE
#define H_THIRD_STATE

#include "ofxState.h"
#include "sharedData.h"

class thirdState : public itg::ofxState<sharedData>
{
public:
    void setup();
	void update();
	void draw();
	string getName();
};

#endif
