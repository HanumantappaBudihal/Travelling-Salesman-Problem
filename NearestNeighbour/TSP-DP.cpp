
#include <iostream>
#include <set>
#include <vector>
#include<fstream>
#include<time.h>


using namespace std;

int n;
vector<vector<int> > dis; // adjacent matrix

typedef struct
{
	int curcity;// current city
	vector<int> unvisited;// unvisited cities
	set<int> type;// set is ordered vector
	int distance;// the distance go from 
}status;

/* testing print */
void printVec(vector<status> vec)
{
	vector<status>::iterator iter;
	vector<int>::iterator it;
	for (iter = vec.begin(); iter != vec.end(); iter++)
	{
		cout << (*iter).curcity << " <";
		for (it = (*iter).unvisited.begin(); it != (*iter).unvisited.end(); it++)
		{
			cout << *it << " ";
		}
		cout << ">" << "  distance:" << (*iter).distance << endl;
	}

}
//to check if there is City I in current status
bool contain(int i, status &sta)
{
	vector<int>::iterator iter;
	if (i == sta.curcity)
		return true;
	else
	{
		for (iter = sta.unvisited.begin(); iter != sta.unvisited.end(); iter++)
			if (i == *iter)
				return true;
	}
	return false;
}
/* Combining the same status*/
vector<status> combine(vector<status> vec)
{
	vector<status> new_vec;
	vector<status>::iterator iter;
	status temp;
	while (vec.size()>0)
	{
		iter = vec.begin();
		temp = *iter;
//		vec.erase(iter);
		for (; iter != vec.end(); iter++)
		{
			if ((temp.curcity == (*iter).curcity) && (temp.type == (*iter).type))
			{
				if ((*iter).distance<temp.distance)
					temp = *iter;
				iter = vec.erase(iter);
				iter--;

			}
		}
		new_vec.push_back(temp);
	}
	return new_vec;
}

/* Input of adjacency matrix */
void input()
{
	int temp;
	ifstream inf("TSP9.txt");
	inf >> n;
	for (int i = 0; i < n; i++)
	{
		dis.push_back(vector<int>());
		for (int j = 0; j < n; j++)
		{
			inf >> temp;
			dis[i].push_back(temp);
		}

	}
	inf.close();
}

int main()
{
	input();

	clock_t start, finish;
	double totaltime;
	srand(time(NULL));
	start = clock();

	vector<status> pre_vector;
	vector<status> cur_vector;
	//Initialization
	for (int i = 1; i<n; i++)
	{
		status sta;
		sta.curcity = i;
		sta.distance = dis[i][0];
		cur_vector.push_back(sta);
	}
	//Recursion, n-2 times
	for (int j = 0; j<n - 2; j++) {
		pre_vector = cur_vector;
		cur_vector.clear();

		for (int i = 1; i<n; i++)
		{
			vector<status>::iterator iter;
			for (iter = pre_vector.begin(); iter != pre_vector.end(); iter++)
			{
				status temp = *iter;
				if (contain(i, temp) == false)// to make sure there is no duplicated routine
				{
					status new_stat = temp;
					vector<int>::iterator int_iter = new_stat.unvisited.begin();
					new_stat.unvisited.insert(int_iter, new_stat.curcity);
					new_stat.type.insert(new_stat.curcity);
					new_stat.distance += dis[i][new_stat.curcity];
					new_stat.curcity = i;
					cur_vector.push_back(new_stat);
				}
			}
		}
		// record shortest path and combine same status
		cur_vector = combine(cur_vector);
	}


	 //printVec(cur_vector);


	// after recursion, last step is calculate dist[lastVertex][startVertex],
	// then add on cost to get final result of shortest routine
	vector<status>::iterator iter = cur_vector.begin();
	status shortest = *iter;
	int min_dis = shortest.distance + dis[0][shortest.curcity];
	iter++;
	for (; iter != cur_vector.end(); iter++)
	{
		int temp_dis = dis[0][(*iter).curcity] + (*iter).distance;
		if (temp_dis<min_dis)
		{
			min_dis = temp_dis;
			shortest = *iter;
		}
	}

	finish = clock();
	
	// Printing
	vector<int>::iterator iter_city;
	cout << "minimum distance is " << min_dis << endl;
	cout << "the shortest path is " << "1 " << shortest.curcity + 1;
	for (iter_city = shortest.unvisited.begin(); iter_city != shortest.unvisited.end(); iter_city++)
		cout << " " << *iter_city + 1;
	cout << " 1" << endl;

	totaltime = ((double)(finish - start) / CLOCKS_PER_SEC*1000.0);
	cout << endl << "  Running Time:" << totaltime << " milliseconds." << endl;
	return 0;
}
