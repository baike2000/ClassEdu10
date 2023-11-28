#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define SIDE 3 

class Piece;
class Board
{
private:
	char board[SIDE][SIDE];
public:
	void ShowBoard()
	{
		printf("\n\n");

		printf("\t\t\t %c | %c | %c \n",
			board[0][0],
			board[0][1],
			board[0][2]);

		printf("\t\t\t------------\n");

		printf("\t\t\t %c | %c | %c \n",
			board[1][0],
			board[1][1],
			board[1][2]);

		printf("\t\t\t------------\n");
		printf("\t\t\t %c | %c | %c \n\n",
			board[2][0],
			board[2][1],
			board[2][2]);

		return;
	}
	void SetPos(int position, char value)
	{
		board[position / SIDE][position % SIDE] = value;
	}
	char GetPos(int position)
	{
		return board[position / SIDE][position % SIDE];
	}
	bool rowCrossed()
	{
		for (int i = 0; i < SIDE; i++) {
			if (board[i][0] == board[i][1]
				&& board[i][1] == board[i][2]
				&& board[i][0] != ' ')
				return (true);
		}
		return (false);
	}
	bool columnCrossed()
	{
		for (int i = 0; i < SIDE; i++) {
			if (board[0][i] == board[1][i]
				&& board[1][i] == board[2][i]
				&& board[0][i] != ' ')
				return (true);
		}
		return (false);
	}
	bool diagonalCrossed()
	{
		if (board[0][0] == board[1][1]
			&& board[1][1] == board[2][2]
			&& board[0][0] != ' ')
			return (true);

		if (board[0][2] == board[1][1]
			&& board[1][1] == board[2][0]
			&& board[0][2] != ' ')
			return (true);

		return (false);
	}
	int GetPlacesCount()
	{
		return SIDE * SIDE;
	}
};

class Rule
{
public:
	Rule() {}
	virtual bool Check(Board* board) = 0;
	virtual bool IsWin() = 0;
};

class RowWin :public Rule
{
public:
	bool Check(Board* board) override
	{
		bool flag = true;
		for (int i = 0; i < board->GetPlacesCount() / SIDE; i++) {
			for (int j = 1; j < board->GetPlacesCount() / SIDE; j++) {
				if (board->GetPos(i * j) == board->GetPos(i * (j - 1))
					&& board->GetPos(i * j) != ' ')
					flag = flag && true;
				else
					flag = flag && false;
			}
		}
		return flag;
	}
	bool IsWin() { return true; }
};

class ColumnWin :public Rule
{
public:
	bool Check(Board* board) override
	{
		bool flag = true;
		for (int i = 0; i < board->GetPlacesCount() / SIDE; i++) {
			for (int j = 1; j < board->GetPlacesCount() / SIDE; j++) {
				if (board->GetPos(i * j) == board->GetPos(i * (j - 1))
					&& board->GetPos(i * j) != ' ')
					flag = flag && true;
				else
					flag = flag && false;
			}
		}
		return flag;
	}
	bool IsWin() { return true; }
};

class DiagonalWin :public Rule
{
public:
	bool Check(Board* board) override
	{
		bool flag = true;
		for (int i = 0; i < (board->GetPlacesCount() / SIDE) - 1; i++) {
			if (board->GetPos(i * i) == board->GetPos((i + 1) * (i + 1))
				&& board->GetPos(i * i) != ' ')
				flag = flag && true;
			else
				flag = flag && false;
		}
		for (int i = 0; i < (board->GetPlacesCount() / SIDE) - 1; i++) {
			if (board->GetPos(((SIDE - i + 1) * i)) == board->GetPos(((SIDE - i + 1) + 1) * (i + 1))
				&& board->GetPos((SIDE - i + 1) * i) != ' ')
				flag = flag && true;
			else
				flag = flag && false;
		}
		return flag;
	}
	bool IsWin() { return true; }
};

class IsFull : public Rule
{
	bool Check(Board* board) override
	{
		bool isnotfill = false;
		for (int i = 0; i < board->GetPlacesCount(); i++)
		{
			isnotfill = isnotfill || (board->GetPos(i) == ' ');
		}
		return !isnotfill;
	}

	bool IsWin() { return false; }
};

class Player
{
private:
	string _name;
	Piece* _piece;
public:
	Player(string name, Piece* piece)
	{
		_name = name;
		_piece = piece;
	}

	string GetName()
	{
		return _name;
	}

	Piece* GetPiece()
	{
		return _piece;
	}

	virtual int TryMove(Board* board) = 0;
};

class HumanPlayer : public Player
{
public:
	HumanPlayer(string name, Piece* piece) :Player(name, piece) {}
	int TryMove(Board* board) override
	{
		int position;
		cin >> position;
		return position - 1;
	}
};

class ComputerPlayer : public Player
{
public:
	ComputerPlayer(string name, Piece* piece) :Player(name, piece) {}

