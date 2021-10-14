
/***************************************************************************************************************************
 * File           : Graph.h
 * 
 * Purpose        : Provide the data structure for GA to implement the TSP
 * 
 * Author         : Hanumantappa Budihal 
 * Date           : 30-09-2021 
 * 
 * Bugs Log       :
 * 
 * Change Log     : Initial Creation : 30-09-2021 
 ****************************************************************************************************************************/

#include <map>

using namespace std;

#ifndef DATA_H
#define DATA_H

class Data
{
public:
    int _size;
    int _totalEdges;
    int _initialVertex;
    std::map<std::pair<int, int>, float> _edges;

public:
    Data(int size, int initialVertex);
    void AddEdge(int source, int destination, float weight);
    float GetEdgeCost(int source, int destination);
};

#endif
