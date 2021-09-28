#include <vector>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <set>
#include <iostream>

using namespace std;

class Data
{
public:
    vector<pair<double, double>> CityCoordinates; //TODO : we are not using this data;
    vector<vector<double>> CostMatrix;
    vector<vector<double>> Visibilities;
    vector<vector<double>> Pheromones; //TODO : Need to change it
    int NumberOfCities;

    Data()
    {
        string isEuclidean; // Present implementation is not using this data
        cin >> isEuclidean;

        cin >> NumberOfCities;

        //This is just small adjustment to indexing access.
        // Index from 1, not from zero in this implementation for below 4 matrix data.
        CityCoordinates.push_back(make_pair(0, 0));
        vector<double> dummyData;
        CostMatrix.push_back(dummyData);
        Pheromones.push_back(dummyData);
        Visibilities.push_back(dummyData);

        //Read cities coordinates matrix from stdin
        for (int i = 1; i <= NumberOfCities; i++)
        {
            double x, y;
            scanf("%lf%lf", &x, &y);
            CityCoordinates.push_back(make_pair(x, y)); // Not using it anywhere
        }

        for (int i = 1; i <= NumberOfCities; i++)
        {
            vector<double> costOfRowElements(NumberOfCities + 1); //Read the distance each element in row and add to distance CostMatrix
            vector<double> pheromoneOfRowElements(NumberOfCities + 1);
            vector<double> visibilityOfRowElements(NumberOfCities + 1);

            for (int j = 1; j <= NumberOfCities; j++)
            {
                scanf("%lf", &costOfRowElements[j]);
                pheromoneOfRowElements[j] = 1.0; //Initially update the pheromone of the edges by 1

                if (costOfRowElements[j] != 0) //if distance is not zero,i.e if there is no wall and path to other node is exists
                {
                    // Visibilities tell us , Shortest path more likely to have more phoremone
                    // (1/ edge distance) -> shortest path has more chance choosing while ant travelling
                    visibilityOfRowElements[j] = 1 / costOfRowElements[j];
                }
            }

            CostMatrix.push_back(costOfRowElements); // Add the row data to respective matrixies
            Pheromones.push_back(pheromoneOfRowElements);
            Visibilities.push_back(visibilityOfRowElements);
        }
    }

    double GetTourCost(vector<int> C)
    {
        int l = C.size();
        double tourCost = 0.0;
        l = l - 1;
        for (int i = 0; i < l; i++)
        {
            tourCost += CostMatrix[C[i]][C[i + 1]];
        }

        tourCost += CostMatrix[C[l]][C[0]];
        return tourCost;
    }

    void print(vector<int> C)
    {
        for (int i = 0; i < C.size(); i++)
            printf("%d ", C[i]);
        printf("\n");
    }
};

Data d; // global data construct

class Ant
{
public:
    vector<int> trail;
    set<int> available;

    double alpha; // importance of the pheromone level
    double beta;  // importance of the Visibilities

    Ant(double _alpha, double _beta)
    {
        alpha = _alpha;
        beta = _beta;
        trail.push_back(1); // always start from the nest (1)

        for (int i = 2; i <= d.NumberOfCities; i++)
        {
            available.insert(i);
        }
    }

    void reset()
    {
        vector<int> L;
        L.push_back(1);
        trail = L; // reset to nest.

        for (int i = 2; i <= d.NumberOfCities; i++)
        {
            available.insert(i);
        }
    }

    void deposit()
    {
        double tourCost = d.GetTourCost(trail);
        int Q = 100;

        double depositAmount = Q / tourCost;
        int l = trail.size();
        l = l - 1;

        for (int i = 0; i < l; i++)
        {
            d.Pheromones[trail[i]][trail[i + 1]] += depositAmount;
        }

        d.Pheromones[trail[l]][trail[0]] += depositAmount;
    }

    vector<int> stop()
    {
        deposit();
        vector<int> temp = trail;
        reset();
        return temp;
    }

    void step()
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

    double getRand()
    {
        double p = (rand() / (RAND_MAX + 1.0));
        return p;
    }

    double moveProbability(int i, int j, double norm)
    {
        double p = (pow(d.Pheromones[i][j], alpha)) * (pow(d.Visibilities[i][j], beta));
        p /= norm;
        return p;
    }

    double probabilityNorm(int currentCity)
    {
        int size = available.size();
        double norm = 0.0;
        for (set<int>::iterator i = available.begin(); i != available.end(); i++)
        {
            norm += (pow(d.Pheromones[currentCity][*i], alpha)) * (pow(d.Visibilities[currentCity][*i], beta));
        }

        return norm;
    }
};

class AntColonyOptimization
{
public:
    int NumberOfCities; // cities
    int M;              // no.of ants
    vector<Ant> ant;    // ants
    double evaporation; // evaporation rate
    double alpha;       // importance of the pheromone level
    double beta;        // importance of the Visibilities
    vector<int> PATH;

    AntColonyOptimization(double a, double b, double e)
    {
        alpha = a;
        beta = b;
        evaporation = e;
        NumberOfCities = d.NumberOfCities;
        M = NumberOfCities * 2; // ants
                                // M = rand() % NumberOfCities;
        for (int i = 0; i < M; i++)
        {
            Ant a(alpha, beta);
            ant.push_back(a);
        }
    }

    void run()
    {

        double minTour, tourC;
        for (int n = 0; n < 30; n++)
        {
            for (int p = 0; p < (NumberOfCities - 1); p++)
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

            for (int i = 1; i <= NumberOfCities; i++)
            {
                for (int j = 1; j <= NumberOfCities; j++)
                {
                    d.Pheromones[i][j] *= evaporation;
                }
            }
        }

        printf("%lf\n", minTour);
        d.print(PATH);
    }
};

int main(void)
{
    time_t startTime, endTime; // TODO : Need to remove the this code later , execution time for code
    startTime = clock();

    //TODO : Can we move as class member ?
    double alpha = (double)rand() / RAND_MAX;           // Pheromones influence ( range 0-1) //TODO : Need to study more about this ?
    double beta = (double)rand() / RAND_MAX;            // Visibilities influence(range 0-1)
    double evaporationRate = (double)rand() / RAND_MAX; // Evaporation rate ( good value is 0.5)

    AntColonyOptimization colony(alpha, beta, evaporationRate);
    colony.run();

    endTime = clock();
    cout << "Total Time taken (in seconds) : " << ((float)(endTime - startTime) / CLOCKS_PER_SEC);

    return 0;
}
