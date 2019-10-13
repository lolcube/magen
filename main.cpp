#include <SDL2/SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <map>
#include <functional>
#include "AppState.h"

SDL_Window *win;
SDL_Renderer *ren;

AppState app;


bool running = true;

using tilemap_t = std::vector<std::vector<int>>;
// using eventHandlers = std::map<SDL_Scancode, std::function<void(const SDL_Event &)>>;

struct tileset{
    SDL_Texture * tex;
    size_t w, h;
    size_t tw, th;
    inline operator SDL_Texture * (){return tex;}

};

void eventLoop(){
    SDL_Event ev;
    while (SDL_PollEvent(&ev)){
        switch (ev.type){
            case SDL_QUIT:
                running = false;
            case SDL_KEYDOWN:
                app.handleKeydown(ev);
                break;
        }
    }
}

void init(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_RESIZABLE, &win, &ren);
    app.winPtr = win;
}

tileset loadTileset(const char* filename, size_t tw, size_t th){
    int w, h;
    tileset t;
    memset(&t, 0, sizeof(t)); 
    if (unsigned char * imagedata = stbi_load(filename, &w, &h, 0, 4)){
        t.tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, w, h);
        t.w = w;
        t.h = h;
        t.tw = tw;
        t.th = th;
        SDL_UpdateTexture(t.tex, NULL, imagedata, 4*w);
        free(imagedata);
    }
    return t;
}

SDL_Rect getTile(tileset ts, size_t tid){
    SDL_Rect tile;
    tile.w = ts.tw;
    tile.h = ts.th;
    int tilesperrow = ts.w / ts.tw;
    tile.y = (tid / tilesperrow)*ts.tw;
    tile.x = (tid - (tilesperrow * (tid/tilesperrow)))*ts.tw;
    return tile;
}

void drawTMap(SDL_Renderer *renderer, tileset & ts, std::vector<std::vector<int>> tsmap){
    using tmap_t = std::vector<int>;
    SDL_Rect destrect;
    destrect.w = ts.tw;
    destrect.h = ts.th;
    destrect.x = app.getMapXPos();
    destrect.y = app.getMapYPos();
    SDL_SetRenderDrawColor(renderer, 0,0,255,255);
    SDL_RenderClear(renderer);
    for(const tmap_t& i : tsmap){
        for(const int & m : i){
            SDL_Rect tile = getTile(ts, m);
            SDL_RenderCopy(renderer, ts.tex, &tile ,&destrect);
            destrect.x += ts.tw;
        }
        destrect.x = app.getMapXPos();
        destrect.y += ts.th;
    }
    float scale = app.getScale();
    SDL_RenderSetScale(renderer,scale,scale); // i probably should do that outside of drawTMap so it doesn't need to be rescaled everytime. Not sure if this is important
    SDL_RenderPresent(renderer);

}

tilemap_t generateRandomMap(){
    tilemap_t vect;
    std::default_random_engine eng;
    std::uniform_int_distribution<int> gen(1, 19);
    vect.resize(255);
    for(auto & row : vect){
        row.resize(555);
        std::generate(row.begin(), row.end(), [&](){
            return gen(eng);
        });
    }
    return vect;
}
int main(int argc, char * argv[]){
    init();
    const char * tsfilep = "../tilemaps/tiles.png";
    tileset t = loadTileset(tsfilep, 16, 16);
    if(!t){
        printf("%s does not exist.\nGo find it yourself\n", tsfilep);
        return 1;
    }
    
    SDL_Rect tile = getTile(t, 1);
    tilemap_t vect = generateRandomMap();
    const int fps = 60;
    uint32_t ticks;
    uint32_t ticksafter;
    int rendertime;
    unsigned int frames = 0;
    unsigned int framescounted = 0;
    unsigned int avgFps = 0;
    while (running){
        ticks = SDL_GetTicks();

        eventLoop();
        drawTMap(ren, t, vect);
        ticksafter = SDL_GetTicks();
        rendertime = ticksafter - ticks;

        if (rendertime < (1000/fps)){
            SDL_Delay((1000/fps) - rendertime);
        }

        frames += (1000/ (SDL_GetTicks()-ticks));

        if ( frames >= 4000) { frames, framescounted = 0;}
        if (framescounted != 0) {avgFps = frames / framescounted;}
        ++framescounted;
    }   

    SDL_Quit();
    return 0;
}
