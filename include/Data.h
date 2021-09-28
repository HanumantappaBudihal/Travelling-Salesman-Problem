
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

using namespace std;

#ifndef DATA_H
#define DATA_H

//TODO: need to add the comment
class Data
{
    //Member data
public:
    vector<pair<double, double>> cityCoords;
    vector<vector<double>> cost;
    vector<vector<double>> visibility;
    vector<vector<double>> T;
    int N;

    //Member function
    void GetData();
    double GetTourCost(vector<int> C); //TODO : need to change the varible name
    void PrintTour(vector<int> tourCost);
};

#endif
