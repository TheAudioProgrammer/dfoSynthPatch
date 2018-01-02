//
//  synth.hpp
//  naturalComputingFinal2
//
//  Created by Joshua Hodge on 1/1/18.
//
//

#ifndef synth_hpp
#define synth_hpp

#include <stdio.h>
#include "ofxMaxim.h"

class synth
{
public:
    double playSynth (float freq1, float freq2, float modFreq, float modDepth, float filterFreq, float filterRes, int& trigger);
    
    
    
private:
    maxiOsc osc1;
    maxiOsc osc2;
    maxiOsc mod;
    maxiFilter filter;
    maxiEnv envelope;
    
    
};



#endif /* synth_hpp */
