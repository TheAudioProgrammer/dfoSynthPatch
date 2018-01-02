//
//  mfccAnalysis.hpp
//  naturalComputingFinal2
//
//  Created by Joshua Hodge on 1/1/18.
//
//

#ifndef mfccAnalysis_hpp
#define mfccAnalysis_hpp

#include <stdio.h>
#include "ofxMaxim.h"


class mfccAnalysis
{
public:
    void setupMFCC(int sampleRate, int fftSize);
    void analyzeMFCC (double inputWave, int fftSize, std::vector <float> &targetMFCC, bool &flyAnalyzed);
    


private:
    ofxMaxiIFFT ifft;
    ofxMaxiFFT mfft;
    int fftSize;
    int bins, dataSize;
    
    ofxMaxiFFTOctaveAnalyzer oct;
    int nAverages;
    float *ifftOutput;
    int ifftSize;
    
    float peakFreq = 0;
    float centroid = 0;
    float RMS = 0;
    
    maxiMFCC mfcc;
    double *mfccs;
    
    bool isAnalyzed;
};




#endif /* mfccAnalysis_hpp */
