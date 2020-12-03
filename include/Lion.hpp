#ifndef PIECE_HPP_INCLUDED
#include "../include/Piece.hpp"
#endif

#ifndef Lion_HPP_INCLUDED
#define Lion_HPP_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class Lion : public Piece
{
public:
  Lion(bool, int, int);
  ~Lion();
  using Piece::GetColor;
  using Piece::GetName;
  using Piece::GetPositionX;
  using Piece::GetPositionY;
  using Piece::GetValue;
  bool IsMovementPossible(int, int);
  bool IsInWater(int, int);

private:
  bool moveOne(int, int);
};

#endif
