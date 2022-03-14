#include<iostream>
#include<set>
#include<map>
#include<unordered_map>
#include<algorithm>

using namespace std;

int main()
{
	map<string, int> m;
	unordered_map<string, int> um;
	set<string> st;
	string s;
	while (cin >> s)
	{
		um[s]++;
	}
	for (auto it = um.begin(); it != um.end(); it++)
	{
		cout << it->first << " " << it->second << endl;
	}
	return 0;
}