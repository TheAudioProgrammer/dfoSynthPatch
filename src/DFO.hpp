//
//  DFO.hpp
//  finalProject1
//
//  Created by Joshua Hodge on 12/27/17.
//
//

#ifndef DFO_hpp
#define DFO_hpp

#include "ofMain.h"
#include <stdio.h>


class DFO
{
public:
    void setupDFO (int _populationSize, int _iterations, std::vector<float> _targetVector, float _lowerBounds, float _upperBounds);
    
    void initializeFlies(std::vector <std::vector <float>> &population, int numParams, int popSize);
    void checkFlies(std::vector <std::vector <float>> population, int numParams);
    
    void calculateFitness(std::vector <std::vector <float>> &totalFlyMFCC, std::vector <float>targetMFCC, std::vector <float> &fitness);
    
    int findSolution(float disturbanceThreshold, std::vector <std::vector <float>> &totalFlyMFCC, std::vector <float> targetMFCC, std::vector <float> &fitness, std::vector <float> &bestResult);

                  
private:
    
    
    int popSize;
    int totalIterations;
    std::vector <float> targetMFCC;
    
    std::vector <float> fitness;
    
    //set upper and lower bounds of data space
    float lowerBounds;
    float upperBounds;
    
    int fittestInSwarm;
    
};






#endif /* DFO_hpp */
