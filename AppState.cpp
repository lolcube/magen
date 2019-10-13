#include "AppState.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <vector>


void AppState::handleKeydown(SDL_Event & ev) {
    switch (ev.key.keysym.scancode){
        case SDL_SCANCODE_K:
            if(AppState::scale <= 1){
                AppState::scale += 0.1;
                break;
            }
            AppState::scale += 1;
            break;
        case SDL_SCANCODE_J:
            if(AppState::scale <= 0.1){
                break;
            } 
            if(AppState::scale <= 1){
                AppState::scale -= 0.1;
                break;
            }
            AppState::scale -= 1;
            break;
        case SDL_SCANCODE_LEFT:
            AppState::mapXpos += 15;
            break;
        case SDL_SCANCODE_RIGHT:
            AppState::mapXpos -= 15;
            break;
        case SDL_SCANCODE_UP:
            AppState::mapYpos += 15;
            break;
        case SDL_SCANCODE_DOWN:
            AppState::mapYpos -= 15;
            break;
        case SDL_SCANCODE_F:
            bool isFullscreen = SDL_GetWindowFlags(AppState::winPtr) & SDL_WINDOW_FULLSCREEN;
            if(isFullscreen){
                SDL_SetWindowFullscreen(AppState::winPtr, 0);
                break;
            }
            SDL_SetWindowFullscreen(AppState::winPtr, SDL_WINDOW_FULLSCREEN);
            break;
    }

}
float AppState::getScale(){
    return AppState::scale;
}

int AppState::getMapXPos(){
    return AppState::mapXpos;
}

int AppState::getMapYPos(){
    return AppState::mapYpos;
}
