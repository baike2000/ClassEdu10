#include<iostream>
#include<vector>
#include<cmath>
#include<map>
#include<set>

using namespace std;

enum Direction
{
	North = 'N', South = 'S', East = 'E', West = 'W'
};


class Screen
{
private:
	vector<vector<char>> _field;
	pair<int, int> _initpos;
	pair<int, int> _size;
	Direction _dir;
public:
	Screen(int x, int y)
	{
		_size = { 32,32 };
		for (int i = 0; i < 32; i++)
		{
			vector<char> v(32);
			for (int j = 0; j < 32; j++)
			{
				v[j] = '.';
			}
			_field.push_back(v);
		}
		_initpos = { x-1,y-1 };
		_dir = North;
	}

	char Get(int x, int y)
	{
		return _field[x][y];
	}

	void Set(int x, int y, char c)
	{
		_field[x][y] = c;
	}
	pair<int, int> GetPos()
	{
		return _initpos;
	}

	void SetPos(pair<int, int> pos)
	{
		_initpos = pos;
	}
	Direction GetDir()
	{
		return _dir;
	}
	void SetDir(Direction dir)
	{
		_dir = dir;
	}
	pair<int, int> Size()
	{
		return _size;
	}
};

class ICommand
{
protected:
	Screen* _screen;
	Direction _dir;
	map<Direction, pair<int, int>> m;
public:
	ICommand(Screen* screen)
	{
		_screen = screen;
		m[North] = { 0,1 };
		m[South] = { 0,-1 };
		m[West] = { -1,0 };
		m[East] = { 1,0 };
		_dir = North;
	}
	virtual void Move()
	{
		if (_screen->GetDir() != _dir)
		{
			_screen->SetDir(_dir);
		}
		else
		{
			_screen->Set(_screen->GetPos().first, _screen->GetPos().second, 'X');
		}
		_screen->SetPos({ _screen->GetPos().first + m[_dir].first,_screen->GetPos().second + m[_dir].second });
	}
};

class NCmd :public ICommand
{
public:
	NCmd(Screen* screen) :ICommand(screen) 
	{
		_dir = North;
	}
	void Move() override
	{
		ICommand::Move();
	}
};

class SCmd :public ICommand
{
public:
	SCmd(Screen* screen) :ICommand(screen) 
	{
		_dir = South;
	}
	void Move() override
	{
		ICommand::Move();
	}
};

class WCmd :public ICommand
{
public:
	WCmd(Screen* screen) :ICommand(screen) 
	{
		_dir = West;
	}
	void Move() override
	{
		ICommand::Move();
	}
};

class ECmd :public ICommand
{
public:
	ECmd(Screen* screen) :ICommand(screen)
	{
		_dir = East;
	}
	void Move() override
	{
		ICommand::Move();
	}
};

class Game
{
private:
	Screen* _screen;
	vector<ICommand*> _cmds;
public:
	Game(int x, int y)
	{
		_screen = new Screen(x,y);
	}

	void AddCommand(char c)
	{
		ICommand* cmd;
		if (c == (char)North)
			cmd = new NCmd(_screen);
		if (c == (char)South)
			cmd = new SCmd(_screen);
		if (c == (char)West)
			cmd = new WCmd(_screen);
		if (c == (char)East)
			cmd = new ECmd(_screen);
		_cmds.push_back(cmd);
	}

	void Run()
	{
		for (auto cmd:_cmds)
		{
			cmd->Move();
		}
	}

	void Draw()
	{
		for (int i = 0; i < _screen->Size().first; i++)
		{
			for (int j = 0; j < _screen->Size().second; j++)
			{
				cout << _screen->Get(i, j);
			}
			cout << endl;
		}
	}

	~Game()
	{
		for (int i = 0; i < _cmds.size(); i++)
			delete _cmds[i];
	}
};

int main()
{
	int x, y;
	cin >> x >>  y;
	Game* game = new Game(x, y);
	char c;
	while(cin >> c)
	{
		game->AddCommand(c);
	}
	game->Run();
	game->Draw();
	delete game;
	return 0;
}