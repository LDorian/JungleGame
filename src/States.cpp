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
  //SDL_Log("MOOOVE %d , %d", position_X, position_Y);
  //SDL_Log("Water : %d", piece->IsInWater(position_X, position_Y));
  SDL_Log("Color %d ", piece->GetColor());
  if (piece->IsMovementPossible(position_X, position_Y) &&
      (IsInTheWay(piece, position_X, position_Y) == Obstacles::Empty) &&
      (isIntheSpot != Obstacles::Friend) && (pieceTurn == piece->GetColor()))
  {
    if (isIntheSpot == Obstacles::Enemy && CheckValues(piece, position_X, position_Y) == 1)
      EatPiece(position_X, position_Y);

    else if (isIntheSpot == Obstacles::Enemy && CheckValues(piece, position_X, position_Y) == 2)
      return false;

    else if (isIntheSpot == Obstacles::Enemy && piece->GetName() == PieceName::Rat && CheckValues(piece, position_X, position_Y) == 3 &&
             piece->IsInWater(piece->GetPositionX(), piece->GetPositionY()) == true)
      return false;

    else if (isIntheSpot == Obstacles::Enemy && piece->GetName() == PieceName::Rat && CheckValues(piece, position_X, position_Y) == 4)
      EatPiece(position_X, position_Y);

    else if (CheckValues(piece, position_X, position_Y) == 3)
      EatPiece(position_X, position_Y);

    SDL_Log("Base : %d", IsInBase());

    piece->IsInTrap(position_X, position_Y);
    SDL_Log("Is in trap %d", piece->IsInTrap(position_X, position_Y));

    piece->SetPosition(position_X, position_Y);
    pieceTurn = !pieceTurn;
    return true;
  }
  return false;
}

//Check Values:

int States::CheckValues(Piece *piece, int position_X, int position_Y) // Return 1 -> OK, Return 2 -> Pas OK, Return 3 -> Rat mange elephant, Return 4 -> Rat mange Rat
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
        if (piece->GetName() == PieceName::Elephant && tmp[j]->GetName() == PieceName::Rat) // Elephant can't eat Rat
          return 2;
        else if (piece->GetValue() > tmp[j]->GetValue()) // If greater = true
          return 1;
        else if (piece->GetName() == PieceName::Rat && tmp[j]->GetName() == PieceName::Elephant) //Rat eat elephant
          return 3;
        else if (tmp[j]->GetName() == PieceName::Rat) // Rat eat Rat
          return 4;
        else
          return 2;
      }
    }
    tmp = red_pieces;
  }
  return 2;
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

int States::IsInBase()
{
  Piece **tmp;
  int i, j;
  tmp = blue_pieces;

  for (i = 0; i < 2; i++)
  {
    for (j = 0; j < 8; j++)
    {
      if ((tmp[j]->GetPositionY() == 0 || tmp[j]->GetPositionY() == 8) && (tmp[j]->GetPositionX() == 3))
      {
        if (i == 0)
          return 1;
        else if (i == 1)
          return 2;
      }
    }
    tmp = red_pieces;
  }
  return 0;
}

GameResult States::WhoWon(void)
{
  // bool blue = false, red = false;
  int i;

  // Test winning condition
  //Array investigation
  // blue = IsInBase(true);
  // // red = IsInBase(false);
  // blue = !blue_pieces[1]->GetIsAlive();
  // red = !red_pieces[1]->GetIsAlive();

  // if (blue && red)
  //   return GameResult::Draw;

  if (!IsInBase() == 1 && !IsInBase() == 2)
  {
    for (i = 0; i < 9; i++)
    {
      if (blue_pieces[i]->GetIsAlive() || red_pieces[i]->GetIsAlive())
        return GameResult::NoContest;
    }
    return GameResult::Draw;
  }

  if (IsInBase() == 2)
    return GameResult::redWins;

  if (IsInBase() == 1)
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
  if ((position_X >= 0) && (position_Y >= 0) && (position_X < 9) && (position_Y < 9))
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

/**
 * 
 * 
 * Ici Gestion Meilleur movement possible pour les difficultés de l'IA
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
*/




void States::Save(GameMode mode)
{
  FILE *saveFile = NULL;
  int i, j;
  Piece **tmp;
  char print;

  if (mode == GameMode::GAME_MODE_PVP)
    saveFile = fopen("game.txt", "w");
  if (saveFile == NULL)
    return;

  fprintf(saveFile, "%s", "[Turn]:");
  fprintf(saveFile, "%c%c", pieceTurn ? 'b' : 'r', '\n');
  fprintf(saveFile, "%s", "[Blue Pieces Board]:");
  tmp = blue_pieces;
  for (j = 0; j < 2; j++)
  {
    for (i = 0; i < 8; i++)
    {
      if (tmp[i]->GetIsAlive())
      {
        switch (tmp[i]->GetName())
        {
        case PieceName::Rat:
          print = 'R';
          break;
        case PieceName::Chat:
          print = 'C';
          break;
        case PieceName::Chien:
          print = 'D';
          break;
        case PieceName::Loup:
          print = 'W';
          break;
        case PieceName::Panthere:
          print = 'P';
          break;
        case PieceName::Tigre:
          print = 'T';
          break;
        case PieceName::Lion:
          print = 'L';
          break;
        case PieceName::Elephant:
          print = 'E';
          break;
        }
        fprintf(saveFile, "%c,%d,%d%c", print, tmp[i]->GetPositionX(), tmp[i]->GetPositionY(), '|');
      }
      else
      {
        fprintf(saveFile, "%c%c", 'x', '|');
      }
    }
    if (j == 0)
    {
      fprintf(saveFile, "%c", '\n');
      fprintf(saveFile, "%s", "[Red Pieces Board ]:");
      tmp = red_pieces;
    }
  }
  fclose(saveFile);
}

void States::Load(GameMode mode)
{
  FILE *saveFile = NULL;
  int i, j;
  char read[170];
  Piece **tmp;

  if (mode == GameMode::GAME_MODE_PVP)
    saveFile = fopen("game.txt", "r");
  if (saveFile == NULL)
    return;

  fscanf(saveFile, "%[^\n].", read);

  read[7] == 'b' ? pieceTurn = true : pieceTurn = false;

  tmp = blue_pieces;
  for (j = 0; j < 2; j++)
  {
    fscanf(saveFile, "%170[^:].", read);
    read[0] = fgetc(saveFile);

    for (i = 0; i < 8; i++)
    {
      fscanf(saveFile, "%170[^|].", read);
      if (read[0] != 'x')
      {
        tmp[i]->WakeFromDead();
        tmp[i]->SetPosition(atoi(&read[2]), atoi(&read[4]));
      }
      else
      {
        tmp[i]->SetDead();
      }
      read[0] = fgetc(saveFile);
    }
    tmp = red_pieces;
  }

  fclose(saveFile);
}