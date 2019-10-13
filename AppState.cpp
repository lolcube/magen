#include "AppState.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <vector>


void AppState::handleKeydown(SDL_Event & ev) {
    switch (ev.key.keysym.scancode){
        case SDL_SCANCODE_K:
            if(scale <= 1){
                scale += 0.1;
                break;
            }
            scale += 1;
            break;
        case SDL_SCANCODE_J:
            if(scale <= 0.1){
                break;
            } 
            if(scale <= 1){
                scale -= 0.1;
                break;
            }
            scale -= 1;
            break;
        case SDL_SCANCODE_LEFT:
            mapXpos += 15;
            break;
        case SDL_SCANCODE_RIGHT:
            mapXpos -= 15;
            break;
        case SDL_SCANCODE_UP:
            mapYpos += 15;
            break;
        case SDL_SCANCODE_DOWN:
            mapYpos -= 15;
            break;
        case SDL_SCANCODE_F:
            bool isFullscreen = SDL_GetWindowFlags(winPtr) & SDL_WINDOW_FULLSCREEN;
            if(isFullscreen){
                SDL_SetWindowFullscreen(winPtr, 0);
                break;
            }
            SDL_SetWindowFullscreen(winPtr, SDL_WINDOW_FULLSCREEN);
            break;
    }

}
float AppState::getScale(){
    return scale;
}

int AppState::getMapXPos(){
    return mapXpos;
}

int AppState::getMapYPos(){
    return mapYpos;
}
