//
//  mfccAnalysis.cpp
//  naturalComputingFinal2
//
//  Created by Joshua Hodge on 1/1/18.
//
//

#include "mfccAnalysis.hpp"

void mfccAnalysis::setupMFCC(int sampleRate, int fftSize)
{
    mfft.setup(fftSize, 512, 256);
    ifft.setup(fftSize, 512, 256);
    
    nAverages = 12;
    oct.setup(sampleRate, fftSize/2, nAverages);
    
    mfccs = (double*) malloc(sizeof(double) * 13);
    mfcc.setup(512, 42, 13, 20, 20000, sampleRate);
}

//=============================================================

void mfccAnalysis::analyzeMFCC (double inputWave, int fftSize, std::vector <float> &targetMFCC, bool &flyAnalyzed)
{
    double wave = inputWave;
    
    //get fft
    if (mfft.process(wave) && ! flyAnalyzed) {
        
        mfft.magsToDB();
        oct.calculate(mfft.magnitudesDB);
        
        float sum = 0;
        float maxFreq = 0;
        int maxBin = 0;
        
        for (int i = 0; i < fftSize/2; i++) {
            sum += mfft.magnitudes[i];
            if (mfft.magnitudes[i] > maxFreq) {
                maxFreq=mfft.magnitudes[i];
                maxBin = i;
            }
        }
        centroid = sum / (fftSize / 2);
        peakFreq = (float)maxBin/fftSize * 44100;
        
        mfcc.mfcc(mfft.magnitudes, mfccs);
        
        
        //cout coefficients
        cout << "\nMFCCS: ";
        for(int i=0; i < 13; i++) {
            
            targetMFCC.push_back(mfccs[i]);
            cout << mfccs[i] << ",";
        }
        
        
        //file is now analyzed, don't analyze again
        flyAnalyzed = true;
    }

}
