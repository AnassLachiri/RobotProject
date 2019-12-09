#ifndef INTI_H
#define INTI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



SDL_Window * createWindow();

SDL_Renderer * createRenderer(SDL_Window * window);

SDL_Surface* createSurface(SDL_Window * window, SDL_Renderer * rend);

SDL_Texture * createTexture(SDL_Window * window, SDL_Renderer * rend, SDL_Surface * surface);


int handleEvents(SDL_Window * window, int *w, int *h, int *up, int *right, int *down, int *left);


void controlRobot(int up, int down, int right, int left, int speed, int *x_vel, int *y_vel);


void rotationRobot(int up, int down, int right, int left, int *rot);

void updateRobotPosition(SDL_Rect *pos, int x_vel, int y_vel, int w, int h);


#endif