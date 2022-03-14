#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int mainpr()
{
	int n;
	cin >> n;
	vector<int> A;
	for (int i = 0; i < n; i++)
	{
		int c;
		cin >> c;
		A.push_back(c);
	}
	sort(A.begin(), A.end());
	for(int i = 0; i < A.size(); i++)
	{
		cout << A[i] << " ";
	}
	return 0;
}