
/******************************************************************************************************************
 * File           : GenericAlgorithm.cpp 
 * 
 * Purpose        : Implementation of the travelling saleman problem using genetic algorithm
 * 
 * Author         : Hanumantappa Budihal 
 * Date           : 30-09-2021
 * 
 * Bugs Log       :
 * 
 * Change Log     : Initial Creation : 30-09-2021
 *****************************************************************************************************************/

#include <bits/stdc++.h>

//User defined header file
#include "../include/Data.h"
#include "../include/GeneticAlgorithm.h"

using namespace std;

/*****************************************************************************************************************
 * Purpose  : 
 * 
 * Inputs   :
 * Outputs  :      
 * TODO     : Need to add the proper comments
 ******************************************************************************************************************/
struct sort_pred
{
    bool operator()(const my_pair &firstElem, const my_pair &secondElem)
    {
        return firstElem.second < secondElem.second;
    }
};

/*****************************************************************************************************************
 * Function : GeneticAlgorithm (Constructor)
 * 
 * Purpose  : Create the instane of GeneticAlgorithm with intial data * 
 * Inputs   :  Data, size of population  and mutation rate         
 ******************************************************************************************************************/
GeneticAlgorithm::GeneticAlgorithm(Data *data, int sizePopulation, int mutationRate)
{
    this->data = data;
    this->size_population = sizePopulation;
    this->real_size_population = 0;
    this->mutation_rate = mutationRate;
} //End of Constructor

/*****************************************************************************************************************
 * Function : IsValidSolution
 * 
 * Purpose  : Verify the solution is valid or not.
 * 
 * Inputs   : Solution
 * Outputs  : return total cost of the valid if solution is valid
 *                   else -1      
 ******************************************************************************************************************/
float GeneticAlgorithm::IsValidSolution(vector<int> &solution)
{
    float totalCost = 0;
    set<int> setSolution;

    for (int i = 0; i < data->_size; i++)
        setSolution.insert(solution[i]);

    if (setSolution.size() != (unsigned)data->_size)
        return -1;

    for (int i = 0; i < data->_size; i++)
    {
        if (i + 1 < data->_size)
        {
            float cost = data->GetEdgeCost(solution[i], solution[i + 1]);
            if (cost == -1)
                return -1;
            else
                totalCost += cost;
        }
        else
        {
            float cost = data->GetEdgeCost(solution[i], solution[0]);
            if (cost == -1)
                return -1;
            else
                totalCost += cost;
            break;
        }
    }

    return totalCost;
}

/*****************************************************************************************************************
 * Function : IsChromosomeExists
 * 
 * Purpose  : This method verifies the chromosome exits
 * 
 * Inputs   :
 * Outputs  :      
 * TODO     : Need to add the proper comments        
 ******************************************************************************************************************/
bool GeneticAlgorithm::IsChromosomeExists(const vector<int> &v)
{
    for (vector<pair<vector<int>, float>>::iterator it = population.begin(); it != population.end(); ++it)
    {
        const vector<int> &vec = (*it).first;
        if (equal(v.begin(), v.end(), vec.begin()))
            return true;
    }
    return false;
}

/*****************************************************************************************************************
 * Function : initialPopulation()
 * 
 * Purpose  : 
 * 
 * Inputs   :
 * Outputs  :      
 * TODO     : Need to add the proper comments
 ******************************************************************************************************************/
void GeneticAlgorithm::initialPopulation() //Private method
{
    vector<int> parent;
    parent.push_back(data->_initialVertex);

    for (int i = 0; i < data->_size; i++)
    {
        if (i != data->_initialVertex)
            parent.push_back(i);
    }

    float totalCost = IsValidSolution(parent);
    population.push_back(make_pair(parent, totalCost));
    real_size_population++;

    for (int i = 0; i < 10000 && real_size_population != size_population; i++)
    {
        random_shuffle(parent.begin() + 1, parent.begin() + (rand() % (data->_size - 1) + 1));

        float total_cost = IsValidSolution(parent);

        if (!IsChromosomeExists(parent))
        {
            population.push_back(make_pair(parent, total_cost));
            real_size_population++;
        }
    }

    sort(population.begin(), population.end(), sort_pred());
}

/*****************************************************************************************************************
 * Function : InsertBinarySearch
 * 
 * Purpose  : 
 * 
 * Inputs   :
 * Outputs  :      
 * TODO     : Need to add the proper comments    
 ******************************************************************************************************************/
void GeneticAlgorithm::InsertBinarySearch(vector<int> &child, float total_cost)
{
    int minimum = 0;
    int maxmum = real_size_population - 1;

    while (maxmum >= minimum)
    {
        int middle = minimum + (maxmum - minimum) / 2;
        if (total_cost == population[middle].second)
        {
            population.insert(population.begin() + middle, make_pair(child, total_cost));
            return;
        }
        else if (total_cost > population[middle].second)
            minimum = middle + 1;
        else
            maxmum = middle - 1;
    }

    population.insert(population.begin() + minimum, make_pair(child, total_cost));
}

/*****************************************************************************************************************
 * Function : CrossOver()
 * 
 * Purpose  : Apply the cross over algorithm to create the childre
 * 
 * Inputs   :
 * Outputs  :      
 * TODO     : Need to add the proper comments       
 ******************************************************************************************************************/
