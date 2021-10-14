#include<iostream>
#include<vector>
#include<fstream>
#include<time.h>

#include "LKMatrix.h"

vector<int> id; // "No." of vertice
vector<vector<int> > map; // adjacent matrix
vector<int> tour,tt;

int main() {
	int n;
	int temp;
	clock_t start, finish;
	double totaltime;
	srand(time(NULL));

	ifstream inf("TSP300.txt");
	inf >> n;
	for (int i = 0; i < n; i++)
	{
		map.push_back(vector<int>());
		id.push_back(i+1);   // Node name as 1-.....
		for (int j = 0; j < n; j++)
		{
			inf >> temp;
			map[i].push_back(temp);
		}

	}
	inf.close();

	start = clock();

	// initialize tour
	tour = vector<int>(n, 0);

	// use the result of Greedy algo. as input

	ifstream readTour("tour300.txt");
	for (int i = 0; i < n; i++)
	{
			readTour >> temp;
			tt.push_back(temp-1);
	}
	readTour.close();
	// base on the routine we read in tt[], build tour[]
	for (int i = 0; i < n-1; i++) {
		tour[tt[i]] = tt[i+1];
	}

/*
	// if there is no result to be improved, use 'random' one

	// initial 'random' tour
	for (int i = 0; i < n; i++) {
		tour[i] = (i + 1) % n;
	}
*/


	LKMatrix mat(map, id,tour);

	mat.optimizeTour();

	finish = clock();

	cout << mat.getCurrentTourDistance() << endl;
	mat.printTourIds();

	totaltime = ((double)(finish - start) / CLOCKS_PER_SEC*1000.0);
	cout << endl << "  Running Time:" << totaltime << " milliseconds." << endl;

	return 0;
}
