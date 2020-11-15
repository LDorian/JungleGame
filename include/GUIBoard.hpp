#include "Piece.hpp"
#include "States.hpp"
#include "common.hpp"

#ifndef GUIBOARD_HPP
#define GUIBOARD_HPP

class GUIBoard
{
public:
    void updateFocus(int x, int y);                                    // Refresh after clic
    int indexToPixel(int index);                                       // Conversion pixel to case
    void renderPieceOnBoard(PieceName piece, int cor, int ix, int iy); // Render piece on board
    void renderAllPieces(States *states);
    bool checkMovement(States *states); // Check if move is possible
    bool choosePieceTurn(GameState *gm, States *states);

    SDL_Rect board[7][9];       // Board
    SDL_Point focus = {-1, -1}; // clic
    Piece *focusedPiece = NULL; // dernniere piece cliquée
};

#endif
