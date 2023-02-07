#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

int main()
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
	dfs(0);
	used[6] = true;
	vector<int> path;
	int v = 6;
	while (v != 0)
	{
		for (int i = 0; i < n; i++)
		{
			if (used[i])
			{
				for (int j = 0; j < g[i].size(); j++)
				{
					if (g[i][j] == v)
					{
						path.push_back(i);
						v = i;
					}
				}
			}
		}
	}
	for (int i = path.size() - 1; i >= 0; i--)
		cout << path[i] << " ";
	return 0;
}

/*
4 2
0 1
2 3

7 8
0 1
0 2
1 3
2 3
2 4
2 5
5 4
5 6

*/