#include "../include/Loup.hpp"
Loup::Loup(bool isblue, int position_X, int position_Y)
{
  this->name = PieceName::Loup;
  this->value = PieceValue::Loup;
  this->isblue = isblue;
  this->position_X = position_X;
  this->position_Y = position_Y;
  isAlive = true;
}

Loup::~Loup()
{
}

bool Loup::moveOne(int movement_x, int movement_y)
{
  if ((movement_y == 1 || movement_y == -1) && movement_x == 0)
    return true;
  else if ((movement_x == 1 || movement_x == -1) && movement_y == 0)
    return true;
  return false;
}

bool Loup::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
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

bool Loup::IsInWater(int x, int y)
{
  if ((x > 0 && x < 3 || x > 3 && x < 6) && (y > 2 && y < 6))
    return true;
  else
    return false;
}

bool Loup::IsInTrap(int x, int y)
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
      this->value = PieceValue::Loup;
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
      this->value = PieceValue::Loup;
      return false;
    }
  }
}