void GeneticAlgorithm::CrossOver(vector<int> &parent1, vector<int> &parent2)
{
    vector<int> child1, child2;
    map<int, int> genes1, genes2;

    for (int i = 0; i < data->_size; i++)
    {
        genes1[parent1[i]] = 0;
        genes2[parent2[i]] = 0;
    }

    int point1 = rand() % (data->_size - 1) + 1;
    int point2 = rand() % (data->_size - point1) + point1;

    if (point1 == point2)
    {
        if (point1 - 1 > 1)
            point1--;
        else if (point2 + 1 < data->_size)
            point2++;
        else
        {
            int point = rand() % 10 + 1;
            if (point <= 5)
                point1--;
            else
                point2++;
        }
    }

    for (int i = 0; i < point1; i++)
    {
        child1.push_back(parent1[i]);
        child2.push_back(parent2[i]);
        genes1[parent1[i]] = 1;
        genes2[parent2[i]] = 1;
    }

    for (int i = point2 + 1; i < data->_size; i++)
    {
        genes1[parent1[i]] = 1;
        genes2[parent2[i]] = 1;
    }

    for (int i = point2; i >= point1; i--)
    {
        if (genes1[parent2[i]] == 0)
        {
            child1.push_back(parent2[i]);
            genes1[parent2[i]] = 1;
        }
        else
        {
            for (map<int, int>::iterator it = genes1.begin(); it != genes1.end(); ++it)
            {
                if (it->second == 0)
                {
                    child1.push_back(it->first);
                    genes1[it->first] = 1;
                    break;
                }
            }
        }

        if (genes2[parent1[i]] == 0)
        {
            child2.push_back(parent1[i]);
            genes2[parent1[i]] = 1;
        }
        else
        {
            for (map<int, int>::iterator it = genes2.begin(); it != genes2.end(); ++it)
            {
                if (it->second == 0)
                {
                    child2.push_back(it->first);
                    genes2[it->first] = 1;
                    break;
                }
            }
        }
    }

    for (int i = point2 + 1; i < data->_size; i++)
    {
        child1.push_back(parent1[i]);
        child2.push_back(parent2[i]);
    }

    int mutation = rand() % 200 + 1;

    if (mutation <= mutation_rate)
    {
        int index_gene1, index_gene2;
        index_gene1 = rand() % (data->_size - 1) + 1;
        index_gene2 = rand() % (data->_size - 1) + 1;

        swap(child1[index_gene2], child1[index_gene1]);
        swap(child2[index_gene1], child2[index_gene2]);
    }

    float total_cost_child1 = IsValidSolution(child1);
    float total_cost_child2 = IsValidSolution(child2);
    if (!IsChromosomeExists(child1))
    {
        InsertBinarySearch(child1, total_cost_child1);
        real_size_population++;
    }

    if (!IsChromosomeExists(child2))
    {
        InsertBinarySearch(child2, total_cost_child2);
        real_size_population++;
    }
}

/*****************************************************************************************************************
 * Function : Run()
 * 
 * Purpose  : 
 * 
 * Inputs   :
 * Outputs  :      
 * TODO     : Need to add the proper comments
 ******************************************************************************************************************/

void GeneticAlgorithm::Run()
{
    initialPopulation();
    if (real_size_population == 0)
        return;

    float best = population[0].second;

    int i = 0;
    while (i >= 0)
    {
        int old_size_population = real_size_population;
        if (real_size_population >= 2)
        {
            if (real_size_population == 2)
            {
                CrossOver(population[0].first, population[1].first);
            }
            else
            {
                int parent1, parent2;
                do
                {
                    parent1 = rand() % real_size_population;
                    parent2 = rand() % real_size_population;
                } while (parent1 == parent2);
                CrossOver(population[parent1].first, population[parent2].first);
            }
            int diff_population = real_size_population - old_size_population;

            if (diff_population == 2)
            {
                if (real_size_population > size_population)
                {
                    population.pop_back();
                    population.pop_back();

                    real_size_population -= 2;
                }
            }
            else if (diff_population == 1)
            {
                if (real_size_population > size_population)
                {
                    population.pop_back();
                    real_size_population--;
                }
            }
        }
        else
        {
            CrossOver(population[0].first, population[0].first);
            if (real_size_population > size_population)
            {
                population.pop_back();
                real_size_population--;
            }
        }
        if (i == 0)
        {
            best = population[0].second;
            const vector<int> &vec = population[0].first;
            //cout << "Tour : " << endl;
            cout << endl;
            for (int i = 0; i < data->_size; i++)
                cout << vec[i] << " ";

            //cout << " | Cost: " << population[0].second;
            cout << endl;
        }
        else if (i % 100 == 0 && best > population[0].second)
        {
            best = population[0].second;
            const vector<int> &vec = population[0].first;
            //cout << "Tour : " << endl;
            cout << endl;

            for (int i = 0; i < data->_size; i++)
                cout << vec[i] << " ";

            //cout << " | Cost: " << population[0].second;
            cout << endl;
        }

        i++;
    }

    cout << "\nBest solution: " << endl;
    const vector<int> &vec = population[0].first;
    for (int i = 0; i < data->_size; i++)
        cout << vec[i] << " ";
    cout << " | Cost: " << population[0].second << endl;
}
