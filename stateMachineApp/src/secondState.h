#ifndef H_SECOND_STATE
#define H_SECOND_STATE

#include "ofxState.h"
#include "sharedData.h"

class secondState : public itg::ofxState<sharedData>
{
public:
    void setup();
	void update();
	void draw();
	string getName();
};

#endif
