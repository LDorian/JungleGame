#ifndef PIECE_HPP_INCLUDED
#define PIECE_HPP_INCLUDED

#include <iostream>
#include <string>

enum class PieceName
{
  Empty,
  Rat,
  Chat,
  Chien,
  Loup,
  Panthere,
  Tigre,
  Lion,
  Elephant
};

using namespace std;

class Piece
{
protected:
  PieceName name = PieceName::Empty; // Quel piece a partir de l'enum
  bool isblue = false;               // Team
  int position_X = -1;
  int position_Y = -1;
  bool isAlive = false;

public:
  Piece();
  ~Piece();
  int PieceValue = -1;
  bool GetColor();
  PieceName GetName();
  int GetPositionX();
  int GetPositionY();
  virtual bool IsMovementPossible(int, int);
  virtual void SetDiagonalEnemy(bool, bool);
  void SetPosition(int, int);
  bool GetIsAlive();
  void WakeFromDead();
  void SetDead();
};

#endif
