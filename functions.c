#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Window * createWindow(){
    //Create SDL WINDOW
    SDL_Window * window = SDL_CreateWindow(
        "Robot Game!!",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        700,
        480,
        SDL_WINDOW_RESIZABLE
    );

    if(window == NULL){
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        SDL_Quit();
        return NULL;
    }

    return window;
}


SDL_Renderer * createRenderer(SDL_Window * window){
    Uint32 renderer_flags = SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer * rend = SDL_CreateRenderer(window, -1 , renderer_flags);
    if(!rend){
        printf("Error  Renderer!!\n");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return NULL;
    }
}

SDL_Surface* createSurface(SDL_Window * window, SDL_Renderer * rend){
    SDL_Surface* surface = IMG_Load("robot.png");
    if(!surface){
        printf("Error  Surface!!\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return NULL;
    }
    return surface;
}

SDL_Texture * createTexture(SDL_Window * window, SDL_Renderer * rend, SDL_Surface * surface){
    SDL_Texture * tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if(!tex){
        printf("Error  Texture!!\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return NULL;
    }
    return tex;
}


int handleEvents(SDL_Window * window, int *w, int *h, int *up, int *right, int *down, int *left){
    SDL_Event e;
    if(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            return 1;
        }
        if(e.type == SDL_WINDOWEVENT){
            if(e.window.event == SDL_WINDOWEVENT_RESIZED){
                SDL_GetWindowSize(window, &w, &h);
            }
        }
        if(e.type == SDL_KEYDOWN){
            switch (e.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                *up = 1;
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                *left = 1;
                break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                *down = 1;
                break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                *right = 1;
                break;
            }
        }
        if(e.type == SDL_KEYUP){
            switch (e.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                *up = 0;
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                *left = 0;
                break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                *down = 0;
                break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                *right = 0;
                break;
            }
        }
    }
    return 0;
}


void controlRobot(int up, int down, int right, int left, int speed, int *x_vel, int *y_vel){
    if (up && !down) *y_vel = -speed;
    if (down && !up) *y_vel = speed;
    if (left && !right) *x_vel = -speed;
    if (right && !left) *x_vel = speed;

}


void rotationRobot(int up, int down, int right, int left, int *rot){
    if(down==1 && right==1){
        *rot = 135;
    }else if(left==1 && down==1){
        *rot = -135;
    }else if(left==1 && up==1){
        *rot = -45;
    }else if(up==1 && right==1){
        *rot = 45;
    }else if(right==1){
        *rot = 90;
    }else if(left==1){
        *rot = -90;
    }else if(up==1){
        *rot = 0;
    }else if(down==1){
        *rot = 180;
    }
}

void updateRobotPosition(SDL_Rect *pos, int x_vel, int y_vel, int w, int h){
    pos->x+=x_vel;
    pos->y+=y_vel;
    if(pos->x>w-100) pos->x=w-100;
    if(pos->x<0) pos->x=0;
    if(pos->y<0) pos->y=0;
    if(pos->y>h-100) pos->y=h-100;
}