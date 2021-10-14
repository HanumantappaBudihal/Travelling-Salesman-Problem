#include <iostream>
using std::cerr;
using std::endl;
#include <fstream>
#include <math.h>
using std::ofstream;
#include <cstdlib> // for exit function

using namespace std;
int main()
{
    ofstream outdata; // outdata is like cin

    int numberOfCities;
    cin >> numberOfCities; // Read the number of cities

    float coordinates[numberOfCities][2]; // Cities coordinates

    outdata.open("matrixData.txt"); // opens the file
    if (!outdata)
    { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    int sn;
    for (int i = 0; i < numberOfCities; i++)
    {
        cin >> sn >> coordinates[i][0] >> coordinates[i][1];
    }

    outdata << numberOfCities << endl;
    for (int i = 0; i < numberOfCities; i++)
    {
        outdata << coordinates[i][0] << " " << coordinates[i][1] << endl;
    }

    // Read the input matrix data and create the edges to graph
    for (int i = 0; i < numberOfCities; i++)
    {
        float x;
        for (int j = 0; j < numberOfCities; j++)
        {
            x = sqrt(pow(coordinates[j][0] - coordinates[i][0], 2) +       // x2-x1
                     pow(coordinates[j][1] - coordinates[i][1], 2) * 1.0); // y2-y1
            outdata << x << " ";
        }

        outdata << endl;
    }

    outdata.close();

    return 0;
}