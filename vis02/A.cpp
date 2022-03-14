#include<iostream>
#include<vector>

using namespace std;

int main()
{
	int n, m, w;
	cin >> n >> m;
	vector<vector<int>> v(n);
	for (int i = 0; i < m; i++)
	{
		vector<int> vc(m, 0);
		v[i] = vc;
	}
	cin >> w;
	for (int i = 0; i < w; i++)
	{
		int x, y;
		cin >> x >> y;
		v[x][y] = -1;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (v[i][j] != -1)
			{
				
			}
		}
	}
	return 0;
}
