#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "Texture.hpp"
#include "common.hpp"

#include <string>

class Graphics
{
public:
    bool init();
    bool loadMedia();
    void close();

    const int SCREEN_WIDTH = 525;
    const int SCREEN_HEIGHT = 675;
};
