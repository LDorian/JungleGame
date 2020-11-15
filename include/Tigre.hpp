#ifndef PIECE_HPP_INCLUDED
#include "../include/Piece.hpp"
#endif

#ifndef Tigre_HPP_INCLUDED
#define Tigre_HPP_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class Tigre : public Piece
{
public:
  Tigre(bool, int, int);
  ~Tigre();
  using Piece::GetColor;
  using Piece::GetName;
  using Piece::GetPositionX;
  using Piece::GetPositionY;
  bool IsMovementPossible(int, int);
};

#endif
