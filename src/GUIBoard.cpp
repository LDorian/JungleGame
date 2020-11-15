#include "../include/GUIBoard.hpp"
#include "../include/GameState.hpp"

void GUIBoard::updateFocus(int x, int y)
{

    // Pour les extremités du board
    if ((x > 525) || (y > 675))
    {
        focus.x = -1;
        focus.y = -1;
        return;
    }
    else
    {

        focus.x = (int)(x) / 53;
        focus.y = (int)(y) / 68;
    }
}

int GUIBoard::indexToPixel(int index)
{

    if ((index < 0) || (index > 9))
    {
        printf("Clic invalide");
        return -1;
    }

    return (index * 75);
}

void GUIBoard::renderPieceOnBoard(PieceName piece, int cor, int ix, int iy)
{

    if (ix < 0 || iy < 0)
    {
        return;
    }

    if (cor == 0)
    {
        bluePieces[(int)piece].render(indexToPixel(ix), indexToPixel(iy));
    }
    else
    {
        redPieces[(int)piece].render(indexToPixel(ix), indexToPixel(iy));
    }
}

void GUIBoard::renderAllPieces(States *states)
{
    int i = 0;
    // Render blanc
    for (i = 0; i < 8; i++)
    {
        renderPieceOnBoard(states->blue_pieces[i]->GetName(), 0, states->blue_pieces[i]->GetPositionX(), states->blue_pieces[i]->GetPositionY());
    }

    // Render noir
    for (i = 0; i < 8; i++)
    {
        renderPieceOnBoard(states->red_pieces[i]->GetName(), 1, states->red_pieces[i]->GetPositionX(), states->red_pieces[i]->GetPositionY());
    }
}

bool GUIBoard::checkMovement(States *states)
{
    bool move = false;
    if (focusedPiece != NULL)
    {
        if (focusedPiece->GetName() != PieceName::Empty)
        {
            move = states->MovePiece(focusedPiece, focus.x, focus.y);
        }
    }
    return move;
}

// Choisir qui commence
bool GUIBoard::choosePieceTurn(GameState *gm, States *states)
{
    bool selected = false;
    bool blue = true;
    int x = -1, y = -1;
    SDL_Event e;

    while (selected == false)
    {

        while (SDL_PollEvent(&e) != 0)
        {

            // Quitter
            if (e.type == SDL_QUIT)
            {
                gm->setGameState(GameMode::GAME_MODE_QUIT);
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION)
            {
                switch (e.type)
                {
                case SDL_MOUSEBUTTONDOWN:
                    selected = true;
                    if (y > 340)
                    {
                        blue = true;
                    }
                    else
                    {
                        blue = false;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&x, &y);
                    break;
                }
            }

            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            // Rendu board
            gBoard.render(0, 0);

            renderAllPieces(states);

            // Rendu selection
            if (y < 340)
            {
                selection.render(0, 0);
            }
            else
            {
                selection.render(0, 360);
            }

            SDL_RenderPresent(gRenderer);
        }
    }
    return blue;
}