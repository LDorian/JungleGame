#include "../include/Rat.hpp"

Rat::Rat(bool isblue, int position_X, int position_Y)
{
  this->name = PieceName::Rat;
  this->isblue = isblue;
  this->position_X = position_X;
  this->position_Y = position_Y;
  isAlive = true;
}

Rat::~Rat()
{
}

bool Rat::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
{
  if(FinalPosition_X >= 0 && FinalPosition_Y >= 0 && FinalPosition_X < 8 && FinalPosition_Y < 8 && isAlive) 
  {
    int movement_x = FinalPosition_X - position_X;
    int movement_y = FinalPosition_Y - position_Y;
  }

  return false;
}
