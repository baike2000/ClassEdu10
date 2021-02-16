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
		board[position / 3][position % 3] = value;
	}
	char GetPos(int position)
	{
		return board[position / 3][position % 3];
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
		for (int i = 0; i < 9; i++)
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
		return { _player, _position + 1};
	}
};

class Game
{
private:
	vector<Move*> _moves;
	vector<Player*> _players;
	Board* _board;

	bool HasWinner()
	{
		return (_board->rowCrossed()
			|| _board->columnCrossed()
			|| _board->diagonalCrossed());
	}
	
	bool IsBoardFill()
	{
		bool isnotfill = false;
		for (int i = 0; i < 9; i++)
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
		for (int i = 0; i < 9; i++)
		{
			_board->SetPos(i, ' ');
		}
		_moves.clear();
	}
public:
	Game(vector<Player*> players)
	{
		_players = players;
	}


	void PlayTicTacToe()
	{
		Initialise();
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

};

int main()
{
	vector<Player*> players(2);
	players[0] = new ComputerPlayer("Computer 1", new X());
	players[1] = new ComputerPlayer("Computer 2", new O());
	/*string name;
	cout << "Enter name of Player: ";
	cin >> name;
	players[1] = new HumanPlayer(name, new X());*/

	Game* game = new Game(players);
	game->PlayTicTacToe();
	for (auto move : game->GetMoves())
	{
		cout << move->GetMove().first->GetName() <<
			" " << move->GetMove().second <<
			" " << move->GetMove().first->GetPiece()->GetChar()
			<< endl;
	}
	return (0);
}
