#include "../include/Chat.hpp"

Chat::Chat(bool isblue, int position_X, int position_Y)
{
  this->name = PieceName::Chat;
  this->isblue = isblue;
  this->position_X = position_X;
  this->position_Y = position_Y;
  isAlive = true;
}

Chat::~Chat()
{
}

bool Chat::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
{
  if (FinalPosition_X >= 0 && FinalPosition_Y >= 0 && FinalPosition_X < 8 && FinalPosition_Y < 8 && isAlive)
  {
    int movement_x = abs(FinalPosition_X - position_X);
    int movement_y = abs(FinalPosition_Y - position_Y);
    
    if ((movement_x == 1 && movement_y == 1))
    {
      return true;
    }
  }

  return false;
}