	int TryMove(Board* board) override
	{
		for (int i = 0; i < board->GetPlacesCount(); i++)
		{
			if (board->GetPos(i) == ' ')
			{
				cout << i + 1 << endl;
				return i;
			}
		}
		return -1;
	}

};

class BestComputerPlayer : public Player
{
public:
	BestComputerPlayer(string name, Piece* piece) :Player(name, piece) {}

	int TryMove(Board* board) override
	{
		bool flag = false;
		int pos = -1;
		do
		{
			pos = rand() % (board->GetPlacesCount());
			if (board->GetPos(pos) == ' ')
				flag = true;
		} while (!flag);
		cout << pos + 1 << endl;
		return pos;
	}

};

class SuperBestComputer :public Player
{
public:
	SuperBestComputer (string name, Piece* piece) :Player(name, piece) {}
	int TryMove(Board* board) override
	{
		return 1;
	}

};

class Piece
{
public:
	virtual bool CanMove(Board* board, int position) = 0;
	virtual char GetChar() = 0;
};

class X :public Piece
{
public:
	bool CanMove(Board* board, int position) override
	{
		return (board->GetPos(position) == ' ');
	}
	char GetChar() override
	{
		return 'X';
	}
};

class O :public Piece
{
public:
	bool CanMove(Board* board, int position) override
	{
		return (board->GetPos(position) == ' ');
	}
	char GetChar() override
	{
		return 'O';
	}
};

class Move
{
private:
	int _position;
	Player* _player;
public:
	Move(Player* player, int pos)
	{
		_player = player;
		_position = pos;
	}

	pair<Player*, int> GetMove()
	{
		return { _player, _position };
	}
};

class Game
{
private:
	vector<Move*> _moves;
	vector<Player*> _players;
	Board* _board;
	string ResultGame;
	vector<Rule*> _rules;

	bool HasWinner()
	{
		/*for (auto r : _rules)
		{
			if (r->IsWin() && r->Check(_board))
			{
				return true;
			}
		}
		return false;*/
		return (_board->rowCrossed()
			|| _board->columnCrossed()
			|| _board->diagonalCrossed());
	}

	bool IsBoardFill()
	{
		bool isnotfill = false;
		for (int i = 0; i < _board->GetPlacesCount(); i++)
		{
			isnotfill = isnotfill || (_board->GetPos(i) == ' ');
		}
		return !isnotfill;
	}
	void ShowInstructions()
	{
		printf("\t\t\t Tic-Tac-Toe\n\n");

		printf("Choose a cell numbered "
			"from 1 to 9 as below"
			" and play\n\n");

		printf("\t\t\t 1 | 2 | 3 \n");
		printf("\t\t\t------------\n");
		printf("\t\t\t 4 | 5 | 6 \n");
		printf("\t\t\t------------\n");
		printf("\t\t\t 7 | 8 | 9 \n\n");

		printf("-\t-\t-\t-\t-\t"
			"-\t-\t-\t-\t-\n\n");

		return;
	}
	void Initialise()
	{
		_board = new Board();
		for (int i = 0; i < _board->GetPlacesCount(); i++)
		{
			_board->SetPos(i, ' ');
		}
	}
public:
	Game(vector<Player*> players)
	{
		_players = players;
		_rules.push_back(new RowWin());
		_rules.push_back(new ColumnWin());
		_rules.push_back(new DiagonalWin());
		_rules.push_back(new IsFull());
	}


	void PlayTicTacToe()
	{
		Initialise();
		_moves.clear();
		ShowInstructions();
		int currentPlayer = 0;
		while (!HasWinner() && !IsBoardFill())
		{
			int pos = 0;
			do
			{
				cout << _players[currentPlayer]->GetName() << "-" << " Your turn:";
				pos = _players[currentPlayer]->TryMove(_board);
				if (!_players[currentPlayer]->GetPiece()->CanMove(_board, pos))
				{
					cout << "Turn is unavaliable!" << endl;
				}
			} while (!_players[currentPlayer]->GetPiece()->CanMove(_board, pos));
			_board->SetPos(pos, _players[currentPlayer]->GetPiece()->GetChar());
			_moves.push_back(new Move(_players[currentPlayer], pos));
			_board->ShowBoard();
			currentPlayer = currentPlayer == 0 ? 1 : 0;
		}
		currentPlayer = currentPlayer == 0 ? 1 : 0;
		if (HasWinner())
		{
			cout << "Winner is " << _players[currentPlayer]->GetName() << endl;
		}
		else
			cout << "Game over. Draw! " << endl;
	}

	vector<Move*> GetMoves()
	{
		return _moves;
	}

	string GetResult()
	{
		return ResultGame;
	}

};

int main()
{
	srand(time(NULL));
	vector<Player*> players(2);
	players[0] = new BestComputerPlayer("x", new X());
	players[1] = new BestComputerPlayer("o", new O());
	Game* game = new Game(players);
	game->PlayTicTacToe();
	cout << game->GetResult() << endl;
	return 0;
}
