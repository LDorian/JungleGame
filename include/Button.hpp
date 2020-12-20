#include "GameState.hpp"
#include "Piece.hpp"

#ifndef SDL_INCLUDES
#define SDL_INCLUDES
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#endif

#include "common.hpp"

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>

enum class ButtonSprite
{
    BUTTON_SPRITE_PVP = 0,
    BUTTON_SPRITE_IA = 1,
    BUTTON_SPRITE_ONLINE = 2,
    BUTTON_SPRITE_QUIT = 3,
    BUTTON_SPRITE_CONTINUE = 4,
    BUTTON_SPRITE_SAVE = 5,
    BUTTON_SPRITE_LOAD = 6,
    BUTTON_SPRITE_MAIN_MENU = 7,
    BUTTON_SPRITE_TOTAL = 8
};

//The mouse button
class Button
{
public:
    //Button constants
    static const int BUTTON_WIDTH = 263;
    static const int BUTTON_HEIGHT = 338;
    static const int TOTAL_BUTTONS = 8;

    //Initializes internal variables
    Button();

    //Sets top left position
    void setPosition(int x, int y);

    void setCurrentSprite(ButtonSprite sprite);

    //Handles mouse event
    void handleEvent(SDL_Event *e, GameState *gm);

    //Shows button sprite
    void render();

private:
    //Top left position
    SDL_Point m_Position;

    //Currently used global sprite
    ButtonSprite m_CurrentSprite;
    int check = 0;
};

#endif
