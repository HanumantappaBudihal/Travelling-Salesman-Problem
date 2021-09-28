#include <cmath>
#include <set>
#include <vector>
#include <stdio.h>

#include "../include/Data.h"

using namespace std;

void Data::GetData()
{
    scanf("%d", &N);

    // index from 1
    cityCoords.push_back(make_pair(0, 0));
    vector<double> L, M, U;
    cost.push_back(L);
    T.push_back(M);
    visibility.push_back(U);

    for (int i = 0; i < N; i++)
    {
        double x, y;
        scanf("%lf%lf", &x, &y);
        cityCoords.push_back(make_pair(x, y));
    }

    for (int i = 0; i < N; i++)
    {
        vector<double> V(N + 1);
        vector<double> t(N + 1);
        vector<double> l(N + 1);
        for (int j = 1; j <= N; j++)
        {
            scanf("%lf", &V[j]);
            t[j] = 1.0;
            if (V[j] != 0)
            {
                l[j] = 1 / V[j];
            }
        }
        cost.push_back(V);
        T.push_back(t);
        visibility.push_back(l);
    }
}

double Data::GetTourCost(vector<int> C)
{
    int l = C.size();
    double tourCost = 0.0;
    l = l - 1;
    for (int i = 0; i < l; i++)
    {
        tourCost += cost[C[i]][C[i + 1]];
    }
    tourCost += cost[C[l]][C[0]];
    return tourCost;
}

void Data::PrintTour(vector<int> C)
{
    for (int i = 0; i < C.size(); i++)
        printf("%d ", C[i]);
    printf("\n");
}
