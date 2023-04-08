#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Base class for chess pieces
class ChessPiece
{
protected:
    int row, col;
    char color;
    string name;

public:
    ChessPiece(int r, int c, char clr, string n) : row(r), col(c), color(clr), name(n) {}

    virtual bool validMove(int r, int c) = 0;

    virtual void move(int r, int c)
    {
        if (validMove(r, c))
        {
            row = r;
            col = c;
            cout << "Moved " << name << " to " << char(col + 'a') << row + 1 << endl;
        }
        else
        {
            cout << "Invalid move" << endl;
        }
    }

    char getColor()
    {
        return color;
    }

    string getName()
    {
        return name;
    }

    int getRow()
    {
        return row;
    }

    int getCol()
    {
        return col;
    }
};

// Derived class for Pawn piece
class Pawn : public ChessPiece
{
public:
    Pawn(int r, int c, char clr) : ChessPiece(r, c, clr, "Pawn") {}

    virtual bool validMove(int r, int c)
    {
        if (color == 'w')
        {
            if (row == 1 && r == 3 && col == c)
            {
                return true;
            }
            else if (r == row + 1 && col == c)
            {
                return true;
            }
        }
        else
        {
            if (row == 6 && r == 4 && col == c)
            {
                return true;
            }
            else if (r == row - 1 && col == c)
            {
                return true;
            }
        }
        return false;
    }
};

// Derived class for Rook piece
class Rook : public ChessPiece
{
public:
    Rook(int r, int c, char clr) : ChessPiece(r, c, clr, "Rook") {}

    virtual bool validMove(int r, int c)
    {
        if (r == row || c == col)
        {
            return true;
        }
        return false;
    }
};

// Derived class for Knight piece
class Knight : public ChessPiece
{
public:
    Knight(int r, int c, char clr) : ChessPiece(r, c, clr, "Knight") {}

    virtual bool validMove(int r, int c)
    {
        int rowDiff = abs(r - row);
        int colDiff = abs(c - col);
        if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))
        {
            return true;
        }
        return false;
    }
};

// Derived class for Bishop piece
class Bishop : public ChessPiece
{
public:
    Bishop(int r, int c, char clr) : ChessPiece(r, c, clr, "Bishop") {}

    virtual bool validMove(int r, int c)
    {
        int rowDiff = abs(r - row);
        int colDiff = abs(c - col);
        if (rowDiff == colDiff)
        {
            return true;
        }
        return false;
    }
};

// Derived class for Queen piece
class Queen : public ChessPiece
{
public:
    Queen(int r, int c, char clr) : ChessPiece(r, c, clr, "Queen") {}

    virtual bool validMove(int r, int c)
    {
        int rowDiff = abs(r - row);
        int colDiff = abs(c - col);
        if (r == row || c == col || rowDiff == colDiff)
        {
            return true;
        }
        return false;
    }
};
// Derived class for King piece
class King : public ChessPiece
{
public:
    King(int r, int c, char clr) : ChessPiece(r, c, clr, "King") {}

    virtual bool validMove(int r, int c)
    {
        int rowDiff = abs(r - row);
        int colDiff = abs(c - col);
        if (rowDiff <= 1 && colDiff <= 1)
        {
            return true;
        }
        return false;
    }
};
// Chess board class to manage the game
class ChessBoard
{
private:
    vector<ChessPiece *> pieces;

public:
    ChessBoard()
    {
        // Create and add white pieces
        pieces.push_back(new Rook(0, 0, 'w'));
        pieces.push_back(new Knight(0, 1, 'w'));
        pieces.push_back(new Bishop(0, 2, 'w'));
        pieces.push_back(new Queen(0, 3, 'w'));
        pieces.push_back(new King(0, 4, 'w'));
        pieces.push_back(new Bishop(0, 5, 'w'));
        pieces.push_back(new Knight(0, 6, 'w'));
        pieces.push_back(new Rook(0, 7, 'w'));
        for (int i = 0; i < 8; i++)
        {
            pieces.push_back(new Pawn(1, i, 'w'));
        }
        // Create and add black pieces
        pieces.push_back(new Rook(7, 0, 'b'));
        pieces.push_back(new Knight(7, 1, 'b'));
        pieces.push_back(new Bishop(7, 2, 'b'));
        pieces.push_back(new Queen(7, 3, 'b'));
        pieces.push_back(new King(7, 4, 'b'));
        pieces.push_back(new Bishop(7, 5, 'b'));
        pieces.push_back(new Knight(7, 6, 'b'));
        pieces.push_back(new Rook(7, 7, 'b'));
        for (int i = 0; i < 8; i++)
        {
            pieces.push_back(new Pawn(6, i, 'b'));
        }
    }
    // Get the piece at the specified location
    ChessPiece *getPiece(int r, int c)
    {
        for (int i = 0; i < pieces.size(); i++)
        {
            if (pieces[i]->getRow() == r && pieces[i]->getCol() == c)
            {
                return pieces[i];
            }
        }
        return nullptr;
    }
    // Move a piece from one location to another
    void movePiece(int fromRow, int fromCol, int toRow, int toCol)
    {
        ChessPiece *piece = getPiece(fromRow, fromCol);
        if (piece != nullptr)
        {
            piece->move(toRow, toCol);
        }
    }
    // Print the current state of the board
    void printBoard()
    {
        cout << endl
             << "  a  b  c  d  e  f  g  h" << endl;
        cout << " +------------------------+" << endl;
        for (int r = 0; r < 8; r++)
        {
            cout << r + 1 << "|";
            for (int c = 0; c < 8; c++)
            {
                ChessPiece *piece = getPiece(r, c);
                if (piece != nullptr)
                {
                    cout << piece->getColor() << piece->getName()[0] << " ";
                }
                else
                {
                    cout << " * ";
                }
            }
            cout << "|" << r + 1 << endl;
        }
        cout << " +------------------------+" << endl;
        cout << "  a  b  c  d  e  f  g  h" << endl
             << endl;
    }
};
int main()
{
    ChessBoard board;
    // Print the initial state of the board
    board.printBoard();
    // Move a piece and print the updated state of the board
    board.movePiece(1, 4, 3, 4);
    board.movePiece(7, 3, 3, 3);
    board.printBoard();
    // Player 2 move a piece
    return 0;
}