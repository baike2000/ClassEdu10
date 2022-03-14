#include<iostream>
#include<algorithm>

using namespace std;

struct TBook
{
	string Author;
	string Title;
	int Count;
};

bool comp(TBook& a, TBook& b)
{
	if (a.Author == b.Author)
		return a.Title > b.Title;
	else
		return a.Author > b.Author;
}

int main01()
{
	TBook books[5];
	books[0].Author = "Tolstoi";
	books[0].Title = "War and Peace";
	books[0].Count = 100;
	for (int i = 0; i < 3; i++)
	{
		cin >> books[i].Author >> books[i].Title >> books[i].Count;
	}
	sort(books, books + 3, comp);
	/*int j = 0;
	cin >> j;
	cin >> books[j].Count;*/
	for (int i = 0; i < 3; i++)
	{
		cout << books[i].Author << " " << books[i].Title << " " << books[i].Count << endl;
	}

	return 0;
}