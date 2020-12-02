#include "../include/Piece.hpp"

// Constructeur
Piece::Piece()
{
}

// Destructeur
Piece::~Piece()
{
}

bool Piece::GetColor()
{
  return isblue;
}

PieceName Piece::GetName()
{
  return name;
}

PieceValue Piece::GetValue()
{
  return value;
}

int Piece::GetPositionX()
{
  return position_X;
}


int Piece::GetPositionY()
{
  return position_Y;
}

bool Piece::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
{
  return false;
}

bool Piece::IsInWater(int FinalPosition_X, int FinalPosition_Y)
{
  return false;
}
void Piece::SetPosition(int position_X, int position_Y)
{
  if(isAlive)
  {
    this->position_X = position_X;
    this->position_Y = position_Y;
  }
}

bool Piece::GetIsAlive()
{
  return isAlive;
}

void Piece::SetDead()
{
  isAlive = false;
  this->position_X = -1;
  this->position_Y = -1;
}

void Piece::WakeFromDead()
{
  isAlive = true;
}
