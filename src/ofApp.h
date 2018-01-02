#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "DFO.hpp"
#include "mfccAnalysis.hpp"
#include "synth.hpp"


#include <sys/time.h>

#include "maxiMFCC.h"
#define HOST "localhost"
#define PORT 12345

class ofApp : public ofBaseApp{
    
public:
    ~ofApp();/* deconsructor is very useful */
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    
    void audioRequested 	(float * input, int bufferSize, int nChannels); /* output method */
    void audioReceived 	(float * input, int bufferSize, int nChannels); /* input method */
    
    float 	* lAudioOut; /* outputs */
    float   * rAudioOut;
    
    float * lAudioIn; /* inputs */
    float * rAudioIn;
    
    int	initialBufferSize; /* buffer size */
    int	sampleRate;
    int fftSize;
    
    
    //MAXIMILIAN STUFF:
    double wave,sample,outputs[2], ifftVal;
    maxiMix mymix, mymix2;
    
    
    //synth stuff (Target)
    int triggerT;
    float freq1T;
    float freq2T;
    float modFreqT;
    float modDepthT;
    float filterFreqT;
    float filterResT;
    
    //normalize synth ranges (Target)
    float freq1NormalizedT;
    float freq2NormalizedT;
    float modFreqNormalizedT;
    float modDepthNormalizedT;
    float filterFreqNormalizedT;
    float filterResNormalizedT;
    
    //synth stuff (Result)
    int triggerR;
    float freq1R;
    float freq2R;
    float modFreqR;
    float modDepthR;
    float filterFreqR;
    float filterResR;
    
    //normalize synth ranges (Result)
    float freq1NormalizedR;
    float freq2NormalizedR;
    float modFreqNormalizedR;
    float modDepthNormalizedR;
    float filterFreqNormalizedR;
    float filterResNormalizedR;
    
    
    
    //mfcc analyzer
    mfccAnalysis mfccAnalyzer;
    
    //synthesizer
    synth mySynth;
    
    //DFO class
    DFO myDFO;
    
    //vectors and variables for DFO
    std::vector <float> targetSound;
    std::vector <std::vector <float>> population;
    std::vector <float> fitness;
    std::vector <float> bestResult;
    int iterations;
    int popSize;
    int numParams;
    float thresh;
    
    ofTrueTypeFont myfont;
    
    ofxOscSender sender;
    
    //bool isAnalyzed;
    
    
    
};

