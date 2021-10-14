
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
 * TODO           :
 *****************************************************************************************************************/
#include <bits/stdc++.h>
#include <iostream>

// User defined header files
#include "../include/SimulatedAnnealing.h"

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
    // TODO : Need to use the trim for string to handle the edge cases
    transform(distanceType.begin(), distanceType.end(), distanceType.begin(), ::toupper);

    if (distanceType == "EUCLIDEAN")
        return true;
    else
        return false;
} // End of IsEuclidean() method.

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
    // TODO : Can't read the when whole matrix is copied from file to console
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
    for (int i = 0; i < matrix.size(); i++) // Iterate each row
    {
        for (int j = 0; j < matrix[i].size(); j++) // Print each row
        {
            cout << matrix[i][j] << " ";
        }

        cout << endl; // Line break after each row print
    }
} // End of PrintMatricValue() method

/*****************************************************************************************************************
 * Function : main()
 *
 * Purpose  : Entry point for the program execution
 ******************************************************************************************************************/
int main()
{
    const clock_t begin_time = clock();
    srand(time(NULL)); // To generates a deterministic sequence of numbers

    TravellingSaleMan travellingSaleMan;
    travellingSaleMan.SimulatedAnnealing();

    cout << "\n\nTime taken to run the genetic algorithm: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " seconds.";
    return 0;
} // End of main method
