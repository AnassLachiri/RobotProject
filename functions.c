#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "trace.h"

SDL_Window * createWindow(){ // Creation d'une "window" SDL
    SDL_Window * window = SDL_CreateWindow(
        "Robot Game!!",                     // Titre du "window"
        SDL_WINDOWPOS_CENTERED,             // Position du "window" centrée
        SDL_WINDOWPOS_CENTERED,
        900,                    // Largeur = 900px
        500,                    // Longueur = 500px
        0
    );

    if(window == NULL){             // Au cas d'erreur 
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());  // Ecrire le type d'erreur
        SDL_Quit();
        return NULL;
    }

    return window;
}


SDL_Renderer * createRenderer(SDL_Window * window){     //  Creation du "Rendrer"
    Uint32 renderer_flags = SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer * rend = SDL_CreateRenderer(window, -1 , renderer_flags);  
    if(!rend){          // Au cas d'erreur
        printf("Error  Renderer!!\n");
        SDL_DestroyWindow(window);          // Detruire le "window" avant de sortir
        SDL_Quit();
        return NULL;
    }
}

SDL_Surface* createSurface(SDL_Window * window, SDL_Renderer * rend){  // Creation du surface Robot
    SDL_Surface* surface = IMG_Load("assets/robot.png");
    if(!surface){       // Au cas d'erreur
        printf("Error  Surface!!\n");
        SDL_DestroyRenderer(rend);  // Detruire le "rendrer" crée
        SDL_DestroyWindow(window);  // Detruire le "window"
        SDL_Quit();                 // Sortir
        return NULL;
    }
    return surface;
}

SDL_Texture * createTexture(SDL_Window * window, SDL_Renderer * rend, SDL_Surface * surface){  // Creation du texture Robot
    SDL_Texture * tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if(!tex){       // Au cas d'erreur
        printf("Error  Texture!!\n");
        SDL_DestroyRenderer(rend);  // Detruire le "rendrer" crée
        SDL_DestroyWindow(window);  // Detruire le "window"
        SDL_Quit();                 // Sortir
        return NULL;
    }
    return tex;
}


int handleEvents(SDL_Window * window, int *w, int *h, int *up, int *right, int *down, int *left, SDL_Rect *pos, SDL_Rect shapes[], int rands[], int* shapeNbr, int tab[], int * menu, int shapes_zone2[]){
    SDL_Event e;
    if(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){     // Gestion du clique sur l'icon de "Quitter"
            return 1;
        }
        if(e.type == SDL_KEYDOWN){
            switch (e.key.keysym.scancode)
            {
            case SDL_SCANCODE_1:
                if(*menu==0 || *menu==1){
                    clearGame(pos, shapes, rands, shapeNbr, *w, *h,shapes_zone2); // Reinitialiser le jeu
                    *menu = 3;          // La page du jeu principale
                }
                break;
            case SDL_SCANCODE_R:
                if(*menu==1) *menu = 3;         // Continuer le jeu
                break;
            case SDL_SCANCODE_2:
                if(*menu==0 || *menu==1) *menu = 2;  // Afficher la page "About"
                break;
            case SDL_SCANCODE_3:
                if(*menu==0 || *menu==1) return 1;      // Quitter le jeu
                break;
            case SDL_SCANCODE_ESCAPE:                   
                if(*menu==2){ *menu = 0;            // Retourner de la page "About" au menu 0
                }else if(*menu!=0) {
                    if(remainingCircles(rands)==0) *menu = 0;   // Retourner de jeu principale au menu 0 ( au cas du fin de jeu )
                    else *menu = 1;             // Retourner au menu 1 ( si on a au milieu du jeu )
                }
                break;
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                *up = 1;        // Déplacer vers le haut
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT: 
                *left = 1;      // Déplacer vers le gauche
                break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                *down = 1;      // Déplacer vers le bas
                break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                *right = 1;     // Déplacer vers la droite
                break;
            case SDL_SCANCODE_SPACE:    // Ramasser un cercle de la zone 1 ( Reposer un cercle dans la zone 2 ) 
                if(*menu==3){
                    checkCircle(pos, shapes, rands, shapeNbr);
                    putCircle(pos, shapes, rands, shapeNbr, tab);
                }
                break;
            }
        }
        if(e.type == SDL_KEYUP){
            switch (e.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                *up = 0;        // Arreter le déplacement vers le haut
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                *left = 0;      // Arreter le déplacement vers le gauche
                break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                *down = 0;      // Arreter le déplacement vers le bas
                break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                *right = 0;     // Arreter le déplacement vers la droite
                break;
            }
        }
    }
    return 0;
}


void controlRobot(int up, int down, int right, int left, int speed, int *x_vel, int *y_vel){ // Mise à jour la position du Robot pour le deplacer dans certains directions
    if (up && !down) *y_vel = -speed;
    if (down && !up) *y_vel = speed;
    if (left && !right) *x_vel = -speed;
    if (right && !left) *x_vel = speed;

}


