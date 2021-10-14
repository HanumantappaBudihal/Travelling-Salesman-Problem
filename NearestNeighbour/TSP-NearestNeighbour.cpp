#include <stdio.h>
#include <iostream>
#include <stack>
#include <vector>
#include<fstream>

using namespace std;
vector<vector<int> > map;
int distance1;
stack<int> stk;
int numberOfNodes;

vector<bool> used;
vector<int> name;
string s;
int n;

void input()
{
	int temp;
	ifstream inf("TSP.txt");
	inf >> n;
	for (int i = 0; i < n; i++)
	{
		map.push_back(vector<int>());
		used.push_back(false);
		name.push_back(49 + i);
		for (int j = 0; j < n; j++)
		{
			inf >> temp;
			map[i].push_back(temp);
		}
	}
	inf.close();
}

void tsp(vector<vector<int> > map) {
	numberOfNodes = n - 1;
	vector<int> visited(numberOfNodes + 1, 0);
	visited[1] = 1;
	stk.push(1);
	int element = 0;
	int dst;
	int i;
	int min = 2147483647;
	bool minFlag = false;
	cout << 1 + " ";

	while (!stk.empty())
	{
		element = stk.top();
		i = 1;
		min = 2147483647;
		while (i <= n-1)
		{
			if (map[element][i] > 1 && visited[i] == 0)
			{
				if (min > map[element][i])
				{
					min = map[element][i];
					dst = i;
					minFlag = true;
				}
			}
			i++;
		}
		if (minFlag)
		{
			distance1 += map[element][dst];
			visited[dst] = 1;
			stk.push(dst);
			cout << dst + " ";
			minFlag = false;
			continue;
		}
		stk.pop();
	}
}

int main() {
	input();
	tsp(map);
}
