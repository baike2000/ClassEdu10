#include<iostream>
#include<stack>
#include<string>

using namespace std;

int main3()
{
	string L = "([{",     // открывающие
		   R = ")]}";     // закрывающие
	string str;           // рабочая строка 
	stack <char> S;		  // стек
	bool err = false;     // была ли ошибка?
	int n;
	cin >> n;
	getline(cin, str);
	getline(cin, str);

	for (int i = 0; i < str.size(); i++) 
	{
		int p = L.find(str[i]);
		if (p >= 0)
			S.push(str[i]);
		p = R.find(str[i]);
		if (p >= 0) 
		{
			if (S.empty())
				err = true;
			else 
			{
				char c = S.top(); 
				S.pop();
				if (p != L.find(c))
					err = true;
			}
			if (err) break;
		}
	}
	err = err || !S.empty();
	if (!err)
		cout << "Yes";
	else
		cout << "No";

	return 0;
}