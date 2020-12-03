#ifndef PIECE_HPP_INCLUDED
#include "../include/Piece.hpp"
#endif

#ifndef Elephant_HPP_INCLUDED
#define Elephant_HPP_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class Elephant : public Piece
{
public:
  Elephant(bool, int, int);
  ~Elephant();
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
