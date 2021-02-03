#include<iostream>
#include<algorithm>
#include <sstream>  
#include <string>
#include<vector>
#include<queue>
#include<map>

using namespace std;

class Board; //forward declaration
class Spot;  //forward declaration

class Piece
{
private:
    bool _killed = false;
    bool _white = false;
public:

    Piece(bool white)
    {
        _white = white;
    }

    bool IsWhite()
    {
        return _white;
    }

    bool IsKilled()
    {
        _killed;
    }

    void SetKilled(bool killed)
    {
        _killed = killed;
    }

    virtual bool CanMove(Board* board, Spot* start, Spot* end) = 0;

};

class Spot {
private:
    Piece* _piece;
    int _x;
    int _y;
public:
    Spot(int x, int y, Piece* piece)
    {
        _piece = piece;
        _x = x;
        _y = y;
    }

    Piece* GetPiece()
    {
        return _piece;
    }
    void SetPiece(Piece* piece)
    {
        _piece = piece;
    }

    int GetX()
    {
        return _x;
    }

    void SetX(int x)
    {
        _x = x;
    }

    int GetY()
    {
        return _y;
    }

    void SetY(int y)
    {
        _y = y;
    }
};

class King : public Piece
{
private:
    bool _castlingDone = false;

public:
    King(bool white) :Piece(white) { }

    bool IsCastlingDone()
    {
        return _castlingDone;
    }

    void SetCastlingDone(bool castlingDone)
    {
        _castlingDone = castlingDone;
    }

    bool CanMove(Board* board, Spot* start, Spot* end) override
    {
        if (end->GetPiece()->IsWhite() == IsWhite()) {
            return false;
        }

        int x = abs(start->GetX() - end->GetX());
        int y = abs(start->GetY() - end->GetY());
        if (x + y == 1) {
            return true;
        }

        return IsValidCastling(board, start, end);
    }

    bool IsValidCastling(Board* board, Spot* start, Spot* end)
    {

        if (IsCastlingDone())
        {
            return false;
        }

    }

    bool IsCastlingMove(Spot* start, Spot* end)
    {
        // check if the starting and  
        // ending position are correct 
    }
};

class Pawn : public Piece
{
public:
    bool CanMove(Board* board, Spot* start, Spot* end) override
    {
        return true;
        // прописать куда двигается пешка
    }
};

class Board {
private:
    vector<vector<Spot*>> boxes;

public:
    Board()
    {
        ResetBoard();
    }

    Spot* GetBox(int x, int y)
    {
        return boxes[x][y];
    }

    void ResetBoard()
    {
        for (int i = 0; i < 8; i++)
        {
            vector<Spot*> v(8);
            boxes.push_back(v);
        }
        /*
        boxes[0][0] = new Spot(0, 0, new Rook(true));
        boxes[0][1] = new Spot(0, 1, new Knight(true));
        boxes[0][2] = new Spot(0, 2, new Bishop(true));
        boxes[1][0] = new Spot(1, 0, new Pawn(true));
        boxes[1][1] = new Spot(1, 1, new Pawn(true));

        boxes[7][0] = new Spot(7, 0, new Rook(false));
        boxes[7][1] = new Spot(7, 1, new Knight(false));
        boxes[7][2] = new Spot(7, 2, new Bishop(false));
        boxes[6][0] = new Spot(6, 0, new Pawn(false));
        boxes[6][1] = new Spot(6, 1, new Pawn(false));
        */
        // initialize remaining boxes without any piece 
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (boxes[i][j] == NULL)
                    boxes[i][j] = new Spot(i, j, NULL);
            }
        }
    }
};

class Player {
public:
    bool _whiteSide;
    bool _humanPlayer;

    bool IsWhiteSide()
    {
        return _whiteSide;
    }
    bool IsHumanPlayer()
    {
        return _humanPlayer;
    }
};

class HumanPlayer : public Player
{
public:
    HumanPlayer(bool whiteSide)
    {
        _whiteSide = whiteSide;
        _humanPlayer = true;
    }
};

