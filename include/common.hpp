#ifndef TEXTURE_BUTTON_HPP
#define TEXTURE_BUTTON_HPP

#include "Button.hpp"
#include "Texture.hpp"

extern SDL_Rect gSpriteClips[(int)ButtonSprite::BUTTON_SPRITE_TOTAL];
extern Texture gCheckTexture;
extern Texture gButtonSpriteSheetTexture;
extern Button gButtons[Button::TOTAL_BUTTONS];

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;

extern Texture gBoard;
extern Texture bluePieces[9];
extern Texture redPieces[9];
extern Texture gChien;
extern Texture pieceSelected;
extern Texture endGame[3];
extern Texture selection;

#endif
