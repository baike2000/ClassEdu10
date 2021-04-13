#include<iostream>
#include<vector>
#include<cmath>
#include<map>
#include<set>

using namespace std;

//Итератор - проход по тексту (TextBuf)
//Фабричный метод - для генерации комманд

class TextBuf
{
private:
	map<pair<int, int>, char> _text;
	int _pos; //текущая позиция
public:
	TextBuf()
	{
		_pos = 0;
	}
	char GetText(int x)
	{
		for (auto it = _text.begin(); it != _text.end(); it++)
		{
			if (x >= it->first.first && x <= it->first.second)
				return it->second;
		}
		return 0;
	}
	void SetText(int x, int count, char text)
	{
		pair<int, int> cur = { 0,0 };
		char cur_c = 0;
		for (auto it = _text.begin(); it != _text.end(); it++)
		{
			if (x >= it->first.first && x <= it->first.second)
			{
				cur = it->first;
				cur_c = it->second;
				break;
			}
		}
		_text.erase(cur);
		_text[{cur.first, x - 1 }] = cur_c;
		_text[{x, x + count }] = text;
		_text[{x + count + 1, x + count + cur.first - cur.second + 1}] = cur_c;
		//Сдвинуть все отрезки вправо на count позиций.
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

