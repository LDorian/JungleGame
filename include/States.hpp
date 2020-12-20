#ifndef STATES_HPP_INCLUDED
#define STATES_HPP_INCLUDED

#include "Piece.hpp"
#include "GameState.hpp"

enum class Obstacles
{
  Empty,
  Friend,
  Enemy
};
enum class GameResult
{
  blueWins,
  redWins,
  Draw,
  NoContest
};

enum class Level
{
  Facile,
  Moyen,
  Difficile
};

class States
{
private:
  void EatPiece(int, int); // Eat piece in x,y.
  bool pieceTurn;          // True - tour des bleus, False - tour des rouges.
  Piece *emptyPiece = new Piece();

public:
  // Vector pieces on board
  Piece *blue_pieces[9];
  Piece *red_pieces[9];

  States();
  Obstacles IsInTheWay(Piece *, int, int);
  Obstacles IsInTheSpot(Piece *, int, int);
  bool MovePiece(Piece *, int, int);  // Move the piece only if possible, returning true if possible and false otherwise (being able to eat a piece when an enemy is in the final square)
  int CheckValues(Piece *, int, int); // Check if piece as a lower value that the piece which will get eat
  int IsInBase();
  GameResult WhoWon(void);
  bool IsPositionValid(Piece *, int, int); // If move position is valid
  Piece *GetPiece(int, int);               // From x and y, return piece
  bool SetPiece(Piece *, int, int);        // Function which places the piece in an X, Y returns true if piece placed there and false if not
  void SetPieceTurn(bool);
  bool GetPieceTurn(void);
  void KillAllPieces(void);

  void IAMove(bool, Level);

  void Save(GameMode);
  void Load(GameMode);
};

#endif
