#include "../include/Chien.hpp"

Chien::Chien(bool isblue, int position_X, int position_Y)
{
  this->name = PieceName::Chien;
  this->isblue = isblue;
  this->position_X = position_X;
  this->position_Y = position_Y;
  isAlive = true;
}

Chien::~Chien()
{
}

bool Chien::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
{
  if (FinalPosition_X >= 0 && FinalPosition_Y >= 0 && FinalPosition_X < 8 && FinalPosition_Y < 8 && isAlive)
  {
    int movement_x = FinalPosition_X - position_X;
    int movement_y = FinalPosition_Y - position_Y;
    
    if((movement_y == 1 || movement_y == -1) && movement_x == 0)
      return true;
    else if((movement_x == 1 || movement_x == -1) && movement_y == 0)
      return true;
  }

  return false;
}
