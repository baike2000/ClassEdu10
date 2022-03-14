#include <iostream>
#include <string>

using namespace std;

typedef struct TNode* PNode;
typedef struct TNode
{
	string data;
	PNode left;
	PNode right;
} TNode;

int Priority(char op)
{
	switch (op)
	{
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	}
	return 100;
}

int LastOp(string s)
{
	long long int i, minPrt, res;
	minPrt = 50; // любое между 2 и 100
	res = -1;
	int c = 0;
	for (i = 0; i < s.size(); i++)
	{
		if (s[i] == '(')
			c++;
		else if (s[i] == ')')
			c--;
		else if (Priority(s[i]) <= minPrt && !c)
		{
			minPrt = Priority(s[i]);
			res = i;
		}
	}
	return res;
}


PNode MakeTree(string s)
{
	long long int k;
	k = LastOp(s);
	if (s[0] == '(' && s[s.size() - 1] == ')' && k == -1)
		return MakeTree(s.substr(1, s.size() - 2));
	PNode Tree;
	Tree = new struct TNode;
	if (k == -1) {
		Tree->data = s;
		Tree->left = NULL;
		Tree->right = NULL;
	}
	else {
		Tree->data = s.substr(k, 1);
		Tree->left = MakeTree(s.substr(0, k));
		Tree->right = MakeTree(s.substr(k + 1));
	}
	return Tree;

}

int Calc(PNode Tree)
{
	long long int n1, n2, res;
	if (Tree->left == NULL)
		res = atoi(Tree->data.c_str());
	else {
		n1 = Calc(Tree->left);
		n2 = Calc(Tree->right);
		switch (Tree->data[0]) {
		case '+': res = n1 + n2; break;
		case '-': res = n1 - n2; break;
		case '*': res = n1 * n2; break;
		case '/': res = n1 / n2; break;
		default: res = 99999;
		}
	}
	return res;
}

int main()
{
	PNode T;
	string s;
	cin >> s;
	int i = 0;
	// ввести строку s
	T = MakeTree(s);
	cout << Calc(T) << endl;
	return 0;
}