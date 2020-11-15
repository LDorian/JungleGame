#ifndef PIECE_HPP_INCLUDED
#include "../include/Piece.hpp"
#endif

#ifndef Loup_HPP_INCLUDED
#define Loup_HPP_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class Loup : public Piece
{
public:
  Loup(bool, int, int);
  ~Loup();
  using Piece::GetColor;
  using Piece::GetName;
  using Piece::GetPositionX;
  using Piece::GetPositionY;
  bool IsMovementPossible(int, int);
};

#endif
