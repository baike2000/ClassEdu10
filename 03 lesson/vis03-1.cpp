#include<iostream>
#include<stack>
#include<string>

using namespace std;
//5 15 + 4 7 + 1 - /

int main2()
{
	stack<int> st;
	string s;
	while(cin >> s)
	{
		if (s != "+" && s != "-" && s != "/" && s != "*")
		{
			int n = atoi(s.c_str());
			st.push(n);
			continue;
		}
		int a = st.top();
		st.pop();
		int b = st.top();
		st.pop();
		int c = 0;
		if (s == "+")
		{
			c = a + b;
		}
		if (s == "-")
		{
			c = b - a;
		}
		if (s == "/")
		{
			c = b / a;
		}
		if (s == "*")
		{
			c = a * b;
		}
		st.push(c);
	}
	cout << st.top() << endl;
	return 0;
}