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
    
    //mfcc analyzer
    mfccAnalysis mfccAnalyzer;
    
    //synthesizer
    synth mySynth, mySynth2;
    int fittestTrigger;
    int targetTrigger;
    
    std::vector <float> targetMFCC;
    std::vector <float> flyMFCC;
    std::vector <std::vector <float>> totalFlyMFCC;
    
    //DFO class
    DFO myDFO;
    
    //vectors and variables for DFO
    std::vector <std::vector <float>> population;
    std::vector <float> targetParams;
    
    std::vector <float> fitness;
    std::vector <float> bestResult;
    int iterations;
    int popSize;
    int numParams;
    float thresh;
    
    int fittestFly;
    
    float targetFreq1;
    float targetFreq2;
    float targetModFreq;
    float targetModDepth;
    float targetFilterFreq;
    float targetFilterRes;
    
    float fittestFreq1;
    float fittestFreq2;
    float fittestModFreq;
    float fittestModDepth;
    float fittestFilterFreq;
    float fittestFilterRes;
    
    ofTrueTypeFont myfont;
    
    ofxOscSender sender;
    
    bool targetAnalyzed;
    bool flyAnalyzed;
};

