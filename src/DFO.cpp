//
//  DFO.cpp
//  finalProject1
//
//  Created by Joshua Hodge on 12/27/17.
//
//

#include "DFO.hpp"

//constructor
void DFO::setupDFO (int _populationSize, int _totalIterations, std::vector<float> _targetVector, float _lowerBounds, float _upperBounds)
{
    populationSize = _populationSize;
    totalIterations = _totalIterations;
    targetVector = _targetVector;
    lowerBounds = _lowerBounds;
    upperBounds = _upperBounds;
}

//initialize the flies
void DFO::initializeFlies(std::vector <std::vector <float>> &population)
{
    for (int i = 0; i < populationSize; i++)
    {
        //create initial flies
        std::vector <float> temp;
        
        for (int j = 0; j < targetVector.size(); j++)
        {
            float randNum = lowerBounds + ofRandom(0.0f, 1.0f) * (upperBounds - lowerBounds);
            temp.push_back(randNum);
        }
        population.push_back(temp);
        temp.clear();
    }
}

void DFO::checkFlies (std::vector <std::vector <float>> population)
{
    for (int i = 0; i < population.size(); i++)
    {
        for (int j = 0; j < targetVector.size(); j++)
        {
            std::cout << "Fly: " << i << " " << population[i][j] << std::endl;
        }
    }
}



void DFO::calculateFitness(std::vector <std::vector <float>> &population, std::vector <float> &fitness)
{
    for (int i = 0; i < population.size(); i++)
    {
        float temp = 0;
    
        for (int j = 0; j < targetVector.size(); j++)
        {
            //euclidean distance square result of differences
            float fitness = pow (targetVector[j] - population[i][j], 2);
            temp = fitness + temp;          //temp stores fitnesses until solution size
        
            if (j == targetVector.size() - 1)
            {
                temp = sqrt(temp);      //square root of sum
            }
        }
        //push distances into vector
        fitness.push_back(temp);
    }
}

//disturbance threshold between 0.0 and 0.9
void DFO::findSolution(float disturbanceThreshold, std::vector <std::vector <float>> &population, std::vector <float> &fitness, std::vector <float> &bestResult)
{
    for (int iterations = 0; iterations < totalIterations; iterations++)
    {
        fitness.clear();    //each iteration we must clear fitnesses and reload
        
        //calculate fitnesses
        calculateFitness(population, fitness);
        
        //find index of fly with best fitness (closest to ideal solution)
        auto result = std::min_element(std::begin(fitness), std::end(fitness));
        fittestInSwarm = (int)(result - fitness.begin());
        
        for (int i = 0; i < targetVector.size(); i++)
        {
            std::cout << "Fittest fly in Swarm: " << fittestInSwarm << " Parameter: " << i << " " << population[fittestInSwarm][i] << std::endl;
        }
        
        for (int i = 0; i < fitness.size(); i++)
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
                for (int j = 0; j < targetVector.size(); j++)
                {
                    //randomly scatter fly
                    float randNum = lowerBounds + ofRandom(0.0f, 1.0f) * (upperBounds - lowerBounds);
                    
                    population[i][j] = randNum;
                }
            }
            else
            {
                for (int j = 0; j < targetVector.size(); j++)
                {
                    //update position
                    population[i][j] = population[bestNeighbor][j] + ofRandom(0.0, 1.0) * (population[fittestInSwarm][j] - population[bestNeighbor][j]);
                }
            }
        }
    }
    for (int i = 0; i < targetVector.size(); i++)
    {
        bestResult.push_back(population[fittestInSwarm][i]);
    }
}


