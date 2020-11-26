#include "../include/Tigre.hpp"

Tigre::Tigre(bool isblue, int position_X, int position_Y)
{
  this->name = PieceName::Tigre;
  this->isblue = isblue;
  this->position_X = position_X;
  this->position_Y = position_Y;
  isAlive = true;
}

Tigre::~Tigre()
{
}

bool Tigre::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
{
  if (FinalPosition_X >= 0 && FinalPosition_Y >= 0 && FinalPosition_X < 8 && FinalPosition_Y < 8 && isAlive)
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
