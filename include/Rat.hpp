#ifndef PIECE_HPP_INCLUDED
#include "../include/Piece.hpp"
#endif

#ifndef Rat_HPP_INCLUDED
#define Rat_HPP_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class Rat : public Piece
{
public:
  Rat(bool, int, int);
  ~Rat();
  using Piece::GetColor;
  using Piece::GetName;
  using Piece::GetPositionX;
  using Piece::GetPositionY;
  bool IsMovementPossible(int, int);
};

#endif
