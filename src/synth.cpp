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
    //adsr settings (need to play sound)
    envelope.setAttack (0.1f);
    envelope.setDecay (200.0f);
    envelope.setSustain (0.8f);
    envelope.setRelease (1000.0f);
    
    //fm oscillator
    double modOsc = mod.square ((modFreq) * modDepth);
    
    //oscs 1 and 2
    double firstOsc = osc1.sawn (freq1 + modOsc);
    double secondOsc = osc2.square (freq2);
    
    //keep levels under 1
    float level = 0.7f;
    
    //combine sounds and store in a variable
    double theWave = firstOsc + secondOsc * level;
    
    //route osc to filter
    double filterOut = filter.lores(theWave, filterFreq, filterRes);
    
    //return synth sound
    return  envelope.adsr(filterOut, trigger);
}

//=============================================================================

void synth::getTargetMFCC (synth mySynth, mfccAnalysis &mfccAnalyzer, int fftSize, std::vector <float> targetSound, std::vector <float> &targetMFCC)
{
    //timer allows mfcc analysis of each synth patch
    ofResetElapsedTimeCounter();
    int time = ofGetElapsedTimeMillis();
    bool targetAnalyzed = false;
    
    do
    {
        //get parameters from target sound
        float freq1Normalized = targetSound[0];
        float freq2Normalized = targetSound[1];
        float modFreqNormalized = targetSound[2];
        float modDepthNormalized = targetSound[3];
        float filterFreqNormalized = targetSound[4];
        float filterResNormalized = targetSound[5];
        
        //re-map parameters from above to synth
        float freq1 = ofMap(freq1Normalized, 0, 1, 100, 1000);
        float freq2 = ofMap(freq2Normalized, 0, 1, 100, 1000);
        float modFreq = ofMap(modFreqNormalized, 0, 1, 100, 1000);
        float modDepth = ofMap(modDepthNormalized, 0, 1, 100, 1000);
        float filterFreq = ofMap(filterFreqNormalized, 0, 1, 100, 500);
        float filterRes = ofMap(filterResNormalized, 0, 1, 0.0, 1.0);
        
        //triggers synth
        int trigger = 1;
        
        //play synth for 1 second
        double envOutTarget = mySynth.playSynth(freq1, freq2, modFreq, modDepth, filterFreq, filterRes, trigger);
        
        //get mfcc analysis of synth patch
        mfccAnalyzer.analyzeMFCC(envOutTarget, fftSize, targetMFCC, targetAnalyzed);
    }
    while (ofGetElapsedTimeMillis() < time + 100);
}

//=============================================================================

void synth::getFlyMFCC (synth mySynth, mfccAnalysis &mfccAnalyzer, int popSize, int fftSize, std::vector <std::vector <float>> population, std::vector <std::vector <float>> &totalFlyMFCC)
{
    for (int i = 0; i < popSize; i++)
    {
        //timer allows mfcc analysis of each synth patch
        ofResetElapsedTimeCounter();
        int time = ofGetElapsedTimeMillis();
        
        //this resets every iteration so analysis is done just once on each fly
        bool flyAnalyzed = false;
        
        //store fly analysis in vector
        std::vector <float> flyMFCC;
    
        do
        {
            //get parameters from fly
            float freq1Normalized = population[i][0];
            float freq2Normalized = population[i][1];
            float modFreqNormalized = population[i][2];
            float modDepthNormalized = population[i][3];
            float filterFreqNormalized = population[i][4];
            float filterResNormalized = population[i][5];
        
            //re-map parameters from above to synth
            float freq1 = ofMap(freq1Normalized, 0, 1, 100, 1000);
            float freq2 = ofMap(freq2Normalized, 0, 1, 100, 1000);
            float modFreq = ofMap(modFreqNormalized, 0, 1, 100, 1000);
            float modDepth = ofMap(modDepthNormalized, 0, 1, 100, 1000);
            float filterFreq = ofMap(filterFreqNormalized, 0, 1, 100, 500);
            float filterRes = ofMap(filterResNormalized, 0, 1, 0.0, 1.0);
        
            //triggers synth
            int trigger = 1;
            
            //play synth for 1 second
            double envOutTarget = mySynth.playSynth(freq1, freq2, modFreq, modDepth, filterFreq, filterRes, trigger);
            
            //get mfcc analysis of synth patch
            mfccAnalyzer.analyzeMFCC(envOutTarget, fftSize, flyMFCC, flyAnalyzed);
        }
        while (ofGetElapsedTimeMillis() < time + 100);
    
        //store the mfcc in a vector
        totalFlyMFCC.push_back(flyMFCC);
        flyMFCC.clear();
    }
}

//=============================================================================

void synth::checkFlies (std::vector <std::vector <float>> totalFlyMFCC)
{
    for (int i = 0; i < totalFlyMFCC.size(); i++)
    {
        for (int j = 0; j < 13; j++)
        {
            std::cout << "Fly: " << i << " " << totalFlyMFCC[i][j] << std::endl;
        }
    }
}

//=============================================================================

void synth::checkTarget (std::vector <float> targetMFCC)
{
    for (int j = 0; j < 13; j++)
    {
        std::cout << "Target: " << targetMFCC[j] << std::endl;
    }
}

