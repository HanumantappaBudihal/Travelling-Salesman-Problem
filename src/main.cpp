#include <bits/stdc++.h>
#include <iostream>
#include "../include/GeneticAlgorithm.h"

using namespace std;

int main()
{
    srand(time(NULL));

    string type;
    int N;
    cin >> type;
    cin >> N;
    Graph *graph5 = new Graph(N, 0);
    float coord[N][2];
    for (int i = 0; i < N; i++)
    {
        cin >> coord[i][0] >> coord[i][1];
    }

    for (int i = 0; i < N; i++)
    {
        float x;
        for (int j = 0; j < N; j++)
        {
            cin >> x;
            graph5->AddEdge(i, j, x);
        }
    }

    GeneticAlgorithm genetic(graph5, 20, 100000, 17);

    const clock_t begin_time = clock();
    genetic.Run();
    cout << "\n\nTime for to run the genetic algorithm: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " seconds.";
    return 0;
}
