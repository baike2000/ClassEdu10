#include<iostream>
#include<vector>
#include<cmath>
#include<map>
#include<set>

using namespace std;

//»тератор - проход по тексту (TextBuf)
//‘абричный метод - дл€ генерации комманд

class TextBuf
{
private:
	string _text; // Ќадо использовать map дл€ хранени€ информации о том, что хранитьс€ по данной позиции кусора
	int _pos; //текуща€ позици€
public:
	TextBuf()
	{
		_text = "";
		_pos = 0;
	}
	string GetText()
	{
		return _text;
	}
	void SetText(string text)
	{
		_text = text;
	}
	int GetPos()
	{
		return _pos;
	}
	void SetPos(int pos)
	{
		if (pos >= _text.size())
			_text += " ";
		if (pos < 0)
			return;
		_pos = pos;
	}
	char GetChar(int index)
	{
		return _text[index];
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
		for (int i = 0; i < _pos; i++)
			_buffer->SetPos(_buffer->GetPos()-1);
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
		for (int i = 0; i < _pos; i++)
			_buffer->SetPos(_buffer->GetPos() + 1);
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
		auto s_old = _buffer->GetText();
		auto it = s_old.begin();
		for (int i = 0; i < _pos; i++)
		{
			s_old.insert(it, _alph);
		}
		for (int i = 0; i < _pos - 1; i++)
		{
			_buffer->SetPos(_buffer->GetPos() + 1);
		}
	}
};

class Editor
{
public:
	TextBuf* _buffer;
	Editor(TextBuf* buffer)
	{
		_buffer = buffer;
	}
	void ExecCommand(ICommand* cmd)
	{
		cmd->exec();
	}
	void PrintChar(int index)
	{
		cout << _buffer->GetChar(index) << endl;
	}
};


int main()
{
	Editor* editor = new Editor(new TextBuf());
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		int c;
		char ch;
		cin >> c >> ch;
		if (ch == 'I')
		{
			char b;
			cin >> b;
			editor->ExecCommand(new InsCommand(editor->_buffer, c, b)); // команды определить в редакторе как шаблонный метод
		}
	}
	for (int i = 0; i < m; i++)
	{
		int k;
		cin >> k;
		editor->PrintChar(k);
	}
	return 0;
}

