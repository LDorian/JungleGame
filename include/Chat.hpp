#ifndef PIECE_HPP_INCLUDED
#include "../include/Piece.hpp"
#endif

#ifndef Chat_HPP_INCLUDED
#define Chat_HPP_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class Chat : public Piece
{
public:
  Chat(bool, int, int);
  ~Chat();
  using Piece::GetColor;
  using Piece::GetName;
  using Piece::GetValue;
  using Piece::GetPositionX;
  using Piece::GetPositionY;
  bool IsMovementPossible(int, int);
  bool IsInWater(int, int);
};

#endif
