#include "common.hpp"

#ifndef SDL_INCLUDES
#define SDL_INCLUDES
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#endif

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
class Texture
{
public:
    Texture();
    ~Texture();
    bool loadFromFile(std::string path);
    void free();
    void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int getWidth();
    int getHeight();

private:
    SDL_Texture *mTexture;

    int mWidth;
    int mHeight;
};

#endif
