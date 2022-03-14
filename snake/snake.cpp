#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

void Cls() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

void SetPos(int x, int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetForeColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void SetBackColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

enum Objects
{
	Empty,
	Rabbit,
	Python,
	Wall
};

class IValue
{
public:
	virtual Objects GetType() = 0;
};

class Cell
{
private:
	int _i, _j;
	IValue* _value;
public:
	Cell(int i, int j, IValue* value)
	{
		_i = i;
		_j = j;
		_value = value;
	}
	int GetI()
	{
		return _i;
	}
	int GetJ()
	{
		return _j;
	}
	IValue* GetValue()
	{
		return _value;
	}
	void SetValue(IValue* value)
	{
		_value = value;
	}
};


class Field
{
private:
	int _w, _h;
	vector<vector<Cell*>> _field;
public:
	Field(int w, int h)
	{
		_w = w;
		_h = h;
		for (int i = 0; i < h; i++)
		{
			vector<Cell*> v;
			for (int j = 0; j < w; j++)
			{
				v.push_back(new Cell(i, j, NULL));
			}
			_field.push_back(v);
		}
	}
};

class Snake : public IValue
{
private:
	Cell* _head;
	vector<Cell*> _tail;
	int _len = 0;
public:
	Snake(Cell* cell)
	{
		_head = cell;
		_head->SetValue(this);
		_len = 1;
	}
	Cell* GetHead()
	{
		return _head;
	}
	vector<Cell*> GetTail()
	{
		return _tail;
	}
	Objects GetType() override
	{
		return Objects::Python;
	}
};

class Wall : public IValue
{
private:
	vector<Cell*> _wall;
public:
	Wall(vector<Cell*> wall)
	{
		_wall = wall;
		for (int i = 0; i < _wall.size(); i++)
		{
			_wall[i]->SetValue(this);
		}
	}
	Objects GetType() override
	{
		return Objects::Wall;
	}
};

class Rabbit : public IValue
{
private:
	Cell* _rabbit;
	int _weight;
public:
	Rabbit(Cell* rabbit, int weigth)
	{
		_rabbit = rabbit;
		_rabbit->SetValue(this);
		_weight = weigth;
	}
	Objects GetType() override
	{
		return Objects::Rabbit;
	}
};

class Draw
{

};

class Game
{
private:
	int _numrabbits;
	int _w, _h;
	int _numwalls;
	Snake* _snake;
public:
	Game(int w, int h, int s_i, int s_j, int numrabbits, int numwalls)
	{
		_w = w; _h = h;
		_numrabbits = numrabbits;
		_numwalls = numwalls;
	}
	void Play()
	{
	}
};

int main()
{
	return 0;
}