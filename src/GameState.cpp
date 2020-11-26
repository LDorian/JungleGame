#include "../include/GameState.hpp"
#include <cstdio>
#include "../include/Piece.hpp"
#include "../include/States.hpp"
#include "../include/GUIBoard.hpp"

GameState::GameState()
{
    gameState = GameMode::GAME_MODE_MAIN_MENU;
}

GameMode GameState::getGameState()
{
    return gameState;
}

void GameState::setGameState(GameMode gameMode)
{
    gameState = gameMode;
}

void GameState::renderMainMenu()
{

    bool quit = false;

    for (int i = 0; i < Button::TOTAL_BUTTONS / 2; i++)
    {
        gButtons[i].setCurrentSprite((ButtonSprite)i);
    }

    // Gestion menu
    SDL_Event e;

    while (gameState == GameMode::GAME_MODE_MAIN_MENU)
    {

        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                gameState = GameMode::GAME_MODE_QUIT;
            }

            //Handle button events
            for (int i = 0; i < Button::TOTAL_BUTTONS / 2; ++i)
            {
                gButtons[i].handleEvent(&e, this);
            }
        }

        //Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        //Render buttons
        for (int i = 0; i < Button::TOTAL_BUTTONS / 2; ++i)
        {
            gButtons[i].render();
        }

        //Update screen
        SDL_RenderPresent(gRenderer);
    }
}

void GameState::renderPauseMenu()
{

    bool quit = false;
    pause = 1;

    for (int i = Button::TOTAL_BUTTONS / 2; i < Button::TOTAL_BUTTONS; i++)
    {
        gButtons[i].setCurrentSprite((ButtonSprite)i);
    }

    //Event handler
    SDL_Event e;

    while (pause == 1)
    {

        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                gameState = GameMode::GAME_MODE_QUIT;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    pause = 0;
                    break;
                }
            }

            //Handle button events
            for (int i = Button::TOTAL_BUTTONS / 2; i < Button::TOTAL_BUTTONS; ++i)
            {
                gButtons[i].handleEvent(&e, this);
            }
        }

        //Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        //Render buttons
        for (int i = Button::TOTAL_BUTTONS / 2; i < Button::TOTAL_BUTTONS; ++i)
        {
            gButtons[i].render();
        }

        //Update screen
        SDL_RenderPresent(gRenderer);
    }
}

void GameState::renderPVP()
{

    bool quit = false;
    bool showHint = false;
    bool showBest = false;
    int x = -1, y = -1;

    SDL_Event e;
    States *states = new States();
    GUIBoard *board = new GUIBoard();
    GameResult gameResult = GameResult::NoContest;

    states->SetPieceTurn(board->choosePieceTurn(this, states));

    while (gameState == GameMode::GAME_MODE_PVP)
    {

        while (SDL_PollEvent(&e) != 0)
        {

            if (e.type == SDL_QUIT)
            {
                gameState = GameMode::GAME_MODE_QUIT;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    renderPauseMenu();
                    break;
                }
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                switch (e.type)
                {
                case SDL_MOUSEBUTTONDOWN:
                    x = -1;
                    y = -1;
                    SDL_GetMouseState(&x, &y);
                    //SDL_Log("Avant %d, %d", x, y);

                    board->updateFocus((int)x, (int)y);



                    if (board->checkMovement(states))
                    {
                        board->focusedPiece = NULL;
                    }
                    else
                    {
                        //If no move, actual focus = piece focus
                        board->focusedPiece = states->GetPiece(board->focus.x, board->focus.y);
                    }
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        gBoard.render(0, 0);

        gameResult = states->WhoWon();
        if (gameResult == GameResult::NoContest)
        {

            if ((board->focusedPiece != NULL))
            {
                if (board->focusedPiece->GetName() != PieceName::Empty && (board->focusedPiece->GetColor() == states->GetPieceTurn()))
                {
                    pieceSelected.render(board->indexToPixel(board->focus.x), board->indexToPixel(board->focus.y) + 2);
                }
            }
            board->renderAllPieces(states);
        }
        else
        {
            endGame[(int)gameResult].render(0, 0);
        }
        SDL_RenderPresent(gRenderer);
    }
    delete states;
    delete board;
}

void GameState::startStateMachine(GameMode gameMode)
{

    gameState = gameMode;

    while (gameState != GameMode::GAME_MODE_QUIT)
    {

        switch (gameState)
        {
        case GameMode::GAME_MODE_MAIN_MENU:
            renderMainMenu();
            break;
        case GameMode::GAME_MODE_PVP:
            renderPVP();
            break;
        }
    }
}
