#include "time.h"
using namespace std;

/***************************************************************************************************************************
 * File           : SimulatedAnnealing.h
 * 
 * Purpose        : Implmenent TSP Algorithm using the simulated annealing approach
 * 
 * Author         : Hanumantappa Budihal 
 * Date           : 30-09-2021 
 * 
 * Bugs Log       :
 * 
 * Change Log     : Initial Creation : 30-09-2021 
 ****************************************************************************************************************************/

#ifndef GeneticAlgorithm_H
#define GeneticAlgorithm_H

//TODO : Need to add the comments
class TravellingSaleMan
{
private:
    char distance_type[30];
    int n;
    double *x, *y;
    double **adjacency_matrix;
    int *curr_path, *new_path, *min_path;
    double temparature;
    clock_t tStart;

public:
    TravellingSaleMan();
    ~TravellingSaleMan();
    void SimulatedAnnealing();
    void readFile();
    void init();
    void retraceMinPath();
    int generateRandomNumber();
    void swap(int, int, int *);
    int getCost(int *);
    void two_opt(int, int, int *);
};

#endif