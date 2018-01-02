//
//  DFO.cpp
//  finalProject1
//
//  Created by Joshua Hodge on 12/27/17.
//
//

#include "DFO.hpp"

//setup
void DFO::setupDFO (int _popSize, int _totalIterations, std::vector<float> _targetMFCC, float _lowerBounds, float _upperBounds)
{
    popSize = _popSize;
    totalIterations = _totalIterations;
    targetMFCC = _targetMFCC;
    lowerBounds = _lowerBounds;
    upperBounds = _upperBounds;
}

//=============================================================================

//initialize the flies
void DFO::initializeFlies(std::vector <std::vector <float>> &population, int numParams, int popSize)
{
    for (int i = 0; i < popSize; i++)
    {
        //create initial flies
        std::vector <float> temp;
        
        for (int j = 0; j < numParams; j++)
        {
            float randNum = lowerBounds + ofRandom(0.0f, 1.0f) * (upperBounds - lowerBounds);
            temp.push_back(randNum);
        }
        population.push_back(temp);
        temp.clear();
    }
}

//=============================================================================

void DFO::checkFlies (std::vector <std::vector <float>> population, int numParams)
{
    for (int i = 0; i < population.size(); i++)
    {
        for (int j = 0; j < numParams; j++)
        {
            std::cout << "Fly: " << i << " " << population[i][j] << std::endl;
        }
    }
}

//=============================================================================

void DFO::calculateFitness(std::vector <std::vector <float>> &totalFlyMFCC, std::vector <float>targetMFCC, std::vector <float> &fitness)
{
    for (int i = 0; i < totalFlyMFCC.size(); i++)
    {
        float temp = 0;
    
        for (int j = 0; j < targetMFCC.size(); j++)
        {
            //euclidean distance square result of differences
            float fitness = pow (targetMFCC[j] - totalFlyMFCC[i][j], 2);
            temp = fitness + temp;          //temp stores fitnesses until solution size
        
            if (j == targetMFCC.size() - 1)
            {
                temp = sqrt(temp);      //square root of sum
            }
        }
        //push distances into vector
        fitness.push_back(temp);
    }
}

//=============================================================================

//disturbance threshold between 0.0 and 0.9
int DFO::findSolution(float disturbanceThreshold, std::vector <std::vector <float>> &totalFlyMFCC, std::vector <float> targetMFCC, std::vector <float> &fitness, std::vector <float> &bestResult)
{
    for (int iterations = 0; iterations < totalIterations; iterations++)
    {
        fitness.clear();    //each iteration we must clear fitnesses and reload
        
        //calculate fitnesses
        calculateFitness(totalFlyMFCC, targetMFCC, fitness);
        
        //find index of fly with best fitness (closest to ideal solution)
        auto result = std::min_element(std::begin(fitness), std::end(fitness));
        fittestInSwarm = (int)(result - fitness.begin());
        std::cout << "Fittest fly in the swarm: for iteration " << iterations << ": " << fittestInSwarm << std::endl;
        
        for (int i = 0; i < fitness.size(); i++)
        {
            //skip fittest in swarm
            if (i != fittestInSwarm)
            {
            
                int leftFly;
                int rightFly;
            
                if (i == 0)
                {
                    leftFly = (int)fitness.size() - 1;
                }
                else
                {
                    //compare left and right fly and find more fit
                    leftFly = i - 1;
                }
            
                //if last fly, right fly is first fly
                if (i == fitness.size() - 1)
                {
                    rightFly = 0;
                }
                else
                {
                    rightFly = i + 1;
                }
            
                //find fittest neighbor
                int bestNeighbor = 0;
            
                if (fitness[leftFly] < fitness[rightFly])
                {
                    bestNeighbor = leftFly;
                }
                else if (fitness[leftFly] > fitness[rightFly])
                {
                    bestNeighbor = rightFly;
                }
            
                //random dice throw to sometimes redistribute fly
                float threshold = ofRandom(0.0f, 1.0f);
            
                if (threshold < disturbanceThreshold)
                {
                    for (int j = 0; j < targetMFCC.size(); j++)
                    {
                        //randomly scatter fly
                        float randNum = lowerBounds + ofRandom(0.0f, 1.0f) * (upperBounds - lowerBounds);
                    
                        totalFlyMFCC[i][j] = randNum;
                    }
                }
                else
                {
                    for (int j = 0; j < targetMFCC.size(); j++)
                    {
                        //update position
                        totalFlyMFCC[i][j] = totalFlyMFCC[bestNeighbor][j] + ofRandom(0.0, 1.0) * (totalFlyMFCC[fittestInSwarm][j] - totalFlyMFCC[bestNeighbor][j]);
                    }
                }
            }
        }
    }
    for (int i = 0; i < targetMFCC.size(); i++)
    {
        bestResult.push_back(totalFlyMFCC[fittestInSwarm][i]);
    }
    return fittestInSwarm;
}


