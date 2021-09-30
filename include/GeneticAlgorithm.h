
/***************************************************************************************************************************
 * File           : GeneticAlgorithm.h
 * 
 * Purpose        : Implmenent the GA to solve the TSP Problem
 * 
 * Author         : Hanumantappa Budihal 
 * Date           : 27-09-2021 
 * 
 * Bugs Log       :
 * 
 * Change Log     : Initial Creation : 23-09-2021
 ****************************************************************************************************************************/

#include <map>
#include <vector>
#include "Graph.h"

using namespace std;

#ifndef GeneticAlgorithm_H
#define GeneticAlgorithm_H

typedef std::pair<std::vector<int>, float> my_pair;

class GeneticAlgorithm
{
private:
    Graph *graph;
    std::vector<my_pair> population;
    int size_population;
    int real_size_population;
    int mutation_rate;

private:
    void initialPopulation();

public:
    GeneticAlgorithm(Graph *graph, int amount_population, int mutation_rate);
    float IsValidSolution(std::vector<int> &solution);
    void CrossOver(std::vector<int> &parent1, std::vector<int> &parent2);
    void InsertBinarySearch(std::vector<int> &child, float total_cost);
    void Run();
    float GetCostBestSolution();
    bool IsChromosomeExists(const std::vector<int> &v);
};

#endif
