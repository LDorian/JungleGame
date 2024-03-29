#ifndef PIECE_HPP_INCLUDED
#include "../include/Piece.hpp"
#endif

#ifndef Chien_HPP_INCLUDED
#define Chien_HPP_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class Chien : public Piece
{
public:
  Chien(bool, int, int);
  ~Chien();
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
