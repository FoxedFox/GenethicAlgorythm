#include <iostream>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <fstream>
#include <vector>
using namespace std;

vector<string> formazioneRandom(int* weight, int* value, int maxWeight, int N, int count)
{
	vector<string> form;
	int rnd;

	for (int i = 0; i < count; i++)
	{
		string str = "";
		for (int j = 0; j < N; j++)
		{
			rnd = rand() % 100 + 1;
			if (rnd < 30) str = str + '1';
			else str = str + '0';
		}
		form.push_back(str);
	}
	return form;

}
vector<string> formazione_avida(int* weight, int* value, int maxWeight, int N, int count)
{
	vector<string> form;
	int rnd;
	for (int i = 0; i < count; i++)
	{
		int sum = 0;
		int Q = 0;
		int number;
		string str = "";
		for (int j = 0; j < N; j++) str = str + '0';
		rnd = rand() % N;
		str[rnd] = '1';
		sum = weight[rnd];
		Q = value[rnd];
		for (int j = 0; j < N - 1; j++)
		{
			int max = 0;
			number = -1;
			for (int k = 0; k < N; k++)
				if (value[k] > max && str[k] == '0')
				{
					max = value[k];
					number = k;
				}
			if (sum + weight[number] <= maxWeight)
			{
				sum = sum + weight[number];
				Q = Q + value[number];
				str[number] = '1';
			}
			else break;
		}
		form.push_back(str);
	}
	return form;
}
int getWQ(string str, int* arr)
{
	int W = 0;
	for (int i = 0; i < str.size(); i++)
		if (str[i] == '1') W = W + arr[i];
	return W;
}
string kros(string par1, string par2)
{
	string child = "";
	int rnd = rand() % 2;
	if (rnd == 0)
	{
		int rnd2 = rand() % par1.size();
		for (int i = 0; i < rnd2; i++)
			child = child + par1[i];
		for (int i = rnd2; i < par2.size(); i++)
			child = child + par2[i];
	}
	else
	{
		for (int i = 0; i < par1.size(); i++)
		{
			int rnd2 = rand() % 2;
			if (rnd2 == 0) child = child + par1[i];
			else child = child + par2[i];
		}
	}
	return child;
}
int equally(string str1, string str2)
{
	int F = 0;
	for (int i = 0; i < 1; i++)
		if (str1[i] != str2[i]) F++;
	if (F == 0) return -1;
	else return F;
}
string mutation(string str)//"." and "saltation?"
{
	int rnd = rand() % 2;
	if (rnd == 0)
	{
		int rnd2 = rand() % str.size();
		if (str[rnd2] == '1') str[rnd2] = '0';
		else str[rnd2] = '1';
	}
	else
	{
		int rnd2 = rand() % (str.size() / 2) + 1;
		char tmp;
		tmp = str[rnd2];
		str[rnd2] = str[str.size() - rnd2];
		str[str.size() - rnd2] = tmp;
	}
	return str;
}
int main()
{
	srand(time(NULL));
	int N = 15, maxWeight = 0, PopulationAlgorythm, StartPopulation, PopCount;
	vector<int> Q;
	vector<int> W;
	vector<string> population;
	int max = 0, weight_max = 0;
	string str_max;
	int* S, * weight, * value;
	S = new int[N];
	weight = new int[N];
	value = new int[N];
	ifstream in("1234.txt");
	if (in.is_open())
	{
		in >> maxWeight;
		for (int i = 0; i < N; i++)
		{
			in >> value[i];
			in >> weight[i];
		}
	}
	else exit(1);
	in.close();
	std::cout <<"Max weight"<<endl<< maxWeight << endl;
	std::cout << "Number, value and weight" << endl;
	for (int i = 0;i < N;i++)
	{
		std::cout << "№"<<i+1<< "         "<< value[i] << "         " << weight[i]<<endl;
	}
	std::cout << "How many individuals on start?\n";
	std::cin >> StartPopulation;
	std::cout << "Select population algorythm:\n1)Random\n2)Greedy algorythm\n";
	cin >> PopulationAlgorythm;
	switch (PopulationAlgorythm)
	{
	case 1:
		population = formazioneRandom(weight, value, maxWeight, N, StartPopulation);
		break;
	case 2:
		population = formazione_avida(weight, value, maxWeight, N, StartPopulation);
		break;
	}


	std::cout << "\nGenerated population: \n";
	for (int i = 0; i < population.size(); i++)
	{
		Q.push_back(0);
		cout << population[i];
		int popweight = getWQ(population[i], weight);
		if (popweight >maxWeight) Q[i] = 0;
		else Q[i] = getWQ(population[i], value);
		W.push_back(popweight);
		if (Q[i] > max)
		{
			max = Q[i];
			weight_max = W[i];
			str_max = population[i];
		}
		cout << " Criteria: " << Q[i] << " Weight: " << W[i] << endl;
	}
	std::cout << "Write count of populations:\n";
	std::cin >> PopCount;
	int ost = 0;
	for (int i = 0; i < PopCount; i++)
	{
		ost++;
		cout << "Generation: " << i + 1 << "\n Solution at now: " << str_max << "Criteria: " << max << " Weight: " << weight_max << endl;
		vector<string> potomki;
		vector<int> ChildValue;
		vector<int> ChildWeight;
		vector<int> mutants;
		cout << "Population at now: " << endl;
		for (int j = 0; j < population.size(); j++)
			cout << population[j] << " Criteria: " << Q[j] << " Weight: " << W[j] << endl;
		cout << "The parents: " << endl;

		for (int j = 0; j < rand() % 3 + population.size(); j++)
		{
			if (rand() % 100 > 98) continue;
			string par1 = "", par2 = "";
			int rnd1 = rand() % 2;
			if (rnd1 == 0)
			{
				int rnd2 = rand() % population.size();
				int rnd3 = rand() % population.size();
				if (rnd2 == rnd3)
					if (rnd2 + 1 < population.size()) rnd2++;
					else rnd2--;
				par1 = population[rnd2];
				par2 = population[rnd3];
			}
			else
			{
				int rnd2 = rand() % population.size();
				par1 = population[rnd2];
				int min = 15;
				for (int k = 0; k < population.size(); k++)
					if (equally(par1, population[k]) < min && equally(par1, population[k]) > 0)
					{
						min = equally(par1, population[k]);
						par2 = population[k];
						
					}
				if (par2 == "") par2 = par1;
			}
			for (int k = 0; k < rand() % 2 + 1; k++)
			{
				string tmp = kros(par1, par2);
				potomki.push_back(tmp);
			}
			cout << par1 << " + " << par2 << endl;
			
	     }			
		    cout << "Children: " << endl;
			for (int j = 0; j < potomki.size(); j++)
			{
				ChildValue.push_back(0);
				cout << potomki[j];
				int popweight = getWQ(potomki[j], weight);
				if (popweight > maxWeight) ChildValue[j] = 0;
				else ChildValue[j] = getWQ(potomki[j], value);
				ChildWeight.push_back(popweight);
				cout << " Criteria: " << ChildValue[j] << " Weight: " << ChildWeight[j] << endl;
			}


			cout << "Mutants: " << endl;
			for (int j = 0; j < potomki.size(); j++)
			{
				int rnd = rand() % 100;
				if (rnd < 20)
				{
					potomki[j] = mutation(potomki[j]);
					int popweight = getWQ(potomki[j], weight);
					if (popweight > maxWeight) ChildValue[j] = 0;
					else ChildValue[j] = getWQ(potomki[j], value);
					ChildWeight[j] = popweight;
					mutants.push_back(j);
				}
			}
			for (int j = 0; j < mutants.size(); j++)
				cout << potomki[mutants[j]] << " Criteria: " << ChildValue[mutants[j]] << " Weight: " << ChildWeight[mutants[j]] << endl;
			for (int j = 0; j < potomki.size(); j++)
				if (ChildValue[j] > max)
				{
					ost = 0;
					max = ChildValue[j];
					str_max = potomki[j];
					weight_max = ChildWeight[j];
				}
			population[0] = str_max;
			Q[0] = max;
			W[0] = weight_max;
			vector<int> rang;
			for (int j = 0; j < potomki.size(); j++)
				rang.push_back(0);
			int sum = 0;

			for (int j = 0; j < potomki.size(); j++)
			{
				int max = 0, number = 0;
				for (int k = 0; k < potomki.size(); k++)
					if (ChildValue[k] >= max && rang[k] == 0)
					{
						max = ChildValue[k];
						number = k;
					}
				rang[number] = j + 1;
				sum = sum + max;
			}

			vector<float> proc;
			for (int j = 0; j < potomki.size(); j++)
				proc.push_back((float)ChildValue[j] / sum);
			for (int j = 1; j < population.size(); j++)
			{
				int rnd = rand() % 2;
				if (rnd == 0)// proportional
				{
					for (int k = 0; k < potomki.size(); k++)
					{
						float rnd2 = (float)(rand() % 100) / 100;
						if (proc[k] > rnd2)
						{
							if (ChildValue[k] == 0) continue;
							population[j] = potomki[k];
							Q[j] = ChildValue[k];
							W[j] = ChildWeight[k];
							proc[k] = -1;
							break;
						}
					}
				}
				else// ranged
				{
					for (int k = 0; k < potomki.size(); k++)
					{
						int n1 = 0, n2 = 1;
						float rnd2 = (float)(rand() % 100) / 100;
						if (rang[k] == 0) continue;
						if ((float)(n1 + (n2 - n1) * (rang[k] - 1) / ((population.size() - 1)) / population.size()) > rnd2)
						{
							if (ChildValue[k] == 0) continue;
							population[j] = potomki[k];
							Q[j] = ChildValue[k];
							W[j] = ChildWeight[k];
							proc[k] = -1;
							break;
						}
					}
				}
			}
			
			for (int j = 0;j < population.size();j++)
			{
				std::cout <<"===="<< population[j]<<endl;
				if (W[j] > maxWeight)
				{
					population.erase(population.begin()+j);
					Q.erase(Q.begin() + j);
					W.erase(W.begin() + j);

				}
				std::cout <<"====="<< population[j]<<endl;
			}
			
	}
	cout << "\n\n\n";
	cout << "Solution: " << str_max << " Criteria: " << max << " Weight: " << weight_max << endl;
	cin >> N;
}