
/***************************************************************************************************************************
 * File           : Data.h
 * 
 * Purpose        : //TODO : Need add the proper comment
 * 
 * Author         : Hanumantappa Budihal 
 * Date           : 27-09-2021 
 * 
 * Bugs Log       :
 * 
 * Change Log     : Initial Creation : 27-09-2021
 ****************************************************************************************************************************/

#include <vector>
#include <set>

#include "Data.h"
using namespace std;

#ifndef ANT_H
#define ANT_H

//TODO: need to add the comment
class Ant
{
public:
    vector<int> trail;
    set<int> available;
    double alpha;                     // importance of the pheromone level
    double beta;                      // importance of the visibility
    Ant(double a, double b, Data *d); //Constructor

    Data d; // global data construct

    void reset();
    void deposit();
    vector<int> stop();
    void step();
    double getRand();
    double moveProbability(int i, int j, double norm);
    double probabilityNorm(int currentCity);
};

#endif
