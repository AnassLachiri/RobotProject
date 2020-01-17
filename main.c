#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "functions.h"


int main(int argc, char *argv[])
{

    srand(time(NULL));
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


    // ***************** CIRCLE ******************** //

    SDL_Surface* circle = IMG_Load("circle.png");
    if(!circle){
        printf("Error  Surface!!\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture * texCircle = SDL_CreateTextureFromSurface(rend, circle);
    SDL_FreeSurface(circle);
    if(!texCircle){
        printf("Error  Texture!!\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    // ***************** RECTANGLE ******************** //



    SDL_Surface* rect = IMG_Load("rect.png");
    if(!rect){
        printf("Error  Surface!!\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture * texRect = SDL_CreateTextureFromSurface(rend, rect);
    SDL_FreeSurface(rect);
    if(!texRect){
        printf("Error  Texture!!\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    // ***************** SHAPE ******************** //




    SDL_Surface* shape = IMG_Load("triangle.png");
    if(!shape){
        printf("Error  Surface!!\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture * texShape = SDL_CreateTextureFromSurface(rend, shape);
    SDL_FreeSurface(shape);
    if(!texShape){
        printf("Error  Texture!!\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }    

    SDL_Rect shapes[6];
    for(int i = 1; i<=6; i++){
        shapes[i-1].x = i*100;
        shapes[i-1].y = 0;
        shapes[i-1].w = 100;
        shapes[i-1].h = 100;
    }

    

    
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    
    SDL_Rect pos;
    pos.x = w -150;
    pos.y = h/2 -50;
    pos.w = 100;
    pos.h = 100;


    SDL_Rect allWindow;
    allWindow.x = 0;
    allWindow.y = 0;
    allWindow.w = w;
    allWindow.h = h;

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

    int k;

    int rands[6];
    for (int i = 0; i<6; i++){
        k = rand()%3;
        rands[i] = k;
    }

    int shapeNbr = -1;
    int shapes_zone2[6]={0,0,0,0,0,0};


    while(1){
        
            int ev = handleEvents(window, &w, &h, &up, &right, &down, &left, &pos, shapes, rands, &shapeNbr, shapes_zone2, &menu, shapes_zone2);
            if(ev==1) break;


            // determine velocity
            int x_vel = 0;
            int y_vel = 0;
            controlRobot(up, down, right, left, speed, &x_vel, &y_vel);


            SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
            SDL_RenderClear(rend);

            rotationRobot(up, down, right, left, &rot);

            for(int i = 0; i<6; i++){
                switch (rands[i])
                {
                case 0:
                    SDL_RenderCopyEx(rend, texCircle  , NULL, &shapes[i], 0, NULL, SDL_FLIP_NONE);
                    break; 
                case 1:
                    SDL_RenderCopyEx(rend, texRect, NULL, &shapes[i], 0, NULL, SDL_FLIP_NONE);
                    break; 
                case 2:
                    SDL_RenderCopyEx(rend, texShape, NULL, &shapes[i], 0, NULL, SDL_FLIP_NONE);
                    break;  
                case -1:
                    SDL_RenderCopyEx(rend, texCircle  , NULL, &shapes[i], 0, NULL, SDL_FLIP_NONE);
                    break;


                }
            }



            SDL_SetRenderDrawColor(rend, 200, 200, 200, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawLine(rend, 100, 0, 100, 100);
            SDL_RenderDrawLine(rend, 100, 100, 700, 100);
            SDL_RenderDrawLine(rend, 700, 0, 700, 100);
            SDL_RenderDrawLine(rend, 100, 500, 100, 400);
            SDL_RenderDrawLine(rend, 100, 400, 700, 400);
            SDL_RenderDrawLine(rend, 700, 400, 700, 500);


            SDL_SetTextureColorMod( rend, 255, 255, 255 );
            SDL_RenderCopyEx(rend, tex, NULL, &pos, rot, NULL, SDL_FLIP_NONE);
            SDL_RenderPresent(rend);


            updateRobotPosition(&pos, x_vel, y_vel, w, h);
            if(shapeNbr!=-1){
                shapes[shapeNbr].x = pos.x;
                shapes[shapeNbr].y = pos.y;
            }

            SDL_Delay(delTime);
        
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
