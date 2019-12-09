#include <stdio.h>
#include <SDL2/SDL.h>
#include "functions.h"


int main(int argc, char *argv[])
{
    // INIT SDL
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create SDL WINDOW
    SDL_Window * window = createWindow();
    if(window==NULL) return 1;

    // CREATE SDL RENDERER
    SDL_Renderer * rend = createRenderer(window);
    if(!rend) return 1;

    // CREATE SDL SURFACE
    SDL_Surface* surface = createSurface(window, rend);
    if(!surface) return 1;

    // CREATE SDL TEXTURE
    SDL_Texture * tex = createTexture(window, rend, surface);
    if(!tex) return 1;
    
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    
    SDL_Rect pos;
    pos.x = w -150;
    pos.y = h/2 -50;
    pos.w = 100;
    pos.h = 100;

    // Set the speed
    int speed = 3;

    // keep track of which inputs are given
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;

    // set the rotation of the texture
    int rot = 0;

    int fps = 60;
    float delTime = 1000.0/fps;

    while(1){
        int ev = handleEvents(window, &w, &h, &up, &right, &down, &left);
        if(ev==1) break;

        // determine velocity
        int x_vel = 0;
        int y_vel = 0;
        controlRobot(up, down, right, left, speed, &x_vel, &y_vel);


        SDL_SetRenderDrawColor(rend, 173, 222, 250, 255);
        SDL_RenderClear(rend);

        rotationRobot(up, down, right, left, &rot);
        
        SDL_SetTextureColorMod( rend, 255, 255, 255 );
        SDL_RenderCopyEx(rend, tex, NULL, &pos, rot, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(rend);


        updateRobotPosition(&pos, x_vel, y_vel, w, h);

        SDL_Delay(delTime);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
