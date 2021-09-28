#include <vector>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <set>
#include <iostream>

#include "../include/Ant.h"
#include "../include/Data.h"
#include "../include/ACO.h"

using namespace std;

void ACO::Init(double a, double b, double e, Data ds)
{
    alpha = a;
    beta = b;
    evaporation = e;

    d = ds;

    // N = d.N;
    M = 100; // ants //should be parameterized

    for (int i = 0; i < M; i++)
    {
        Ant a(alpha, beta, &d);
        ant.push_back(a);
    }
}

void ACO::run()
{
    vector<int> PATH;
    double minTour, tourC;
    for (int n = 0; n < 30; n++)
    {
        for (int p = 0; p < (N - 1); p++)
        {
            for (int i = 0; i < M; i++)
            {
                ant[i].step();
            }
        }

        for (int i = 0; i < M; i++)
        {
            vector<int> p = ant[i].stop();
            if (!PATH.size())
            {
                PATH = p;
                minTour = d.GetTourCost(p);
                continue;
            }
            tourC = d.GetTourCost(p);
            if (tourC < minTour)
            {
                minTour = tourC;
                PATH = p;
            }
        }
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                d.T[i][j] *= evaporation;
            }
        }
    }

    printf("%lf\n", minTour);
    d.PrintTour(PATH);
}
