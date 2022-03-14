#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

struct atom
{
	char A;
	int C;
};

set<char> ch;

vector<atom> ConvertTo(string s)
{
	vector<atom> a;
	int i = 0;
	while (i < s.size())
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
		{
			atom ac;
			ac.A = s[i];
			ac.C = 1;
			i++;
			if (i < s.size() && s[i] > '1' && s[i] <= '9')
			{
				ac.C = (int)s[i] - '0';
				i++;
			}
			a.push_back(ac);
		}
	}
	return a;
}

bool check(int a, int b, int c, vector<atom> at[])
{
	int atr[3][100] = { 0 };
	int cf[3] = { a,b,c };
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < at[j].size(); i++)
		{
			atr[j][i] = at[j][i].C * cf[j];
		}
	}
	for (int j = 0; j < at[2].size(); j++)
	{
		if (atr[0][j] + atr[1][j] != atr[2][j])
			return false;
	}
	return true;
}
int mainB()
{
	string s[3];
	cin >> s[0] >> s[1] >> s[2];
	vector<atom> atoms[3];
	for (int i = 0; i < 3; i++)
	{
		atoms[i] = ConvertTo(s[i]);
		for (int j = 0; j < atoms[i].size(); j++)
			ch.insert(atoms[i][j].A);
	}
	for (auto c : ch)
	{
		for (int j = 0; j < 3; j++)
		{
			bool flag = false;
			for (int i = 0; i < atoms[j].size(); i++)
			{
				if (atoms[j][i].A == c)
				{
					flag = true;
					break;
				}
			}
			if (!flag)
				atoms[j].push_back({ c, 0 });
		}
	}
	for (int i = 0; i < 3; i++)
		sort(atoms[i].begin(), atoms[i].end(), [](atom a, atom b) {return a.A > b.A; });

	for (int i = 1; i < 100; i++)
	{
		for (int j = 1; j < 100; j++)
		{
			for (int k = 1; k < 100; k++)
			{
				if (check(i, j, k, atoms))
				{
					cout << i << " " << j << " " << k << endl;
					return 0;
				}
			}
		}
	}
	cout << "0 0 0" << endl;
	return 0;
}
/*
H2 O2 H2O

a 2*2H 2*0O = 4H 0O

b 1*0H 1*2O = 0H 2O

c 2*2H 2*1O = 4H 2O
*/