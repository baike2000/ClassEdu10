#include<iostream>
#include<algorithm>

using namespace std;

struct company
{
	string name;
	long long price;
	int quality;
};

company comps[1000000];

bool comp(company& a, company& b)
{
	if (a.price == b.price)
		return a.quality > b.quality;
	return a.price < b.price;
}

int mainA()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> comps[i].name >> comps[i].price >> comps[i].quality;
	}
	sort(comps, comps + n, comp);

	cout << comps[0].name << endl;
	
	return 0;
}