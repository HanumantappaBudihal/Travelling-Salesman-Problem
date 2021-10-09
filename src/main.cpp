
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
 * 
 * TODO           : 1. Analysis the better algorithm for large input :
 *                    Tried to implement the ACO algo to solve the problme but not able to get the expected output and performance.
 *                   Still looking for better approach :
 * 
 *                      a. ACO - with better improvement (Implemented but need to improve)
 *                      b. ABO - African buffalo optimization looks promising in terms of time complexity and cost
 *                      c. SA
 * 
 *                  2.Comparion Report :
 *                      TSPLIB data comparion report for final implementation
 * 
 *                  3.Implement the Parallel computing to improve the performance 
 *****************************************************************************************************************/
#include <bits/stdc++.h>
#include <iostream>

//User defined header files
#include "../include/GeneticAlgorithm.h"

using namespace std;

/*****************************************************************************************************************
 * Function : IsEuclidean()
 * 
 * Purpose  : Verify the give distance type is ecuclidean or not.
 * 
 * Inputs   : DistanceType
 * Outputs  : if distance type is Euclidean return true 
 *            else false         
 ******************************************************************************************************************/
bool IsEuclidean(string distanceType)
{
    //TODO : Need to use the trim for string to handle the edge cases
    transform(distanceType.begin(), distanceType.end(), distanceType.begin(), ::toupper);

    if (distanceType == "EUCLIDEAN")
        return true;
    else
        return false;
} //End of IsEuclidean() method.

/*****************************************************************************************************************
 * Function : ReadMatrixValues()
 * 
 * Purpose  : Read the matrix data from the stdin
 * 
 * Inputs   : lenght and width of the matrix
 * Outputs  : Return the matrix data which is inputted from stdin        
 ******************************************************************************************************************/
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

/*****************************************************************************************************************
 * Function : PrintMatrixValues()
 * 
 * Purpose  : Print the matrix data to stdout
 * 
 * Inputs   : Matridata
 * Outputs  : Print the matrix data to stdout        
 ******************************************************************************************************************/
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

/*****************************************************************************************************************
 * Function : main()
 * 
 * Purpose  : Entry point for the program execution      
 ******************************************************************************************************************/
int main()
{
    const clock_t begin_time = clock();
    srand(time(NULL)); // To generates a deterministic sequence of numbers

    char distanceType[20];
    int numberOfCities;
    cin.getline(distanceType, 20); //Read distance type ( ecluiden or non ecluidean)
    cin >> numberOfCities;         //Read the number of cities

    Data *data = new Data(numberOfCities, 0);
    float coordinates[numberOfCities][2]; //Cities coordinates

    for (int i = 0; i < numberOfCities; i++)
    {
        cin >> coordinates[i][0] >> coordinates[i][1];
    }

    //Read the input matrix data and create the edges to graph
    for (int i = 0; i < numberOfCities; i++)
    {
        float x;
        for (int j = 0; j < numberOfCities; j++)
        {
            cin >> x;
            data->AddEdge(i, j, x);
        }
    }

    //TODO : Need to analysis these two parameter
    //sizePopulation =  25% if the number of citiies
    //mutationRate = 50% of the number of citiies
    GeneticAlgorithm genetic(data, (numberOfCities * 0.25), (numberOfCities * 0.5));
    genetic.Run();

    cout << "\n\nTime taken to run the genetic algorithm: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " seconds.";
    return 0;
} //End of main method
