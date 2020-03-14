#ifndef INTI_H
#define INTI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "trace.h"



SDL_Window * createWindow();

SDL_Renderer * createRenderer(SDL_Window * window);

SDL_Surface* createSurface(SDL_Window * window, SDL_Renderer * rend);

SDL_Texture * createTexture(SDL_Window * window, SDL_Renderer * rend, SDL_Surface * surface);


int handleEvents(SDL_Window * window, int *w, int *h, int *up, int *right, int *down, int *left, SDL_Rect *pos, SDL_Rect shapes[], int rands[], int* shapeNbr, int tab[], int *menu, int shapes_zone2[]);


void controlRobot(int up, int down, int right, int left, int speed, int *x_vel, int *y_vel);


void rotationRobot(int up, int down, int right, int left, int *rot);

void updateRobotPosition(SDL_Rect *pos, int x_vel, int y_vel, int w, int h);

void checkCircle(SDL_Rect *pos, SDL_Rect shapes[], int rands[], int* shapeNbr);

void putCircle(SDL_Rect *pos, SDL_Rect shapes[],int rands[], int* shapeNbr, int tab[]);

void clearGame(SDL_Rect *pos, SDL_Rect shapes[],int rands[], int* shapeNbr, int w, int h, int shapes_zone2[]);

int remainingCircles(int *rands);


#endif