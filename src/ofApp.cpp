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
    
    //variable initialization
    fftSize = 1024;
    iterations = 50;
    popSize = 15;
    numParams = 6;
    thresh = 0.8f;
    targetTrigger = 0;
    fittestTrigger = 0;
    targetAnalyzed = false;

    //setup MFCC
    mfccAnalyzer.setupMFCC(sampleRate, fftSize);
    
    ofxMaxiSettings::setup(sampleRate, 2, initialBufferSize);
    ofSoundStreamSetup(2,2, this, sampleRate, initialBufferSize, 4);/* Call this last ! */
    
    //initialize target sound
    for (int i = 0; i < numParams; i++)
    {
        targetParams.push_back (ofRandom (0.0, 1.0));
    }
    
    //get target MFCC we want to get to
    mySynth.getTargetMFCC(mySynth, mfccAnalyzer, fftSize, targetParams, targetMFCC);
    
    
    //setup DFO
    myDFO.setupDFO(popSize, iterations, targetMFCC, 0.0, 1.0);
    
    //initialize flies into population
    myDFO.initializeFlies(population, numParams, popSize);
    
    //check flies are ok
    //myDFO.checkFlies(population, numParams);
    
    //get initial fly MFCCs
    mySynth.getFlyMFCC(mySynth, mfccAnalyzer, popSize, fftSize, population, totalFlyMFCC);
    
    //calculate how far fly MFCC is from target MFCC
    //myDFO.calculateFitness(totalFlyMFCC, targetMFCC, fitness);
    
    fittestFly = myDFO.findSolution(0.1, totalFlyMFCC, targetMFCC, fitness, bestResult);
    //mySynth.checkTarget(targetMFCC);
    
    
    //re-map parameters from above to synth
    targetFreq1 = ofMap(targetParams[0], 0, 1, 100, 1000);
    targetFreq2 = ofMap(targetParams[1], 0, 1, 100, 1000);
    targetModFreq = ofMap(targetParams[2], 0, 1, 100, 1000);
    targetModDepth = ofMap(targetParams[3], 0, 1, 100, 1000);
    targetFilterFreq = ofMap(targetParams[4], 0, 1, 100, 500);
    targetFilterRes = ofMap(targetParams[5], 0, 1, 0.0, 1.0);
    
    fittestFreq1 = ofMap(population[fittestFly][0], 0, 1, 100, 1000);
    fittestFreq2 = ofMap(population[fittestFly][1], 0, 1, 100, 1000);
    fittestModFreq = ofMap(population[fittestFly][2], 0, 1, 100, 1000);
    fittestModDepth = ofMap(population[fittestFly][3], 0, 1, 100, 1000);
    fittestFilterFreq = ofMap(population[fittestFly][4], 0, 1, 100, 500);
    fittestFilterRes = ofMap(population[fittestFly][5], 0, 1, 0.0, 1.0);
    
    std::cout << "READY TO PLAY" << std::endl;
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
        
        double targetEnvOut = mySynth.playSynth(targetFreq1, targetFreq2, targetModFreq, targetModDepth, targetFilterFreq, targetFilterRes, targetTrigger);
        
        
        double fittestEnvOut = mySynth2.playSynth(fittestFreq1, fittestFreq2, fittestModFreq, fittestModDepth, fittestFilterFreq, fittestFilterRes, fittestTrigger);
        
        
        if (targetTrigger == 1)
        {
            //filter to output
            mymix.stereo(targetEnvOut, outputs, 0.8);
        }
        
        if (fittestTrigger == 1)
        {
            mymix2.stereo(fittestEnvOut, outputs, 0.8);
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
    
    if (key == 116)
    {
        targetTrigger = 1;
    }
    
    if (key == 114)
    {
        fittestTrigger = 1;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    //play sample using space bar
    if (key == 116)
    {
        targetTrigger = 0;
    }
    
    if (key == 114)
    {
        fittestTrigger = 0;
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

