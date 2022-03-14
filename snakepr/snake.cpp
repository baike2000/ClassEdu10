#include<iostream>
#include<vector>

using namespace std;

const int c_w = 80;
const int c_h = 40;
const int c_max_snake = 1000;
const int c_max_wall_size = 1000;
const int c_max_rabbits = 10;
const int c_step = 15;
const int c_empty = 0;
const int c_snake_head = 10;
const int c_snake_tail = 11;
const int c_wall = 12;

enum Color
{
	LightGray,
	White,
	Yellow,
	Blue,
	Brown,
	Black
};

class Cell
{
public:
	int i, j;
	int x1, y1, x2, y2;
	Color clPen;
	Color clBrush;
	int val;
};

class Field
{
public:
	vector<vector<Cell>> field;
};
class Snake
{
public:
	Cell head;
	vector<Cell> tail;
	int len;
	int curlen;
};

class Wall
{
public:
	vector<Cell> wallcells;
	int size;
};

class Rabbit
{
public:
	Cell pos;
	int weight;
};

class Rabbits
{
public:
	vector<Rabbit> rabbits;
};

void SetCell(Cell &dst_cell, Cell src_cell)
{
	dst_cell.i  = src_cell.i;
	dst_cell.j  = src_cell.j;
	dst_cell.x1  = src_cell.x1;
	dst_cell.x2  = src_cell.x2;
	dst_cell.y1  = src_cell.y1;
	dst_cell.y2  = src_cell.y2;
	dst_cell.clPen  = src_cell.clPen;
	dst_cell.clBrush  = src_cell.clBrush;
	dst_cell.val = src_cell.val;
}

void SetEmpty(Cell& a_cell)
{
	a_cell.val  = c_empty;
	a_cell.clPen  = Color::LightGray;
	a_cell.clBrush  = Color::White;
}

void SetWall(Cell& a_cell)
{
	a_cell.val  = c_wall;
	a_cell.clPen  = Color::LightGray;
	a_cell.clBrush  = Color::Yellow;
}

void SetHead(Cell &a_cell)
{
	a_cell.val = c_snake_head;
	a_cell.clPen = Color::LightGray;
	a_cell.clBrush = Color::Blue;
}

void SetTail(Cell &a_cell)
{
	a_cell.val = c_snake_tail;
	a_cell.clPen = Color::LightGray;
	a_cell.clBrush = Color::Brown;
}

void SetRabbit(Cell &a_cell, int val)
{
	a_cell.val = val;
	a_cell.clPen = Color::LightGray;
	a_cell.clBrush = Color::Black;
}

void DrawCell(Cell a_cell)
{
	//SetPenColor(a_cell.clPen);
	//SetBrushColor(a_cell.clBrush);
	//Rectangle(a_cell.x1, a_cell.y1, a_cell.x2, a_cell.y2);
}

void InitField(Field &a_field)
{
	int i, j, x, y;
	x = 0; y = 0;
	for (j = 0; j < c_h; j++)
	{
		for (i = 1; i < c_w; i++)
		{
			a_field.field[i][j].i = i;
			a_field.field[i][j].j = j;
			a_field.field[i][j].x1 = x;
			a_field.field[i][j].x2 = x + c_step;
			a_field.field[i][j].y1 = y;
			a_field.field[i][j].y2 = y + c_step;
			SetEmpty(a_field.field[i][j]);
			x = x + c_step;
		}
		y = y + c_step;
		x = 0;
	}
}

void InitWall(int x1, int y1, int x2, int y2, Field& a_field, Wall& a_wall)
{
	int i, j;
	for (i = x1; i <= x2; i++)
		for (j = y1; j <= y2; j++)
		{
			SetWall(a_field.field[i][j]);
			a_wall.size++;
			SetCell(a_wall.wallcells[a_wall.size], a_field.field[i][j]);
		}
}

void GetRandomEmptyCell(int& x, int &y, Field& a_field)
{
	bool flag = false;
	do
	{
		x = rand() % 79 + 2;
		y = rand() % 39 + 2;
		if (a_field.field[x][y].val == c_empty) 
			flag = true;
	} while (!flag);
}

void InitRabbits(Field& a_field, Rabbits& a_rabbits, int maxrabbit)
{
	int i, a_w, x, y, flag;
	for (i = 1; i <= maxrabbit; i++)
	{
		if (a_rabbits.rabbits[i].weight == 0)
		{
			a_w = rand() % 9 + 1;
			GetRandomEmptyCell(x, y, a_field);
			SetRabbit(a_field.field[x][y], a_w);
			SetCell(a_rabbits.rabbits[i].pos, a_field.field[x][y]);
			a_rabbits.rabbits[i].weight = a_w;
		}
	}
}

