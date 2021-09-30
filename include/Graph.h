
/***************************************************************************************************************************
 * File           : Graph.h
 * 
 * Purpose        : //TODO : Need add the proper comment
 * 
 * Author         : Hanumantappa Budihal 
 * Date           : 27-09-2021 
 * 
 * Bugs Log       :
 * 
 * Change Log     : Initial Creation : 23-09-2021
 ****************************************************************************************************************************/

#include <map>

using namespace std;

/***************************************************************************************************************************
 * File           : Graph.h
 * 
 * Purpose        : Implement the graph data strucutre which supports the implementation of the travelling    
 *                  saleman problem using genetic algorithm
 * 
 * Author         : Hanumantappa Budihal 
 * Date           : 27-09-2021 
 * 
 * Bugs Log       :
 * 
 * Change Log     : Initial Creation : 23-09-2021
 ****************************************************************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
public:
    int _size; //TODO public function to acces the data ?
    int _totalEdges;
    int _initialVertex;
    std::map<std::pair<int, int>, float> _edges;

public:
    Graph(int size, int initialVertex); //TODO : need to
    void AddEdge(int source, int destination, float weight);
    float GetEdgeCost(int source, int destination);

    friend class Genetic; //TODO : Need to rename the variable
};

#endif
