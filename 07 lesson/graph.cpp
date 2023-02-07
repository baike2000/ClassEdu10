#include <iostream>
#include <string>
#include <vector>

using namespace std;

int mainG()
{
	int g[10][10] = {0};
	vector<vector<int>> g1(10);

	g[0][1] = 1;
	g[1][0] = 1;
	g[0][9] = 1;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (g[i][j] == 1)
				g1[i].push_back(j);
			//cout << g[i][j] << " ";
		}
		//cout << endl;
	}
	//cout << endl;

	/*g1[0].push_back(1);
	g1[0].push_back(2);
	g1[2].push_back(3);
	g1[2].push_back(5);
	g1[1].push_back(9);*/

	for (int i = 0; i < g1.size(); i++)
	{
		cout << i << ":";
		for (int j = 0; j < g1[i].size(); j++)
		{
			cout << g1[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}