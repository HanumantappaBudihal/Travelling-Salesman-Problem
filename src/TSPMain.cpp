#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include "../include/ACO.h"
#include "../include/Data.h"
#include "../include/Ant.h"

using namespace std;
//TSP Algorithm section
//#include <../Dynamic/TSPUsingDynamicProgramming.hpp>
class TSPUsingDynamicProgramming
{
private:
    int _numberOfCities;
    vector<vector<float>> _distances;

    int visited[10]; //TODO : Need to make it dynamic
    float _minimumCost;
    vector<int> _optimalPath;

    int GetLeastOCost(int cityNumber)
    {
        int i, nc = INT32_MAX;
        float min = INT32_MAX, kmin; //TODO : need to change the data type to float
        for (i = 0; i < _numberOfCities; i++)
        {
            if ((_distances[cityNumber][i] != 0) && (visited[i] == 0))
                if (_distances[cityNumber][i] < min)
                {
                    min = _distances[i][0] + _distances[cityNumber][i];
                    kmin = _distances[cityNumber][i];
                    nc = i;
                }
        }

        if (min != INT32_MAX)
            _minimumCost += kmin;

        return nc;
    }

    //Constructor
public:
    TSPUsingDynamicProgramming(vector<vector<float>> distances, int numberOfcities)
    {
        _distances = distances;
        _numberOfCities = numberOfcities;

        //Assign the min cost to zero
        _minimumCost = 0;
        for (int i = 0; i < numberOfcities; i++) //Set all cities unvisited
            visited[i] = 0;
    }

    void Clear()
    {
        _distances.clear();
        _minimumCost = 0;
        _optimalPath.clear();
    }

    void GenerateMinCost(int cityNumber)
    {
        int i, ncity;
        visited[cityNumber] = 1;

        //Add the city to optimal path
        _optimalPath.push_back(cityNumber + 1);

        ncity = GetLeastOCost(cityNumber);
        if (ncity == INT32_MAX)
        {
            ncity = 0;
            printf("%d", ncity + 1);
            _minimumCost += _distances[cityNumber][ncity];

            return;
        }

        GenerateMinCost(ncity);
    }

    vector<int> GetOptimalPath()
    {
        return _optimalPath;
    }

    int GetMinimumCost()
    {
        return _minimumCost;
    }
};

//End of TSPUsingDynamincProgramming

/**************************************************************************************************************
 * //Whole file function
 * TODO : Need to add the description for implementation
 * 
 * 
 ************************************************************************************************************/
// tsp_dynamic algorithm

/************************************************************************************************************
 * 
 * 
 * TODO : add the description for function
 ***********************************************************************************************************/
bool IsEuclidean(string heursticFunctionType)
{
    //TODO : Need to use the trim for string to handle the edge cases
    transform(heursticFunctionType.begin(), heursticFunctionType.end(), heursticFunctionType.begin(), ::toupper);

    if (heursticFunctionType == "EUCLIDEAN")
        return true;
    else
        return false;
} //End of IsEuclidean() method.

/************************************************************************************************************
 * 
 * 
 * TODO : add the description for function
 ***********************************************************************************************************/
vector<vector<float>> ReadMatrixValues(int length, int width)
{
    //TODO : Can't read the when whole matrix is copied from file to console
    vector<vector<float>> matrix;
    for (int i = 0; i < length; i++)
    {
        vector<float> row;
        float inputReader;
        for (int j = 0; j < width; j++)
        {
            cin >> inputReader;
            row.push_back(inputReader);
        }
        cin.clear();
        matrix.push_back(row);
    }

    return matrix;
}

/************************************************************************************************************
 * 
 * 
 * TODO : add the description for function
 ***********************************************************************************************************/
void PrintMatrixValues(vector<vector<float>> matrix)
{
    for (int i = 0; i < matrix.size(); i++) //Iterate each row
    {
        for (int j = 0; j < matrix[i].size(); j++) // Print each row
        {
            cout << matrix[i][j] << " ";
        }

        cout << endl; //Line break after each row print
    }
} //End of PrintMatricValue() method

/*********************************************** Main() ****************************************************
 *  
 * 
 * TODO : add the description for function
 ***********************************************************************************************************/

int main_Temp()
{
    //Timer to compare the algorithms
    time_t startTime, endTime;

    startTime = clock();
    //Read from input -> heurstic function is euclidean or non-euclidean
    bool isEuclidean;
    string heursticFunctionType;

    //TODO : Need to enble only when it is required
    //cin >> heursticFunctionType;
    //isEuclidean = IsEuclidean(heursticFunctionType);

    //Read the input value from the std in
    int numberOfCities; //No of cities
    cin >> numberOfCities;

    //Read the coordinates values of the cities
    vector<vector<float>> coordinates = ReadMatrixValues(numberOfCities, 2); //width - 2 , only  X and Y coordinates

    //Read the distance values for the cities
    vector<vector<float>> distances = ReadMatrixValues(numberOfCities, numberOfCities); //width - 2 , only  X and Y coordinates

    //2.Dynamic programming
    TSPUsingDynamicProgramming tsp(distances, numberOfCities);
    tsp.GenerateMinCost(0); // Starting of tour from 1st city

    float minimumCost = tsp.GetMinimumCost();
    vector<int> optimalPath = tsp.GetOptimalPath(); // Optimal path city indexes

    cout << "The min cost is : " << minimumCost << endl;

    for (int it = 0; it < optimalPath.size(); it++)
    {
        cout << optimalPath[it] << " ";
    }

    cout << endl
         << "Total time taken is (in seconds): " << (endTime - startTime) << endl;
    //TODO : Need to remove these to print method
    //PrintMatrixValues(distances);
    //PrintMatrixValues(coordinates);

    return 0;
} //End of main method

//Need to include the

int main()
{
    time_t startTime, endTime;

    startTime = clock();

    time_t t;
    srand(time(&t));

    double perfectMin;

    double alpha = 1;         // pheromone importance
    double beta = 1;          // visibility importance
    double evaporation = 0.5; // evaporation rate
    Data d;
    d.GetData();

    ACO colony;
    colony.Init(alpha, beta, evaporation, d);
    colony.run();

    endTime = clock();
    cout << "Total Time taken (in seconds) : " << ((float)(endTime - startTime) / CLOCKS_PER_SEC);
    return 0;
}