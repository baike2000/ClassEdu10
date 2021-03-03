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

class CheckPlayer : public Player
{
public:
	CheckPlayer(string name, Piece* piece) :Player(name, piece) {}
	int TryMove(Board* board) override
	{
		for (int i = 0; i < 9; i++)
		{
			if (board->GetPos(i) == ' ')
			{
				return i;
			}
		}
		return -1;
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
		return { _player, _position};
	}
};

class Game
{
private:
	vector<Move*> _moves;
	vector<Player*> _players;
	Board* _board;
	string ResultGame;

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
	}
public:
	Game(vector<Player*> players)
	{
		_players = players;
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

	void CheckGame()
	{
		Initialise();
		int pos = -1;
		int currentPlayer = 0;
		int currentMove = -1;
		while (!HasWinner() && !IsBoardFill() && currentMove < (int)_moves.size() - 1)
		{
			currentMove++;
			auto move = _moves[currentMove]->GetMove();
			if (_players[currentPlayer] != move.first)
			{
				ResultGame = "Game is not valid. Wrong move";
				return;
			}
			if (move.second < 0 || move.second > 8)
			{
				ResultGame = "Game is not valid. Move outside of board";
				return;
			}
			if (!_players[currentPlayer]->GetPiece()->CanMove(_board, move.second))
			{
				ResultGame = "Game is not valid. Cell is occupied";
				return;
			}
			_board->SetPos(move.second, _players[currentPlayer]->GetPiece()->GetChar());
			currentPlayer = currentPlayer == 0 ? 1 : 0;
		}
		currentPlayer = currentPlayer == 0 ? 1 : 0;
		if (currentMove < (int)_moves.size() - 1)
		{
			ResultGame = "Game is not valid. Move after finished game";
			return; 
		}
		if (!HasWinner() && _players[currentPlayer]->TryMove(_board) != -1)
		{
			ResultGame = "Game is valid. Game is not finished";
			return;
		}
		if (HasWinner())
		{
			ResultGame = "Game is valid. Player " + _players[currentPlayer]->GetName() + " win";
		}
		else
			ResultGame = "Game is valid. Draw";
	}

	vector<Move*> GetMoves()
	{
		return _moves;
	}

	void SetMoves(vector<Move*> moves)
	{
		_moves = moves;
	}

	string GetResult()
	{
		return ResultGame;
	}

};

int main()
{
	vector<Player*> players(2);
	players[0] = new CheckPlayer("x", new X());
	players[1] = new CheckPlayer("o", new O());
	vector<Move*> moves;
	int pos;
	string piece;
	while (cin >> pos)
	{
		cin >> piece;
		Player* player = players[1];
		if (piece == players[0]->GetName())
			player = players[0];

		Move* move = new Move(player, pos-1);
		moves.push_back(move);
	}
	Game* game = new Game(players);
	game->SetMoves(moves);
	game->CheckGame();
	cout << game->GetResult() << endl;
	return (0);
}
