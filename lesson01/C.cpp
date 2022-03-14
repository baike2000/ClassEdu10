#include<iostream>
#include<algorithm>

using namespace std;

struct fraction
{
	int nominator;
	int denominator;
	long double value;
};

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

fraction getfr(int a, int b)
{
	int g = gcd(a, b);
	fraction r;
	r.nominator = a / g;
	r.denominator = b / g;
	r.value = ((long double)a) / b;
	return r;
}

bool comp(fraction& a, fraction& b)
{
	return a.value < b.value;
}

fraction fr[1000000];

int main()
{
	int n;
	cin >> n;

	int cnt = 0;
	for (int i = 1; i < n; i++)
	{
		for (int j = i+1; j <= n; j++)
		{
			if (gcd(i, j) > 1)
				continue;
			fr[cnt] = getfr(i, j);
			cnt++;
		}
	}
	sort(fr, fr + cnt, comp);
	for (int i = 0; i < cnt; i++)
	{
		//if (i > 0 && fr[i].nominator == fr[i - 1].nominator && fr[i].denominator == fr[i - 1].denominator)
			//continue;
		cout << fr[i].nominator << "/" << fr[i].denominator << endl;
	}
	return 0;
}



