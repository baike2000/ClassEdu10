#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int>> A(n);
	for (int i = 0; i < A.size(); i++)
	{
		for (int j = 0; j < m; j++)
		{
			int c;
			cin >> c;
			A[i].push_back(c);
		}
	}
	for (int i = 0; i < A.size(); i++)
	{
		sort(A[i].begin(), A[i].end());
		for (int j = 0; j < A[i].size(); j++)
		{
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}