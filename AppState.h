#pragma once

#include <SDL2/SDL.h>

class AppState{
    public:
        float getScale();
        void handleKeydown(SDL_Event & ev);
        int getMapXPos();
        int getMapYPos();
        SDL_Window * winPtr;
        //AppState(){};

    private:
        int mapXpos = 0;
        int mapYpos = 0;
        float scale = 1;


};
