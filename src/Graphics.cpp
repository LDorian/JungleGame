#include "../include/Graphics.hpp"
#include <cstdio>
#include "../include/Piece.hpp"
#include "../include/States.hpp"

// Gestion boutons souris
SDL_Rect gSpriteClips[(int)ButtonSprite::BUTTON_SPRITE_TOTAL];
Texture gCheckTexture;
Texture gButtonSpriteSheetTexture;
// Objets boutons
Button gButtons[Button::TOTAL_BUTTONS];
// Window
SDL_Window *gWindow = NULL;
// Renderer
SDL_Renderer *gRenderer = NULL;
// Les Textures
Texture gBoard;
Texture bluePieces[9];
Texture redPieces[9];
Texture gChien;
Texture pieceSelected;
Texture endGame[3];
Texture selection;

bool Graphics::loadMedia()
{
    bool success = true;

    // Chargement des textures
    if (!gBoard.loadFromFile("../assets/planJungle.bmp"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }

    if (!pieceSelected.loadFromFile("../assets/selected.png"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }

    if (!gChien.loadFromFile("../assets/chienR.bmp"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }

    if (!selection.loadFromFile("../assets/Teamselect.png"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }

    // Texture de fin de partie
    if (!endGame[(int)GameResult::blueWins].loadFromFile("../assets/Bwin.png"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }

    if (!endGame[(int)GameResult::redWins].loadFromFile("../assets/Rwin.png"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }

    if (!endGame[(int)GameResult::Draw].loadFromFile("../assets/draw.png"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }

    // Pieces bleue

    if (!bluePieces[(int)PieceName::Rat].loadFromFile("../assets/ratB.bmp"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }
    if (!bluePieces[(int)PieceName::Chat].loadFromFile("../assets/chatB.bmp"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }
    if (!bluePieces[(int)PieceName::Chien].loadFromFile("../assets/chienB.bmp"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }
    if (!bluePieces[(int)PieceName::Loup].loadFromFile("../assets/loupB.bmp"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }
    if (!bluePieces[(int)PieceName::Panthere].loadFromFile("../assets/panthereB.bmp"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }
    if (!bluePieces[(int)PieceName::Tigre].loadFromFile("../assets/tigreB.bmp"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }
    if (!bluePieces[(int)PieceName::Lion].loadFromFile("../assets/lionB.bmp"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }
    if (!bluePieces[(int)PieceName::Elephant].loadFromFile("../assets/elephantB.bmp"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }

    // Pieces Rouge

    if (!redPieces[(int)PieceName::Rat].loadFromFile("../assets/ratR.bmp"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }
    if (!redPieces[(int)PieceName::Chat].loadFromFile("../assets/chatR.bmp"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }
    if (!redPieces[(int)PieceName::Chien].loadFromFile("../assets/chienR.bmp"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }
    if (!redPieces[(int)PieceName::Loup].loadFromFile("../assets/loupR.bmp"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }
    if (!redPieces[(int)PieceName::Panthere].loadFromFile("../assets/panthereR.bmp"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }
    if (!redPieces[(int)PieceName::Tigre].loadFromFile("../assets/tigreR.bmp"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }
    if (!redPieces[(int)PieceName::Lion].loadFromFile("../assets/lionR.bmp"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }
    if (!redPieces[(int)PieceName::Elephant].loadFromFile("../assets/elephantR.bmp"))
    {
        printf("Failed to load texture!\n");
        success = false;
    }

    // Charger le menu du jeu
    if (!gButtonSpriteSheetTexture.loadFromFile("../assets/menus.png"))
    {
        printf("Failed to load button sprite texture!\n");
        success = false;
    }
    else
    {

        // Set up des sprites
        for (int i = 0; i < (int)ButtonSprite::BUTTON_SPRITE_TOTAL; ++i)
        {
            gSpriteClips[i].x = 0;
            gSpriteClips[i].y = i * 340;
            gSpriteClips[i].w = Button::BUTTON_WIDTH;
            gSpriteClips[i].h = Button::BUTTON_HEIGHT;
        }

        // Placer les boutons dans les coins
        gButtons[0].setPosition(0, 0);
        gButtons[1].setPosition(SCREEN_WIDTH - Button::BUTTON_WIDTH, 0);
        gButtons[2].setPosition(0, SCREEN_HEIGHT - Button::BUTTON_HEIGHT);
        gButtons[3].setPosition(SCREEN_WIDTH - Button::BUTTON_WIDTH, SCREEN_HEIGHT - Button::BUTTON_HEIGHT);
        gButtons[4].setPosition(0, 0);
        gButtons[5].setPosition(SCREEN_WIDTH - Button::BUTTON_WIDTH, 0);
        gButtons[6].setPosition(0, SCREEN_HEIGHT - Button::BUTTON_HEIGHT);
        gButtons[7].setPosition(SCREEN_WIDTH - Button::BUTTON_WIDTH, SCREEN_HEIGHT - Button::BUTTON_HEIGHT);
    }
    return success;
}

bool Graphics::init()
{

    bool success = true;
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf("Erreur SDL init : %s\n", SDL_GetError());
        success = false;
    }
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Erreur SDL init : %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Filtre de texture
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Pas de filtre de texture lineaire");
        }

        // Creation de la fenêtre
        gWindow = SDL_CreateWindow("JungleC | Gabin et Dorian", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Fenetre pas crée : %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Renderer
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL)
            {
                printf("Renderer erreur : %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Gesiton de la transparence
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Init des pngs
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image erreur: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

void Graphics::close()
{
    // libere les images
    gBoard.free();

    for (int i = 0; i < 9; i++)
    {
        bluePieces[i].free();
    }

    for (int i = 0; i < 9; i++)
    {
        redPieces[i].free();
    }
    // detruire la fenetre
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Fermer la SDL
    IMG_Quit();
    SDL_Quit();
}
