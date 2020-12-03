#ifndef PIECE_HPP_INCLUDED
#include "../include/Piece.hpp"
#endif

#ifndef Panthere_HPP_INCLUDED
#define Panthere_HPP_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class Panthere : public Piece
{
public:
  Panthere(bool, int, int);
  ~Panthere();
  using Piece::GetColor;
  using Piece::GetName;
  using Piece::GetPositionX;
  using Piece::GetPositionY;
  using Piece::GetValue;
  bool IsMovementPossible(int, int);
  bool IsInWater(int, int);
  bool IsInTrap(int, int);

private:
  bool moveOne(int, int);
};

#endif
