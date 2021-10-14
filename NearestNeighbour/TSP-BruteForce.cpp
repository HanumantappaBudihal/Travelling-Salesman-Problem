/*

CPE 593:	TSP brute force solution.
Author:		Jinglong
Date:		April 8th.

*/

#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<time.h>

using namespace std;

// map with every routine weight
// routine weight to itself is defined as 0
vector<vector<int> > map;

vector<bool> used;
vector<int> name;
string s;

// total number of node
int n;
int start,mstart;
int mmm=2147483647; // set min as biggest <int>
string mmmrout="";


void input()
{
	int temp;
	ifstream inf("TSP9.txt");
	inf >> n;
	for (int i = 0; i < n; i++)
	{
		map.push_back(vector<int>());
		used.push_back(false);
//		name.push_back(65 + i);   // Node name as A-Z
		name.push_back(49 + i);   // Node name as 1-.....
		for (int j = 0; j < n; j++)
		{
			inf >> temp;
			map[i].push_back(temp);
		}
	}
	inf.close();
}

void output(string rout,int weight,int last){
	//list all routine with weight;
	//cout << rout <<start+1<< ' ' << weight<<endl;
	weight += map[last][start];
	if (weight < mmm)
	{
		mmm = weight;
		mmmrout = rout;
		mstart = start;
	}
}

void tspbf(int sour, int des,int count,int weight, string rout)
{
	used[des] = true;
	count++;
	weight += map[sour][des];
	rout += name[des];
	if (count == n-1) 
	{ output(rout,weight,des); return; }
	for (int i = 0; i < n; i++)
	{
		if (used[i] == false && map[des][i]>0)
		{
			tspbf(des, i, count, weight, rout);
			used[i] = false;
		}
	}
	used[des] = false;
}

void reset(int sour)
{
	for (int i = 0; i < n; i++)
		used[i] = false;
	used[sour] = true;
	s = "";
}




int main() {

	clock_t startt, finish;
	double totaltime;
	srand(time(NULL));

	input();
	startt = clock();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{		
			if (map[i][j]>0)
			{
				start = i;
				//reset the routine as empty and all note not used. except i.
				reset(i);
				s += name[i];
				tspbf(i, j, 0, 0, s);
			}
	}
	cout << mmmrout <<mstart+1<< ' ' << mmm << endl;
	finish = clock();
	totaltime = ((double)(finish - startt) / CLOCKS_PER_SEC);
	cout << endl << "  Running Time:" << totaltime << " seconds." << endl;

	return 0;
}