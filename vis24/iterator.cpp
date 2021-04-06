#include<iostream>
#include<vector>
#include<cmath>
#include<map>
#include<set>
#include<algorithm>

using namespace std;

int main()
{
	vector<int> v = { 1,2,3,4,5,6,7,8,9 };
	for (auto it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
	map<int, string> m = { {1,"one"},{3,"three"},{2,"two"} };
	for (auto it = m.begin(); it != m.end(); it++)
	{
		cout << it->first << " " << it->second << endl;
	}

	for (auto x : m)
	{
		cout << x.first << " " << x.second << endl;
	}
	//vector<int> v1;
	//copy(v.begin(), v.end(), v1);

	//vector<int>::iterator bound;
	auto bound = partition(v.begin(), v.end(), [](int i) {return i % 2 == 1; });
	copy(v.begin(), bound, ostream_iterator<int>(cout, " "));
	return 0;
}