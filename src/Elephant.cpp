#include "../include/Elephant.hpp"

Elephant::Elephant(bool isblue, int position_X, int position_Y)
{
  this->name = PieceName::Elephant;
  this->value = PieceValue::Elephant;
  this->isblue = isblue;
  this->position_X = position_X;
  this->position_Y = position_Y;
  isAlive = true;
}

Elephant::~Elephant()
{
}

bool Elephant::moveOne(int movement_x, int movement_y)
{
  if ((movement_y == 1 || movement_y == -1) && movement_x == 0)
    return true;
  else if ((movement_x == 1 || movement_x == -1) && movement_y == 0)
    return true;
  return false;
}

bool Elephant::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
{
  if (FinalPosition_X >= 0 && FinalPosition_Y >= 0 && FinalPosition_X < 7 && FinalPosition_Y < 9 && isAlive && IsInWater(FinalPosition_X, FinalPosition_Y) == false)
  {
    int movement_x = FinalPosition_X - position_X;
    int movement_y = FinalPosition_Y - position_Y;

    if (GetColor() == 1)
    {
      if (FinalPosition_X == 3 && FinalPosition_Y == 0)
      {
        return false;
      }
      else
      {
        return moveOne(movement_x, movement_y);
      }
    }
    else if (GetColor() == 0)
    {
      if (FinalPosition_X == 3 && FinalPosition_Y == 8)
      {
        return false;
      }
      else
      {
        return moveOne(movement_x, movement_y);
      }
    }
  }

  return false;
}

bool Elephant::IsInWater(int x, int y)
{
  if ((x > 0 && x < 3 || x > 3 && x < 6) && (y > 2 && y < 6))
    return true;
  else
    return false;
}

bool Elephant::IsInTrap(int x, int y)
{
  if (GetColor() == 0)
  {
    if (((x == 2 || x == 4) && y == 0) || (x == 3 && y == 1))
    {
      this->value = PieceValue::Empty;
      return true;
    }
    else
    {
      this->value = PieceValue::Elephant;
      return false;
    }
  }
  else
  {
    if (((x == 2 || x == 4) && y == 8) || (x == 3 && y == 7))
    {
      this->value = PieceValue::Empty;
      return true;
    }
    else
    {
      this->value = PieceValue::Elephant;
      return false;
    }
  }
}