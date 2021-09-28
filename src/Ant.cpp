#include <cmath>
#include <set>
#include <vector>

//User defined header
#include "../include/Data.h"
#include "../include/Ant.h"

Ant ::Ant(double a, double b, Data *data)
{
    d = *data;
    alpha = a;
    beta = b;
    trail.push_back(1); // always start from the nest (1)
    for (int i = 2; i <= d.N; i++)
    {
        available.insert(i);
    }
}
void Ant ::reset()
{
    vector<int> L;
    L.push_back(1);
    trail = L; // reset to nest.
    for (int i = 2; i <= d.N; i++)
    {
        available.insert(i);
    }
}

void Ant ::deposit()
{
    double tourCost = d.GetTourCost(trail);
    int Q = 100;
    double depositAmount = Q / tourCost;
    int l = trail.size();
    l = l - 1;
    for (int i = 0; i < l; i++)
    {
        d.T[trail[i]][trail[i + 1]] += depositAmount;
    }
    d.T[trail[l]][trail[0]] += depositAmount;
}

vector<int> Ant ::stop()
{
    deposit();
    vector<int> temp = trail;
    reset();
    return temp;
}

void Ant ::step()
{
    int currentCity = trail[trail.size() - 1];
    double norm = probabilityNorm(currentCity);
    double p, gp;
    bool moved = false;
    double highestProb = 0;
    double cityHighest = 0;
    for (set<int>::iterator i = available.begin(); i != available.end(); i++)
    {
        p = moveProbability(currentCity, *i, norm);
        if (p > highestProb)
        {
            cityHighest = *i;
            highestProb = p;
        }
        gp = getRand();
        if (gp <= p)
        { // move
            moved = true;
            trail.push_back(*i);
            available.erase(i);
            break;
        }
    }
    if (!moved)
    {
        // make a move to the highest available prob city
        // move to cityHighest
        trail.push_back(cityHighest);
        available.erase(cityHighest);
    }
}

double Ant ::getRand()
{
    double p = (rand() / (RAND_MAX + 1.0));
    return p;
}
double Ant ::moveProbability(int i, int j, double norm)
{
    double p = (pow(d.T[i][j], alpha)) * (pow(d.visibility[i][j], beta));
    p /= norm;
    return p;
}

double Ant ::probabilityNorm(int currentCity)
{
    int size = available.size();
    double norm = 0.0;
    for (set<int>::iterator i = available.begin(); i != available.end(); i++)
    {
        norm += (pow(d.T[currentCity][*i], alpha)) * (pow(d.visibility[currentCity][*i], beta));
    }
    return norm;
}