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

enum class PieceValue
{
  Empty = 0,
  Rat = 1,
  Chat = 2,
  Chien = 3,
  Loup = 4,
  Panthere = 5,
  Tigre = 6,
  Lion = 7,
  Elephant = 8
};

using namespace std;

class Piece
{
protected:
  PieceName name = PieceName::Empty; // Quel piece a partir de l'enum
  PieceValue value = PieceValue::Empty;
  bool isblue = false;               // Team
  int position_X = -1;
  int position_Y = -1;
  bool isAlive = false;

public:
  Piece();
  ~Piece();
  bool GetColor();
  PieceName GetName();
  PieceValue GetValue();
  int GetPositionX();
  int GetPositionY();
  virtual bool IsMovementPossible(int, int);
  virtual bool IsInWater(int, int);
  virtual bool IsInTrap(int, int);
  void SetPosition(int, int);
  bool GetIsAlive();
  void WakeFromDead();
  void SetDead();
};

#endif
