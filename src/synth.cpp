//
//  synth.cpp
//  naturalComputingFinal2
//
//  Created by Joshua Hodge on 1/1/18.
//
//

#include "synth.hpp"

double synth::playSynth (float freq1, float freq2, float modFreq, float modDepth, float filterFreq, float filterRes, int& trigger)
{
    //adsr settings
    envelope.setAttack (0.1f);
    envelope.setDecay (200.0f);
    envelope.setSustain (0.8f);
    envelope.setRelease (1000.0f);
    
    double modOsc = mod.square ((modFreq) * modDepth);
    
    double firstOsc = osc1.sawn (freq1 + modOsc);
    double secondOsc = osc2.square (freq2);
    float level = 0.7f;
    
    //osc routing
    double theWave = firstOsc + secondOsc * level;
    
    //route osc to filter
    double filterOut = filter.lores(theWave, filterFreq, filterRes);
    
    return  envelope.adsr(filterOut, trigger);
}





