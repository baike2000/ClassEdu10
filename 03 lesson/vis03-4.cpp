#include<iostream>
#include<queue>

using namespace std;

struct point
{
	point(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
	int x, y;
};

queue<point> q;
int a[100][100] = {0};
int m, n;

void paint(int x, int y, int col1, int col2)
{
	q.push(point(x, y));
	while (!q.empty())
	{
		point p = q.front();
		q.pop();
		if (a[p.x][p.y] == col1)
			a[p.x][p.y] = col2;
		if (p.x > 0 && a[p.x - 1][p.y] == col1)
			q.push(point(p.x - 1, p.y));
		if (p.y > 0 && a[p.x][p.y - 1] == col1)
			q.push(point(p.x, p.y - 1));
		if (p.x < n - 1 && a[p.x + 1][p.y] == col1)
			q.push(point(p.x + 1, p.y));
		if (p.y < m - 1 && a[p.x][p.y + 1] == col1)
			q.push(point(p.x, p.y + 1));
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> a[i][j];
		}
	}
	int col1, col2;
	cin >> col1 >> col2;
	bool fl = false;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (a[i][j] == col1)
			{
				paint(i, j, col1, col2);
				fl = true;
				break;
			}
		}
		if (fl)
			break;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}

/*
5 5
0 1 0 1 1
1 1 1 2 2
0 1 0 2 2
3 3 1 2 2
0 1 1 0 0
2 4
*/