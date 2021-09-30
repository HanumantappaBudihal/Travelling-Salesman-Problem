/****************************************************************************************************************
 * File           : Graph.cpp 
 * 
 * Purpose        : Implement the graph data strucutre which supports the implementation of the travelling    
 *                  saleman problem using genetic algorithm
 * 
 * Author         : Hanumantappa Budihal 
 * Date           : 23-08-2021 19:10 IST
 * 
 * Bugs Log       :
 * 
 * Change Log     : Initial Creation : 23-08-2021 19:10 IST
 *****************************************************************************************************************/
#include "../include/Graph.h"

using namespace std;

/*****************************************************************************************************************
 * Function : Graph (Constructor)
 * 
 * Purpose  : Initiate the graph instance with size of the graph , initial vertex and totalEdges
 * 
 * Inputs   : Size of the graph and initial vertex
 * Outputs  : New instance created with give graph size and vertex           
 ******************************************************************************************************************/
Graph::Graph(int size, int initialVertex)
{
    this->_size = size;
    this->_initialVertex = initialVertex;
    this->_totalEdges = 0;
} //End of constructor

/*****************************************************************************************************************
 * Function : Graph (Constructor)
 * 
 * Purpose  : Add the edge to graph edges list
 * 
 * Inputs   : source , destination and cost between the source and destination
 * Outputs  : //TOOD : Need to add the comment here       
 ******************************************************************************************************************/
void Graph::AddEdge(int source, int destination, float cost)
{
    _edges[make_pair(source, destination)] = cost;
} // End of AddEdge

/*****************************************************************************************************************
 * Function : Graph (Constructor)
 * 
 * Purpose  : Return the cost of the edge between source and destination
 * 
 * Inputs   : source and destination
 * Outputs  : return the edge cost betweent the source and destination          
 ******************************************************************************************************************/
float Graph::GetEdgeCost(int source, int destination)
{
    map<pair<int, int>, float>::iterator it = _edges.find(make_pair(source, destination));

    return it->second;
} //End of GetEdgeCost
