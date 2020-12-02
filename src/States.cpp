#include "../include/Piece.hpp"
#include "../include/Rat.hpp"
#include "../include/Chat.hpp"
#include "../include/Chien.hpp"
#include "../include/Loup.hpp"
#include "../include/Panthere.hpp"
#include "../include/Tigre.hpp"
#include "../include/States.hpp"
#include "../include/Lion.hpp"
#include "../include/Elephant.hpp"
#include "../include/GameState.hpp"
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

States::States(void)
{
  int i;

  // Init des pions
  blue_pieces[0] = new Rat(true, 0, 2);
  blue_pieces[1] = new Chat(true, 5, 1);
  blue_pieces[2] = new Chien(true, 1, 1);
  blue_pieces[3] = new Loup(true, 4, 2);
  blue_pieces[4] = new Panthere(true, 2, 2);
  blue_pieces[5] = new Tigre(true, 0, 0);
  blue_pieces[6] = new Lion(true, 6, 0);
  blue_pieces[7] = new Elephant(true, 6, 2);

  red_pieces[0] = new Rat(false, 6, 6);
  red_pieces[1] = new Chat(false, 1, 7);
  red_pieces[2] = new Chien(false, 5, 7);
  red_pieces[3] = new Loup(false, 2, 6);
  red_pieces[4] = new Panthere(false, 4, 6);
  red_pieces[5] = new Tigre(false, 6, 8);
  red_pieces[6] = new Lion(false, 0, 8);
  red_pieces[7] = new Elephant(false, 0, 6);

  pieceTurn = true;
}

// Piece dans le chemin ?

Obstacles States::IsInTheWay(Piece *piece, int position_X, int position_Y)
{
  int i, j;
  Piece **tmp;

  switch (piece->GetName())
  {
    // If needed add a case where animal and special moves -> For instance jump over water and so on
  default:
    int deplacement_x = position_X - piece->GetPositionX();
    int deplacement_y = position_Y - piece->GetPositionY();
    int deplacement_loop, vertical, horizontal;

    for (i = 0; i <= 7; i++)
    {
      tmp = blue_pieces;
      for (j = 0; j <= 1; j++)
      {
        deplacement_loop = 0;
        vertical = 0;
        horizontal = 0;

        deplacement_x != 0 ? deplacement_loop = deplacement_x : deplacement_loop = deplacement_y;
        deplacement_loop = abs(deplacement_loop);

        while (deplacement_loop > 1)
        {
          if (abs(deplacement_x) != abs(deplacement_y))
          {
            deplacement_y > 0 ? vertical++ : (deplacement_y != 0 ? vertical-- : vertical = 0);
            deplacement_x > 0 ? horizontal++ : (deplacement_x != 0 ? horizontal-- : horizontal = 0);
          }
          else
          {
            deplacement_y > 0 ? vertical++ : (deplacement_y != 0 ? vertical-- : vertical = 0);
            deplacement_x > 0 ? horizontal++ : (deplacement_x != 0 ? horizontal-- : horizontal = 0);
          }

          if ((tmp[i]->GetPositionX() == (piece->GetPositionX() + horizontal)) &&
              (tmp[i]->GetPositionY() == (piece->GetPositionY() + vertical)))
          {
            if ((piece->GetColor() && tmp[i]->GetColor()) || (!piece->GetColor() && !tmp[i]->GetColor()))
            {
              return Obstacles::Friend;
            }
            else
            {
              return Obstacles::Enemy;
            }
          }
          deplacement_loop--;
        }
        tmp = red_pieces;
      }
    }
    return Obstacles::Empty;
    break;
  }
}

Obstacles States::IsInTheSpot(Piece *piece, int position_X, int position_Y)
{
  int i, j;
  Piece **tmp;

  for (i = 0; i <= 7; i++)
  {
    tmp = blue_pieces;
    for (j = 0; j <= 1; j++)
    {
      if ((tmp[i]->GetPositionX() == position_X) && (tmp[i]->GetPositionY() == position_Y))
      {
        if ((piece->GetColor() && tmp[i]->GetColor()) || (!piece->GetColor() && !tmp[i]->GetColor()))
        {
          return Obstacles::Friend;
        }
        else
        {
          return Obstacles::Enemy;
        }
      }
      tmp = red_pieces;
    }
  }
  return Obstacles::Empty;
}

bool States::MovePiece(Piece *piece, int position_X, int position_Y)
{
  Obstacles isIntheSpot = IsInTheSpot(piece, position_X, position_Y);
  SDL_Log("MOOOVE %d , %d", position_X, position_Y);
  if (piece->IsMovementPossible(position_X, position_Y) &&
      (IsInTheWay(piece, position_X, position_Y) == Obstacles::Empty) &&
      (isIntheSpot != Obstacles::Friend) && (pieceTurn == piece->GetColor()))
  {

    // if (piece->GetName() == PieceName::Tigre)
    //   //if(Blocked(piece->GetColor(), position_X, position_Y))
    //   return false;

    // if (piece->GetName() == PieceName::Rat) //If enemy in front of him and try to go in
    //   if (isIntheSpot == Obstacles::Enemy && (position_X - piece->GetPositionX() == 0))
    //     return false;
    
    if (isIntheSpot == Obstacles::Enemy && CheckValues(piece, position_X, position_Y) == true)
      EatPiece(position_X, position_Y);
    else if( isIntheSpot == Obstacles::Enemy && CheckValues(piece, position_X, position_Y) == false)
      return false;

    piece->SetPosition(position_X, position_Y);
    pieceTurn = !pieceTurn;
    return true;
  }
  return false;
}

