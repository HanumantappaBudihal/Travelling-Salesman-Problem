#include <bits/stdc++.h>
#include <iostream>

//User defined header files
#include "../include/GeneticAlgorithm.h"

using namespace std;

/****************************************************************************************************************
 * File           : Main.cpp 
 * 
 * Purpose        : Implementation of the travelling saleman problem using genetic algorithm
 * 
 * Author         : Hanumantappa Budihal 
 * Date           : 30-09-2021
 * 
 * Bugs Log       :
 * 
 * Change Log     : Initial Creation : 30-09-2021
 *****************************************************************************************************************/

int main()
{
    const clock_t begin_time = clock();
    srand(time(NULL)); // To generates a deterministic sequence of numbers

    string distanceType;
    int numberOfCities;
    cin >> distanceType;   //Read distance type ( ecluiden or non ecluidean)
    cin >> numberOfCities; //Read the number of cities

    Graph *graph = new Graph(numberOfCities, 0);
    float coord[numberOfCities][2]; //Cities coordinates

    for (int i = 0; i < numberOfCities; i++)
    {
        cin >> coord[i][0] >> coord[i][1];
    }

    //Read the input matrix data and create the edges to graph
    for (int i = 0; i < numberOfCities; i++)
    {
        float x;
        for (int j = 0; j < numberOfCities; j++)
        {
            cin >> x;
            graph->AddEdge(i, j, x);
        }
    }

    //sizePopulation = 20
    //generations = 100000
    //mutationRate = 17
    GeneticAlgorithm genetic(graph, 20, 100000, 17);
    genetic.Run();

    cout << "\n\nTime for to run the genetic algorithm: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " seconds.";
    return 0;
} //End of main method