void SetNewRabbit(Field& a_field, Rabbit& a_rabbit)
{
	int a_w, x, y, flag;
	a_w = rand() % 9 + 1;
	GetRandomEmptyCell(x, y, a_field);
	SetRabbit(a_field.field[x][y], a_w);
	SetCell(a_rabbit.pos, a_field.field[x][y]);
	a_rabbit.weight = a_w;
}

void DrawField(int h, int w, Field a_field)
{
	int i, j;
	for (i = 1; i < w; i++)
		for (j = 1; j < h; j++)
			DrawCell(a_field.field[i][j]);
}

void DrawSnake(Snake& a_snake, int x, int y, Field& a_field)
{
	Cell a_cell, tmp;
	int i;
	if (x == a_snake.head.i && y == a_snake.head.j)
		return;
	SetCell(a_cell, a_snake.head);
	SetEmpty(a_cell);
	DrawCell(a_cell);
	SetCell(a_field.field[a_snake.head.i][a_snake.head.j], a_cell);
	SetHead(a_field.field[x][y]);
	SetCell(a_snake.head, a_field.field[x][y]);
	DrawCell(a_snake.head);
	if (a_snake.len > 0)
	{
		if (a_snake.curlen > 0)
			SetCell(tmp, a_snake.tail[a_snake.curlen]);
		for (i = a_snake.curlen; i >= 2; i--)
		{
			SetCell(a_snake.tail[i], a_snake.tail[i - 1]);
		}
		if (a_snake.len == a_snake.curlen)
		{
			SetEmpty(tmp);
			SetCell(a_field.field[tmp.i][tmp.j], tmp);
			SetTail(a_field.field[a_cell.i][a_cell.j]);
			SetCell(a_snake.tail[1], a_field.field[a_cell.i][a_cell.j]);
			DrawCell(tmp);
		}
		if (a_snake.len > a_snake.curlen)
		{
			a_snake.curlen++;
			SetCell(a_snake.tail[a_snake.curlen], tmp);
			SetTail(a_field.field[a_cell.i][a_cell.j]);
			SetCell(a_snake.tail[1], a_field.field[a_cell.i][a_cell.j]);
		}
		for (i = 1; i <= a_snake.curlen; i++)
			DrawCell(a_snake.tail[i]);
	}
}

Snake v_snake;
Field v_field;
Wall walls[4];
Rabbits v_rabbits;
int side;

void IncCoord(int ix, int iy, int& x, int& y)
{
	int i;
	if (v_field.field[x + ix][y + iy].val == c_wall)
		return;
	if (v_field.field[x + ix][y + iy].val == c_snake_tail)
		return;
	if (v_field.field[x + ix][y + iy].val >= 1 && v_field.field[x + ix][y + iy].val <= 9)
	{
		v_snake.len = v_snake.len + v_field.field[x + ix][y + iy].val;
		SetEmpty(v_field.field[x + ix][y + iy]);
		for (i = 1; i <= 10; i++)
			if (v_rabbits.rabbits[i].pos.i == x + ix && v_rabbits.rabbits[i].pos.j == y + iy)
			{
				SetEmpty(v_rabbits.rabbits[i].pos);
				v_rabbits.rabbits[i].weight = 0;
				SetNewRabbit(v_field, v_rabbits.rabbits[i]);
				DrawCell(v_rabbits.rabbits[i].pos);
			}
	}
	x = x + ix;
	y = y + iy;
}


void KeyEvent(int c)

{
	int x, y;

	x = v_snake.head.i;
	y = v_snake.head.j;
	side = c;
	if (c == 37) IncCoord(-1, 0, x, y);
	if (c == 39) IncCoord(1, 0, x, y);
	if (c == 38) IncCoord(0, -1, x, y);
	if (c == 40) IncCoord(0, 1, x, y);
	DrawSnake(v_snake, x, y, v_field);
}

int main()
{
	InitField(v_field);
	InitWall(1, 1, 80, 1, v_field, walls[1]);
	InitWall(1, 40, 80, 40, v_field, walls[2]);
	InitWall(1, 1, 1, 40, v_field, walls[3]);
	InitWall(80, 1, 80, 40, v_field, walls[4]);
	v_snake.curlen = 0;
	v_snake.len = 5;
	SetHead(v_field.field[40][20]);
	SetCell(v_snake.head, v_field.field[40][20]);
	InitRabbits(v_field, v_rabbits, 10);
	DrawField(c_h, c_w, v_field);
	//OnKeyDown = KeyEvent;
	side = 38;
	do
	{
		//sleep(100);
		KeyEvent(side);
	}
	while (true);
}