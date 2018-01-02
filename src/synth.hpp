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
#include "ofMain.h"
#include <sys/time.h>
#include "mfccAnalysis.hpp"

class synth
{
public:
    double playSynth (float freq1, float freq2, float modFreq, float modDepth, float filterFreq, float filterRes, int& trigger);
    
    void getTargetMFCC (synth mySynth, mfccAnalysis &mfccAnalyzer, int fftSize, std::vector <float> targetSound, std::vector <float> &targetMFCC);
    
    void getFlyMFCC (synth mySynth, mfccAnalysis &mfccAnalyzer, int popSize, int fftSize, std::vector <std::vector <float>> population, std::vector <std::vector <float>> &totalFlyMFCC);
    
    void checkFlies (std::vector <std::vector <float>> totalFlyMFCC);
    void checkTarget (std::vector <float> targetMFCC);
    
    
    
private:
    maxiOsc osc1;
    maxiOsc osc2;
    maxiOsc mod;
    maxiFilter filter;
    maxiEnv envelope;
    
    
};



#endif /* synth_hpp */
