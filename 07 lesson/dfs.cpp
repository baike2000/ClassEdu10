#include <iostream>
#include <string>
#include <vector>

using namespace std;
/**
vector<vector<int>> g;
int n, k, m = 0;

vector<bool> used = { 0 };

void dfs(int v)
{
	used[v] = true;
	for (int i = 0; i < g[v].size(); i++)
	{
		if (!used[g[v][i]])
			dfs(g[v][i]);
	}
}

int mainD()
{
	cin >> n >> k;
	g.resize(n);
	used.resize(n);
	for (int i = 0; i < k; i++)
	{
		int p1, p2;
		cin >> p1 >> p2;
		g[p1].push_back(p2);
	}
	for (int i = 0; i < n; i++)
	{
		if (!used[i])
		{
			m++;
			dfs(i);
		}
	}
	cout << m << endl;
	return 0;
}
*/
/*
4 2
0 1
2 3

6 7
0 1
0 2
1 3
2 3
2 4
2 5
5 4
5 6

*/