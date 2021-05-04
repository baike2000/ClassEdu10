#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

enum CellStatus
{
	emptycell = '@',
	krosh = 'X',
	lutik = 'O'
};

class Cell
{
private:
	CellStatus _status = emptycell;
public:
	Cell(CellStatus status)
	{
		_status = status;
	}
	char GetCellValue()
	{
		return _status;
	}
	void SetCellValue(CellStatus status)
	{
		_status = status;
	}
};

class Parliament
{
private:
	vector<vector<vector<Cell*>>> _p;
	int _size = 4;
public:
	Parliament(vector<CellStatus> p, int size)
	{
		_size = size;
		_p.resize(_size);
		int c = 0;
		for (int i = 0; i < _size; i++)
		{
			_p[i].resize(_size);
			for (int j = 0; j < _size; j++)
			{
				_p[i][j].resize(_size);
				for (int k = 0; k < _size; k++)
				{
					_p[i][j][k] = new Cell((CellStatus)p[c]);
					c++;
				}
			}
		}
	}
	void Conquare()
	{

	}
	void Print()
	{
		for (int i = 0; i < _size; i++)
		{
			for (int j = 0; j < _size; j++)
			{
				for (int k = 0; k < _size; k++)
				{
					cout << _p[i][j][k]->GetCellValue();
				}
				cout << endl;
			}
			cout << endl;
		}
	}
};

class Rule
{
public:
	virtual bool Check(vector<CellStatus> s) = 0;
};

class TurnOrder : public Rule
{
public:
	bool Check(vector<CellStatus> s) override
	{
		int k = 0;
		int l = 0;
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == krosh)
				k++;
			if (s[i] == lutik)
				l++;
		}
		return (k - l != 0);
	}
};

class Validator
{
private:
	vector<Rule*> _v;
	vector<CellStatus> _s;
	bool _result;
public:
	Validator(vector<CellStatus> s)
	{
		_s = s;
	}
	void AddRule(Rule* rule)
	{
		_v.push_back(rule);
	}
	void Vlaidate()
	{
		_result = true;
		for (auto vl : _v)
		{
			_result = _result && vl->Check(_s);
		}
	}
	bool GetResult()
	{
		return _result;
	}
};
int main()
{
	string s;
	cin >> s;
	vector<CellStatus> v;
	for (int i = 0; i < s.size(); i++)
	{
		v.push_back((CellStatus)s[i]);
	}
	Validator* validator = new Validator(v);
	validator->AddRule(new TurnOrder());
	validator->Vlaidate();
	if (!validator->GetResult())
	{
		cout << "BREAKDOWN" << endl;
		return 0;
	}
	Parliament* par = new Parliament(v, 4);
	par->Print();
	par->Conquare();
	return 0;
}


