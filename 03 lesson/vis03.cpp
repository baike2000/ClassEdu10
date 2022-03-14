#include<iostream>
#include<stack>

using namespace std;

int main1()
{
	int n;
	stack<int> st;
	while (cin >> n)
	{
		st.push(n);
	}
	while (!st.empty())
	{
		cout << st.top() << " ";
		st.pop();
	}
	
	return 0;
}