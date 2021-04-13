#include<iostream>
#include<vector>
#include<cmath>
#include<map>
#include<set>
#include<algorithm>

using namespace std;

//Итератор - проход по тексту (TextBuf)
//Фабричный метод - для генерации комманд

class Position
{
public:
	int l, r;
	char c;
};


class TextBuf
{
private:
	vector<Position> _text;
	int _pos; //текущая позиция
public:
	TextBuf()
	{
		_pos = 0;
	}
	char GetText(int x)
	{
		for (int i = 0; i < _text.size(); i++)
		{
			if (x >= _text[i].l && x <= _text[i].r)
				return _text[i].c;
		}
		return 0;
	}
	void SetText(int x, int count, char text)
	{
		Position ps;
		int i = 0;
		int sz = _text.size();
		for(i = 0; i < sz; i++)
		{
			if (x >= _text[i].l && x <= _text[i].r) // внутри отрезка
			{
				int r = _text[i].r;
				_text[i].r = x - 1;
				Position p1;
				p1.l = x;
				p1.r = x + count;
				p1.c = text;
				_text.push_back(p1);
				Position p2;
				p2.l = x + count + 1;
				p2.r = r + count;
				p2.c = _text[i].c;
				_text.push_back(p2);
				break;
			}
			if ((x > _text[i].r && i < sz - 1 && x < _text[i + 1].l) || i == sz - 1)
			{
				Position p;
				p.l = x;
				p.l = x + count;
				p.c = text;
				_text.push_back(p);
				break;
			}
		}
		for (int j = i + 1; j < sz; j++)
		{
			_text[j].l += count;
			_text[j].r += count;
		}
		sort(_text.begin(), _text.end(), [](Position& a, Position& b) { return a.l < b.l; });
	}
	int GetPos()
	{
		return _pos;
	}
	void SetPos(int pos)
	{
		_pos = pos;
	}
};

class ICommand
{
public:
	ICommand(TextBuf* buffer)
	{
		_buffer = buffer;
	}
	virtual void exec() = 0;
protected:
	TextBuf* _buffer;
};

class HCommand : public ICommand
{
private:
	int _pos;
public:
	HCommand(TextBuf* buffer, int pos) : ICommand(buffer)
	{
		_pos = pos;
	}
	void exec() override
	{
		_buffer->SetPos(_buffer->GetPos() - _pos);
	}
};

class LCommand : public ICommand
{
private:
	int _pos;
public:
	LCommand(TextBuf* buffer, int pos) : ICommand(buffer)
	{
		_pos = pos;
	}
	void exec() override
	{
		_buffer->SetPos(_buffer->GetPos() + _pos);
	}
};

class InsCommand : public ICommand
{
private:
	int _pos;
	char _alph;
public:
	InsCommand(TextBuf* buffer, int pos, char alph) : ICommand(buffer)
	{
		_pos = pos;
		_alph = alph;
	}
	void exec() override
	{
		_buffer->SetText(_buffer->GetPos(), _pos, _alph);
		_buffer->SetPos(_buffer->GetPos() + _pos);
	}
};

class Editor
{
private:
	vector<ICommand*> _cmds;
	TextBuf* _buffer;
public:
	Editor()
	{
		_buffer = new TextBuf();
	}
	void AddCommand(int cnt, char cmd, char alph)
	{
		ICommand* ccmd;
		if (cmd == 'I')
			ccmd = new InsCommand(_buffer, cnt, alph);
		if (cmd == 'H')
			ccmd = new HCommand(_buffer, cnt);
	    if (cmd == 'L')
			ccmd = new LCommand(_buffer, cnt);
		_cmds.push_back(ccmd);
	}
	void Exec()
	{
		for(auto cmd:_cmds)
			cmd->exec();
	}
	void PrintChar(int index)
	{
		cout << _buffer->GetText(index) << endl;
	}
};


int main()
{
	Editor* editor = new Editor();
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		int c;
		char ch, b = 0;
		cin >> c >> ch;
		if (ch == 'I')
		{
			cin >> b;
		}
		editor->AddCommand(c, ch, b);
	}
	editor->Exec();
	for (int i = 0; i < m; i++)
	{
		int k;
		cin >> k;
		editor->PrintChar(k);
	}
	return 0;
}