//Check Values:

bool States::CheckValues(Piece *piece, int position_X, int position_Y)
{
  Piece **tmp;
  int i, j;
  tmp = blue_pieces;
  for(i = 0; i < 2; i++)
  {
    for(j = 0; j < 8; j++)
    {
      if ((tmp[j]->GetPositionX() == position_X) && (tmp[j]->GetPositionY() == position_Y))
      {
        if(piece>*tmp)
          return true; // If greater = true
        else
          return false;        
      }
    }
    tmp = red_pieces;
  }
  return false;
}

//Set Dead on eat
void States::EatPiece(int position_X, int position_Y)
{
  Piece **tmp; 
  int i, j;
  tmp = blue_pieces;
  for (i = 0; i < 2; i++)
  {
    for (j = 0; j < 8; j++)
    {
      if ((tmp[j]->GetPositionX() == position_X) && (tmp[j]->GetPositionY() == position_Y))
      {
        tmp[j]->SetDead();
      }
    }
    tmp = red_pieces;
  }
}

// bool States::IsInBase(bool baseSide)
// {
//   Piece **tmp;
//   Piece **tmp2;
//   int i, j, k, x, y;
//   if (baseSide)
//   {
//     tmp = blue_pieces;
//     tmp2 = red_pieces;
//   }
//   else
//   {
//     tmp = red_pieces;
//     tmp2 = blue_pieces;
//   }

//   for (i = 0; i < 9; i++)
//   {
//     if (tmp[i]->GetPositionX() == 3 && tmp[i]->GetPositionY() == 0)
//       return true;
//   }
//   return false;
// }

GameResult States::WhoWon(void)
{
  bool blue = false, red = false;
  int i;

  // Test winning condition
  //Array investigation
  // blue = IsInBase(true);
  // red = IsInBase(false);
  blue = !blue_pieces[1]->GetIsAlive();
  red = !red_pieces[1]->GetIsAlive();
  if (blue && red)
    return GameResult::Draw;

  if (!blue && !red)
  {
    for (i = 0; i < 9; i++)
    {
      if (blue_pieces[i]->GetIsAlive() || red_pieces[i]->GetIsAlive())
        return GameResult::NoContest;
    }
    return GameResult::Draw;
  }

  if (red)
    return GameResult::redWins;

  if (blue)
    return GameResult::blueWins;

  return GameResult::NoContest;
}

bool States::IsPositionValid(Piece *piece, int position_X, int position_Y)
{
  Obstacles obstacle;
  if (piece->GetName() == PieceName ::Tigre)
  {
    //if(Blocked(piece->GetColor(), position_X, position_Y))
    return false;
  }
  obstacle = IsInTheSpot(piece, position_X, position_Y);
  if (piece->IsMovementPossible(position_X, position_Y) &&
      (IsInTheWay(piece, position_X, position_Y) == Obstacles::Empty) &&
      (obstacle != Obstacles::Friend))
  {
    if ((piece->GetName() == PieceName ::Rat) && (obstacle == Obstacles::Enemy))
    {
      if (piece->GetPositionX() - position_X != 0)
        return true;
    }
    else
    {
      return true;
    }
  }
  return false;
}

Piece *States::GetPiece(int position_X, int position_Y)
{
  if ((position_X >= 0) && (position_Y >= 0) && (position_X < 8) && (position_Y < 8))
  {
    for (int i = 0; i < 8; i++)
    {
      if (blue_pieces[i]->GetPositionX() == position_X && blue_pieces[i]->GetPositionY() == position_Y)
        return blue_pieces[i];
      if (red_pieces[i]->GetPositionX() == position_X && red_pieces[i]->GetPositionY() == position_Y)
        return red_pieces[i];
    }
  }
  return emptyPiece;
}

bool States::SetPiece(Piece *piece, int position_X, int position_Y)
{
  if ((position_X >= 0) && (position_Y >= 0) && (position_X < 8) && (position_Y < 8))
    if (IsInTheSpot(piece, position_X, position_Y) == Obstacles::Empty)
    {
      piece->WakeFromDead();
      piece->SetPosition(position_X, position_Y);
      return true;
    }

  return false;
}

void States::SetPieceTurn(bool pieceTurn)
{
  this->pieceTurn = pieceTurn;
}

bool States::GetPieceTurn(void)
{
  return this->pieceTurn;
}

void States::KillAllPieces(void)
{
  int i;
  for (i = 0; i < 8; i++)
  {
    blue_pieces[i]->SetDead();
    red_pieces[i]->SetDead();
  }
}
