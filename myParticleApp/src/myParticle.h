//
//  myParticle.h
//  emptyExample
//
//  Created by Krisjanis Rijnieks on 10/1/13.
//
//

#ifndef __emptyExample__myParticle__
#define __emptyExample__myParticle__

#include "ofMain.h"

class myParticle {
public:
    myParticle();
    ~myParticle();
    
    ofPoint position;
    float radius;
    ofPoint speed;
    
private:
    int randomVariable;
};

#endif /* defined(__emptyExample__myParticle__) */
