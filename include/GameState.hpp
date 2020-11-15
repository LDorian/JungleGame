#include "Texture.hpp"
#ifndef SDL_INCLUDES
#define SDL_INCLUDES
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#endif

#include "common.hpp"

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

enum class GameMode
{

    GAME_MODE_PVP = 0,
    GAME_MODE_QUIT = 3,
    GAME_MODE_CONTINUE = 4,
    GAME_MODE_MAIN_MENU = 7,
    GAME_MODE_PAUSE = 8,
    GAME_MODE_TOTAL = 9

};

class GameState
{

public:
    GameState();
    int pause = 0;

    GameMode getGameState();
    void setGameState(GameMode gameMode);
    void startStateMachine(GameMode gameMode);
    void renderPauseMenu();

private:
    GameMode gameState;

    void renderPVP();
    void renderMainMenu();
};

#endif
