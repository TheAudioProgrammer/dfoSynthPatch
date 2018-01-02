/* This is an example of how to integrate maximilain into openFrameworks,
 including using audio received for input and audio requested for output.
 
 
 You can copy and paste this and use it as a starting example.
 
 */


#include "ofApp.h"
#include "maximilian.h"/* include the lib */
#include "time.h"

//-------------------------------------------------------------
ofApp::~ofApp() {
    
}


//--------------------------------------------------------------
void ofApp::setup(){
    
    sender.setup(HOST, PORT);
    /* some standard setup stuff*/
    
    ofSetWindowShape(0, 0);
    
    /* This is stuff you always need.*/
    
    sampleRate 			= 44100; /* Sampling Rate */
    initialBufferSize	= 512;	/* Buffer Size. you have to fill this buffer with sound*/
    lAudioOut			= new float[initialBufferSize];/* outputs */
    rAudioOut			= new float[initialBufferSize];
    lAudioIn			= new float[initialBufferSize];/* inputs */
    rAudioIn			= new float[initialBufferSize];
    
    
    /* This is a nice safe piece of code */
    memset(lAudioOut, 0, initialBufferSize * sizeof(float));
    memset(rAudioOut, 0, initialBufferSize * sizeof(float));
    
    memset(lAudioIn, 0, initialBufferSize * sizeof(float));
    memset(rAudioIn, 0, initialBufferSize * sizeof(float));
    
    fftSize = 1024;
    
    //setup MFCC
    mfccAnalyzer.setupMFCC(sampleRate, fftSize);
    
    ofxMaxiSettings::setup(sampleRate, 2, initialBufferSize);
    ofSoundStreamSetup(2,2, this, sampleRate, initialBufferSize, 4);/* Call this last ! */
    
    
    iterations = 50;
    popSize = 50;
    numParams = 6;
    thresh = 0.6f;
    
    //initialize target sound
    for (int i = 0; i < numParams; i++)
    {
        targetSound.push_back (ofRandom (0.0, 1.0));
    }
    
    //setup DFO
    myDFO.setupDFO(popSize, iterations, targetSound, 0.0, 1.0);
    
    //initialize flies into population
    myDFO.initializeFlies(population);
    
    //check flies are ok
    //myDFO.checkFlies(population);
    
    //calculate initial distance
    myDFO.calculateFitness(population, fitness);
    
    //put target sound params in synth
    freq1NormalizedT = targetSound[0];
    freq2NormalizedT = targetSound[1];
    modFreqNormalizedT = targetSound[2];
    modDepthNormalizedT = targetSound[3];
    filterFreqNormalizedT = targetSound[4];
    filterResNormalizedT = targetSound[5];
    
    
    //re-map to synth
    freq1T = ofMap(freq1NormalizedT, 0, 1, 100, 1000);
    freq2T = ofMap(freq2NormalizedT, 0, 1, 100, 1000);
    modFreqT = ofMap(modFreqNormalizedT, 0, 1, 100, 1000);
    modDepthT = ofMap(modDepthNormalizedT, 0, 1, 100, 1000);
    filterFreqT = ofMap(filterFreqNormalizedT, 0, 1, 100, 500);
    filterResT = ofMap(filterResNormalizedT, 0, 1, 0.0, 1.0);
    
    for (int i = 0; i < iterations; i++)
    {
        myDFO.findSolution(thresh, population, fitness, bestResult);
    }
    
    for (int i = 0; i < numParams; i++)
    {
        std::cout << targetSound[i] << std::endl;
    }
    
    //put target sound params in synth
    freq1NormalizedR = bestResult[0];
    freq2NormalizedR = bestResult[1];
    modFreqNormalizedR = bestResult[2];
    modDepthNormalizedR = bestResult[3];
    filterFreqNormalizedR = bestResult[4];
    filterResNormalizedR = bestResult[5];
    
    
    //re-map to synth
    freq1R = ofMap(freq1NormalizedR, 0, 1, 100, 1000);
    freq2R = ofMap(freq2NormalizedR, 0, 1, 100, 1000);
    modFreqR = ofMap(modFreqNormalizedR, 0, 1, 100, 1000);
    modDepthR = ofMap(modDepthNormalizedR, 0, 1, 100, 1000);
    filterFreqR = ofMap(filterFreqNormalizedR, 0, 1, 100, 500);
    filterResR = ofMap(filterResNormalizedR, 0, 1, 0.0, 1.0);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}



//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::audioRequested 	(float * output, int bufferSize, int nChannels){
    
    for (int i = 0; i < bufferSize; i++){
        
        double envOutTarget = mySynth.playSynth(freq1T, freq2T, modFreqT, modDepthT, filterFreqT, filterResT, triggerT);
        
        
        double envOutResult = mySynth.playSynth(freq1R, freq2R, modFreqR, modDepthR, filterFreqR, filterResR, triggerR);
        
        if (triggerT == 1)
        {
            //filter to output
            mymix.stereo(envOutTarget, outputs, 0.8);
        }
        
        if (triggerR == 1)
        {
            mymix2.stereo(envOutResult, outputs, 0.8);
        }
        
        //output to speakers
        lAudioOut[i] = output[i*nChannels    ] = outputs[0];
        rAudioOut[i] = output[i*nChannels + 1] = outputs[1];
    }
}

//--------------------------------------------------------------
void ofApp::audioReceived 	(float * input, int bufferSize, int nChannels){
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    //play sample using space bar
    if (key == 116)
    {
        triggerT = 1;
    }
    
    if (key == 114)
    {
        triggerR = 1;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    //play sample using space bar
    if (key == 116)
    {
        triggerT = 0;
    }
    
    if (key == 114)
    {
        triggerR = 0;
    }

    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