class ComputerPlayer : public Player
{
public:
    ComputerPlayer(bool whiteSide)
    {
        _whiteSide = whiteSide;
        _humanPlayer = false;
    }
};

class Move {
private:
    Player* _player;
    Spot* _start;
    Spot* _end;
    Piece* _pieceMoved;
    Piece* _pieceKilled;
    bool _castlingMove = false;

public:
    Move(Player* player, Spot* start, Spot* end)
    {
        _player = player;
        _start = start;
        _end = end;
        _pieceMoved = start->GetPiece();
    }

    bool IsCastlingMove()
    {
        return _castlingMove;
    }

    void SetCastlingMove(bool castlingMove)
    {
        _castlingMove = castlingMove;
    }

    Spot* GetStart()
    {
        return _start;
    }

    Spot* GetEnd()
    {
        return _end;
    }

    void SetPieceKilled(Piece* piece)
    {
        _pieceKilled = piece;
    }

};

enum GameStatus
{
    ACTIVE,
    BLACK_WIN,
    WHITE_WIN,
    FORFEIT,
    STALEMATE,
    RESIGNATION
};

class Game
{
public:
    vector<Player*> _players;
    Board* _board;
    Player* _currentTurn;
    GameStatus _status;
    vector<Move*> _movesPlayed;

    void Initialize(Player* p1, Player* p2)
    {
        _players.push_back(p1);
        _players.push_back(p2);

        _board->ResetBoard();

        if (p1->IsWhiteSide())
        {
            _currentTurn = p1;
        }
        else
        {
            _currentTurn = p2;
        }

        _movesPlayed.clear();
    }

    bool IsEnd()
    {
        return GetStatus() != GameStatus::ACTIVE;
    }

    GameStatus GetStatus()
    {
        return _status;
    }

    void SetStatus(GameStatus status)
    {
        _status = status;
    }

    bool PlayerMove(Player* player, int startX, int startY, int endX, int endY)
    {
        Spot* startBox = _board->GetBox(startX, startY);
        Spot* endBox = _board->GetBox(startY, endY);
        Move* move = new Move(player, startBox, endBox);
        return MakeMove(move, player);
    }

    bool MakeMove(Move* move, Player* player)
    {
        Piece* sourcePiece = move->GetStart()->GetPiece();
        if (sourcePiece == NULL)
        {
            return false;
        }

        if (player != _currentTurn)
        {
            return false;
        }

        if (sourcePiece->IsWhite() != player->IsWhiteSide())
        {
            return false;
        }

        if (!sourcePiece->CanMove(_board, move->GetStart(), move->GetEnd()))
        {
            return false;
        }

        Piece* destPiece = move->GetEnd()->GetPiece();
        if (destPiece != NULL)
        {
            destPiece->SetKilled(true);
            move->SetPieceKilled(destPiece);
        }

        if (sourcePiece != NULL && dynamic_cast<King*>(sourcePiece)
            && dynamic_cast<King*>(sourcePiece)->IsCastlingMove(move->GetStart(), move->GetEnd()))
        {
            move->SetCastlingMove(true);
        }

        _movesPlayed.push_back(move);

        move->GetEnd()->SetPiece(move->GetStart()->GetPiece());
        move->GetStart()->SetPiece(NULL);

        if (destPiece != NULL && dynamic_cast<King*>(destPiece))
        {
            if (player->IsWhiteSide()) {
                SetStatus(GameStatus::WHITE_WIN);
            }
            else {
                SetStatus(GameStatus::BLACK_WIN);
            }
        }

        if (_currentTurn == _players[0])
        {
            _currentTurn = _players[1];
        }
        else
        {
            _currentTurn = _players[0];
        }

        return true;
    }
};

int main()
{
    Game* game = new Game();
    game->Initialize(new HumanPlayer(true), new ComputerPlayer(false));
    while (!game->IsEnd())
    {
    }
    return 0;
}