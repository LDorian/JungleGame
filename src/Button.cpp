#include "../include/Button.hpp"

Button::Button()
{
    m_Position.x = 0;
    m_Position.y = 0;

    m_CurrentSprite = ButtonSprite::BUTTON_SPRITE_MAIN_MENU;
}

void Button::setPosition(int x, int y)
{
    m_Position.x = x;
    m_Position.y = y;
}

void Button::setCurrentSprite(ButtonSprite sprite)
{
    m_CurrentSprite = sprite;
}

void Button::handleEvent(SDL_Event *e, GameState *gm)
{
    check = 0; // If on it
    //If mouse event happened
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN)
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        bool inside = true;

        //Mouse is left of the button
        if (x < m_Position.x)
        {
            inside = false;
        }
        //Mouse is right of the button
        else if (x > m_Position.x + BUTTON_WIDTH)
        {
            inside = false;
        }
        //Mouse above the button
        else if (y < m_Position.y)
        {
            inside = false;
        }
        //Mouse below the button
        else if (y > m_Position.y + BUTTON_HEIGHT)
        {
            inside = false;
        }

        if (inside)
        {
            check = 1;
            //Set mouse over sprite
            switch (e->type)
            {
            case SDL_MOUSEBUTTONDOWN:
                switch (m_CurrentSprite)
                {
                case ButtonSprite::BUTTON_SPRITE_PVP:
                    gm->setGameState(GameMode::GAME_MODE_PVP);
                    break;
                case ButtonSprite::BUTTON_SPRITE_QUIT:
                    gm->setGameState(GameMode::GAME_MODE_QUIT);
                    break;
                case ButtonSprite::BUTTON_SPRITE_CONTINUE:
                    gm->pause = 0;
                    break;
                case ButtonSprite::BUTTON_SPRITE_SAVE:
                    gm->pause = 0;
                    gm->setGameState(GameMode::GAME_MODE_SAVE);
                    break;
                case ButtonSprite::BUTTON_SPRITE_LOAD:
                    gm->pause = 0;
                    gm->setGameState(GameMode::GAME_MODE_LOAD);
                    break;
                case ButtonSprite::BUTTON_SPRITE_MAIN_MENU:
                    gm->pause = 0;
                    gm->setGameState(GameMode::GAME_MODE_MAIN_MENU);
                    break;
                }
                break;
            }
        }
    }
}

void Button::render()
{
    //Show current button sprite
    gButtonSpriteSheetTexture.render(m_Position.x, m_Position.y, &(gSpriteClips[(int)m_CurrentSprite]));

    if (check == 1)
    {
        //Render a mouse on center top of selected one
        redPieces[(int)PieceName::Rat].render(m_Position.x + BUTTON_WIDTH / 2 - 40, m_Position.y);
    }
}
