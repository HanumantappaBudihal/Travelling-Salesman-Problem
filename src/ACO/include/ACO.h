#include <vector>
#include "../include/Ant.h"
#include "../include/Data.h"

using namespace std;

#ifndef ACO_H
#define ACO_H

class ACO
{
public:
    int N;              // cities
    int M;              // no.of ants
    vector<Ant> ant;    // ants
    double evaporation; // evaporation rate
    double alpha;       // importance of the pheromone level
    double beta;        // importance of the visibility
    Data d;

    void Init(double a, double b, double e, Data ds);
    void run();
};

#endif