void rotationRobot(int up, int down, int right, int left, int *rot){ // Controler la rotation du Robot ( La direction de deplacement )
    if(down==1 && right==1){
        *rot = 135;             // Rotation vers le bas-droite
    }else if(left==1 && down==1){
        *rot = -135;            // Rotation vers le bas-gauche
    }else if(left==1 && up==1){
        *rot = -45;             // Rotation vers le haut-gauche
    }else if(up==1 && right==1){
        *rot = 45;              // Rotation vers le haut-droite
    }else if(right==1){
        *rot = 90;              // Rotation vers la droite
    }else if(left==1){
        *rot = -90;             // Rotation vers le gauche
    }else if(up==1){
        *rot = 0;               // Rotation vers le haut
    }else if(down==1){
        *rot = 180;             // Rotation vers le bas
    }
}

void updateRobotPosition(SDL_Rect *pos, int x_vel, int y_vel, int w, int h){ // Déplacer la position du Robot
    pos->x+=x_vel;
    pos->y+=y_vel;
    if(pos->x>w-100) pos->x=w-100;      // Détecter la collision entre le robot et la limite droite du "window"
    if(pos->x<0) pos->x=0;              // Détecter la collision entre le robot et la limite gauche du "window"
    if(pos->y<0) pos->y=0;              // Détecter la collision entre le robot et la limite haute du "window"
    if(pos->y>h-100) pos->y=h-100;      // Détecter la collision entre le robot et la limite bas du "window"

    if((pos->x<=700 && pos->x>0 && pos->y<=100)||       // Détecter la collision entre le robot et la zone 1
        (pos->x<=700 && pos->x>0 && pos->y>=300)){      // Détecter la collision entre le robot et les zones 2
            pos->x-=x_vel;
            pos->y-=y_vel;
    }
}

void checkCircle(SDL_Rect *pos, SDL_Rect shapes[], int rands[], int* shapeNbr){     // Vérfier les conditions pour déplacer un cercle
    int m = pos->x + 50;    // Affecter la position du milieu de la robot à m
    if(*shapeNbr==-1){      // Le robot est libre ( n'a pas de cercle actuellement )
        if(pos->y>=100 && pos->y<130 && m>100 && m<=700){ // Vérifier si le robot est proche de la zone 1
            if(rands[m/100-1]==0){          // Si la forme la plus proche du robot est bien un cercle
                *shapeNbr =  m/100-1;       // le nombre du cercle correspondant
            }
        }else{
            *shapeNbr = -1;
        }
    }
}

void putCircle(SDL_Rect *pos, SDL_Rect shapes[],int rands[], int* shapeNbr, int tab[]){ // Reposer le cercle dans la zone 1
    int m = pos->x + 50;    // Affecter la position du milieu de la robot à m
    if(*shapeNbr!=-1){      // Vérifier si le robot a déja un cercle
        if(pos->y>=270 && pos->y<=300 && m>100 && m<=700 && tab[(m/100)-1]==0){ // Vérifier si le robot est proche de la zone 2
            rands[*shapeNbr]=-1;    // Mise a jour du tableau des formes de la zone 1
            shapes[*shapeNbr].x= (m/100)*100;    // Le cercle porté par le robot prend la place la plus proche dans la zone 2
            shapes[*shapeNbr].y= 400;            // Le cercle porté par le robot prend la place la plus proche dans la zone 2
            *shapeNbr =  -1;        // Déclarer que le robot est libre ( n'a pas de cercle )
            tab[(m/100)-1] = 1;     // Déclarer que la postion actuelle est occupée
        }
    }
}

void clearGame(SDL_Rect *pos, SDL_Rect shapes[],int rands[], int* shapeNbr, int w, int h, int shapes_zone2[]){ // Reinitialiser les parametres du jeu
    // Reinitialiser la position du robot
    pos->x = w -150;
    pos->y = h/2 -50;
    pos->w = 100;
    pos->h = 100;

    // Reinitialiser les positions des formes
    for(int i = 1; i<=6; i++){
        shapes[i-1].x = i*100;
        shapes[i-1].y = 0;
        shapes[i-1].w = 100;
        shapes[i-1].h = 100;
    }

    // Reinitialiser les formes dans la zone 1
    int k;
    for (int i = 0; i<6; i++){
        k = rand()%3;
        rands[i] = k;
    }

    *shapeNbr = -1;  // Déclarer que le robot est libre ( n'a pas de cercle )

    for(int i = 0; i<=5; i++){
        shapes_zone2[i] = 0;    // Déclarer que la zone 2 est vide
    }

}

int remainingCircles(int *rands){   // Compter le nombre des cercles restés dans la zone 1
    int count = 0;
    for(int i = 0; i<6; i++){
        if(rands[i]==0) count++;    // Vérifier que la i-eme forme est un cercle
    }
    return count;
}

