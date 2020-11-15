#include "../include/Piece.hpp"
#include "../include/Rat.hpp"
#include "../include/Chat.hpp"
#include "../include/Chien.hpp"
#include "../include/Loup.hpp"
#include "../include/Panthere.hpp"
#include "../include/Tigre.hpp"
#include "../include/Lion.hpp"
#include "../include/Elephant.hpp"
#include "../include/States.hpp"

#include "../include/Graphics.hpp"
#include "common.hpp"

#ifndef SDL_INCLUDES                                                       
#define SDL_INCLUDES                                                       
#include <SDL2/SDL_image.h>                                                
#include <SDL2/SDL.h>                                                      
#endif    

#include <cstdio>
#include <string>


using namespace std;

int main( int argc, char* args[] ){

    Graphics *graphics = new Graphics();

    
    GameState *gm = new GameState(); 

	if( !graphics->init() ){
		printf( "Impossible d'initialiser!\n" );
	}
	else{

		if( !graphics->loadMedia() ){
			printf( "Impossible de charger les medias!\n" );
		}
		else{
            gm->startStateMachine(GameMode::GAME_MODE_MAIN_MENU);            
    	}

        graphics->close();

	    return 0;
    }
}

