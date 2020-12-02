#include "../include/Panthere.hpp"

Panthere::Panthere(bool isblue, int position_X, int position_Y)
{
  this->name = PieceName::Panthere;
  this->isblue = isblue;
  this->position_X = position_X;
  this->position_Y = position_Y;
  isAlive = true;
}

Panthere::~Panthere()
{
}

bool Panthere::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
{
  if (FinalPosition_X >= 0 && FinalPosition_Y >= 0 && FinalPosition_X < 9 && FinalPosition_Y < 9 && isAlive && IsInWater(FinalPosition_X, FinalPosition_Y) == false)
  {
    int movement_x = FinalPosition_X - position_X;
    int movement_y = FinalPosition_Y - position_Y;
    if ((movement_y == 1 || movement_y == -1) && movement_x == 0)
      return true;
    else if ((movement_x == 1 || movement_x == -1) && movement_y == 0)
      return true;
  }

  return false;
}

bool Panthere::IsInWater(int x, int y)
{
  if ((x > 0 && x < 3 || x > 3 && x < 6) && (y > 2 && y < 6))
    return true;
  else
    return false;
}
