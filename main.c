#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "functions.h"
#include "trace.h"




int main(int argc, char *argv[])
{
    srand(time(NULL));
    //  Initialiser le SDL
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    // Creation du "window" SDL 
    SDL_Window * window = createWindow();
    if(window==NULL) return 1;
    // Creation du "Rendrer"
    SDL_Renderer * rend = createRenderer(window);
    if(!rend) return 1;
    // Creation du surface pour le robot
    SDL_Surface* surface = createSurface(window, rend);
    if(!surface) return 1;
    // Creation du texture pour le robot
    SDL_Texture * tex = createTexture(window, rend, surface);
    if(!tex) return 1;

    // ***************** CIRCLE ******************** //

    SDL_Surface* circle = IMG_Load("assets/circle.png");    // Creation du surface Cercle
    if(!circle){        // Au cas d'erreur
        printf("Error  Surface!!\n");
        SDL_DestroyRenderer(rend);      // Detruire le "Renderer"
        SDL_DestroyWindow(window);      // Detruire le "window"
        SDL_Quit();                     
        return 1;
    }

    SDL_Texture * texCircle = SDL_CreateTextureFromSurface(rend, circle);  // Creation du texture Cercle
    SDL_FreeSurface(circle);        // Detruire la surface cercle
    if(!texCircle){     // Au cas d'erreur
        printf("Error  Texture!!\n");
        SDL_DestroyRenderer(rend);      // Detruire le "Renderer"
        SDL_DestroyWindow(window);      // Detruire le "window"
        SDL_Quit();
        return 1;
    }

    // ***************** RECTANGLE ******************** //

    SDL_Surface* rect = IMG_Load("assets/rect.png");    // Creation du surface Rectangle
    if(!rect){      // Au cas d'erreur
        printf("Error  Surface!!\n");
        SDL_DestroyRenderer(rend);      // Detruire le "Renderer"
        SDL_DestroyWindow(window);      // Detruire le "window"
        SDL_Quit();
        return 1;
    }

    SDL_Texture * texRect = SDL_CreateTextureFromSurface(rend, rect);
    SDL_FreeSurface(rect);        // Detruire la surface Rectangle
    if(!texRect){       // Au cas d'erreur
        printf("Error  Texture!!\n");
        SDL_DestroyRenderer(rend);      // Detruire le "Renderer"
        SDL_DestroyWindow(window);      // Detruire le "window"
        SDL_Quit();
        return 1;
    }

    // ***************** Triangle( Shape ) ******************** //

    SDL_Surface* shape = IMG_Load("assets/triangle.png");       // Creation du surface shape ( Triangle )
    if(!shape){     // Au cas d'erreur
        printf("Error  Surface!!\n");
        SDL_DestroyRenderer(rend);      // Detruire le "Renderer"
        SDL_DestroyWindow(window);      // Detruire le "window"
        SDL_Quit();
        return 1;
    }

    SDL_Texture * texShape = SDL_CreateTextureFromSurface(rend, shape);
    SDL_FreeSurface(shape);        // Detruire la surface shape ( Traingle )
    if(!texShape){      // Au cas d'erreur
        printf("Error  Texture!!\n");
        SDL_DestroyRenderer(rend);      // Detruire le "Renderer"
        SDL_DestroyWindow(window);      // Detruire le "window"
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

    //******************* Menus *********************//

    SDL_Surface* menu0 = IMG_Load("assets/menu0.png");      // Creation du surface Menu0
    if(!menu0){     // Au cas d'erreur
        printf("Error  Surface!!\n");
        SDL_DestroyRenderer(rend);      // Detruire le "Renderer"
        SDL_DestroyWindow(window);      // Detruire le "window"
        SDL_Quit();
        return 1;
    }

    SDL_Texture * texMenu0 = SDL_CreateTextureFromSurface(rend, menu0);
    SDL_FreeSurface(menu0);        // Detruire la surface menu0
    if(!texMenu0){      // Au cas d'erreur
        printf("Error  Texture!!\n");
        SDL_DestroyRenderer(rend);      // Detruire le "Renderer"
        SDL_DestroyWindow(window);      // Detruire le "window"
        SDL_Quit();
        return 1;
    } 

    SDL_Surface* menu1 = IMG_Load("assets/menu1.png");      // Creation du surface Menu1
    if(!menu1){     // Au cas d'erreur
        printf("Error  Surface!!\n");
        SDL_DestroyRenderer(rend);      // Detruire le "Renderer"
        SDL_DestroyWindow(window);      // Detruire le "window"
        SDL_Quit();
        return 1;
    }

    SDL_Texture * texMenu1 = SDL_CreateTextureFromSurface(rend, menu1);
    SDL_FreeSurface(menu1);        // Detruire la surface menu1
    if(!texMenu1){      // Au cas d'erreur
        printf("Error  Texture!!\n");
        SDL_DestroyRenderer(rend);      // Detruire le "Renderer"
        SDL_DestroyWindow(window);      // Detruire le "window"
        SDL_Quit();
        return 1;
    } 

    //******************* About Page *********************//

    SDL_Surface* about = IMG_Load("assets/about.png");      // Creation du surface About
    if(!about){     // Au cas d'erreur
        printf("Error  Surface!!\n");
        SDL_DestroyRenderer(rend);      // Detruire le "Renderer"
        SDL_DestroyWindow(window);      // Detruire le "window"
        SDL_Quit();
        return 1;
    }

    SDL_Texture * texAbout = SDL_CreateTextureFromSurface(rend, about);
    SDL_FreeSurface(about);        // Detruire la surface about
    if(!texAbout){      // Au cas d'erreur
        printf("Error  Texture!!\n");
        SDL_DestroyRenderer(rend);      // Detruire le "Renderer"
        SDL_DestroyWindow(window);      // Detruire le "window"
        SDL_Quit();
        return 1;
    } 

    
    int w, h;       // Largeur et longueur du "window"
    SDL_GetWindowSize(window, &w, &h);      // Affectation les valeurs aux w et h
    
    SDL_Rect pos;       // la position du robot dans le "window"
    pos.x = w -150;
    pos.y = h/2 -50;
    pos.w = 100;
    pos.h = 100;

    Trace * trace = (Trace *) malloc(sizeof(Trace));  // Lise chainee pour stocker les valeurs du chemin
    trace->x = pos.x + pos.w/2;
    trace->y = pos.y + pos.h/2;
    trace->next = NULL;

    int speed = 3;      // La vitesse de deplacement du robot ( en px/frame )

    // Variables pour la gestion de la direction de deplacement du robot
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;

    // Variable de rotaion du robot
    int rot = 0;

    int fps = 60;       // Variable de nombre de "frame" par seconde
    float delTime = 1000.0/fps;     // Variable pour le temps de delais

    int rands[6];       // Tableau des valeurs aleatoires ( entre 0 et 2 )
    int k;
    for (int i = 0; i<6; i++){
        k = rand()%3;
        rands[i] = k;
    }

    int shapeNbr = -1;  // Le nombre de la forme portee par le robot ( s'il n'existe pas  shapeNbr=-1 )
    int shapes_zone2[6]={0,0,0,0,0,0};      // Tableau dont les elements indique si la place corresondant est disponible ( 0 ) ou non ( 1 )

    int menu = 0;  
    while(1){
        if(menu==0){        // Afficher le menu principale ( menu0 ) 
            int ev = handleEvents(window, &w, &h, &up, &right, &down, &left, &pos, shapes, rands, &shapeNbr, shapes_zone2, &menu, shapes_zone2);  // Gestion des evenements
            if(ev==1) break;

            SDL_RenderClear(rend);      // Effacer le "renderer"
            SDL_RenderCopyEx(rend, texMenu0  , NULL, NULL, 0, NULL, SDL_FLIP_NONE);     // Afficher le menu principale ( menu0 )
            SDL_RenderPresent(rend);        // Presenter le menu dans le "renderer"
            if(trace!=NULL){    //Au cas d'erreur
                freeTrace(trace, pos.x + pos.w/2, pos.y + pos.h/2);  // Reinitialiser la liste chainée du chemin
            }
            SDL_Delay(delTime);     // Un retard de "delTime"

        }else if(menu==1){
            int ev = handleEvents(window, &w, &h, &up, &right, &down, &left, &pos, shapes, rands, &shapeNbr, shapes_zone2, &menu, shapes_zone2);        // Gestion des evenements
            if(ev==1) break;

            SDL_RenderClear(rend);      // Effacer le "renderer"
            SDL_RenderCopyEx(rend, texMenu1  , NULL, NULL, 0, NULL, SDL_FLIP_NONE); // Afficher le menu 1
            SDL_RenderPresent(rend);       // Presenter le menu 1 dans le "renderer"

            
            SDL_Delay(delTime);     // Un retard de "delTime"

        }else if(menu==2){
            int ev = handleEvents(window, &w, &h, &up, &right, &down, &left, &pos, shapes, rands, &shapeNbr, shapes_zone2, &menu, shapes_zone2);        // Gestion des evenements
            if(ev==1) break;
            
            SDL_RenderClear(rend);      // Effacer le "renderer"
            SDL_RenderCopyEx(rend, texAbout  , NULL, NULL, 0, NULL, SDL_FLIP_NONE); // Afficher la page "about"
            SDL_RenderPresent(rend);    // Presenter la page "about" dans le "renderer"
            
            SDL_Delay(delTime);     // Un retard de "delTime"

        }else{
            int ev = handleEvents(window, &w, &h, &up, &right, &down, &left, &pos, shapes, rands, &shapeNbr, shapes_zone2, &menu, shapes_zone2);        // Gestion des evenements
            if(ev==1) break;

            int x_vel = 0;  // Deplacement selon x
            int y_vel = 0;  // Deplacement selon y
            controlRobot(up, down, right, left, speed, &x_vel, &y_vel); // Mise à jour la position du Robot pour le deplacer dans certains directions


            SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);   // Determiner la couleur de l'arriere ( background )
            SDL_RenderClear(rend);      // Effacer le "renderer"

            rotationRobot(up, down, right, left, &rot);     // Mise a jour de la rotation du robot

            for(int i = 0; i<6; i++){
                switch (rands[i])       // Determiner la forme qu'on va afficher
                {
                case 0:
                    SDL_RenderCopyEx(rend, texCircle  , NULL, &shapes[i], 0, NULL, SDL_FLIP_NONE);  // Afficher un cercle dans la i-eme position de la zone 1
                    break; 
                case 1:
                    SDL_RenderCopyEx(rend, texRect, NULL, &shapes[i], 0, NULL, SDL_FLIP_NONE);      // Afficher un rectangle dans la i-eme position de la zone 1
                    break; 
                case 2:
                    SDL_RenderCopyEx(rend, texShape, NULL, &shapes[i], 0, NULL, SDL_FLIP_NONE);     // Afficher un triangle dans la i-eme position de la zone 1
                    break;  
                case -1:
                    SDL_RenderCopyEx(rend, texCircle  , NULL, &shapes[i], 0, NULL, SDL_FLIP_NONE);  // Afficher un cercle
                    break;
                }
            }



            SDL_SetRenderDrawColor(rend, 200, 200, 200, SDL_ALPHA_OPAQUE);      // Determiner la couleur des limites des zones 1 et 2
            //  Afficher les limites de la zone 1
            SDL_RenderDrawLine(rend, 100, 0, 100, 100);
            SDL_RenderDrawLine(rend, 100, 100, 700, 100);
            SDL_RenderDrawLine(rend, 700, 0, 700, 100);
            // Afficher les limites de la zone 2
            SDL_RenderDrawLine(rend, 100, 500, 100, 400);
            SDL_RenderDrawLine(rend, 100, 400, 700, 400);
            SDL_RenderDrawLine(rend, 700, 400, 700, 500);


            if(remainingCircles(rands)!=0){     // Vérifier que le nombre de cercles restés en zone 1 est different de 0
                SDL_RenderCopyEx(rend, tex, NULL, &pos, rot, NULL, SDL_FLIP_NONE);      // Afficher le robot
                // Ajouter la position actuelle du robot au liste chainee "trace"
                Trace * firstTrace = (Trace *) malloc(sizeof(Trace));
                firstTrace->x = pos.x + pos.w/2;
                firstTrace->y = pos.y + pos.h/2;
                firstTrace->next = trace;
                trace = firstTrace;
            }else{    // Le cas du fin de jeu
                // Dessiner le chemin ( lignes entre tout deux positions successives du liste chainee "trace" )
                Trace * drawTrace = (Trace *) malloc(sizeof(Trace));
                drawTrace = trace;
                while(drawTrace->next!=NULL){
                    SDL_SetRenderDrawColor(rend, 0, 0, 0, SDL_ALPHA_OPAQUE); // Determiner la couleur du chemin
                    SDL_RenderDrawLine(rend, drawTrace->x, drawTrace->y, drawTrace->next->x, drawTrace->next->y);
                    drawTrace = drawTrace->next;
                }
            }
            SDL_RenderPresent(rend);    // Presenter les dessins dans le "renderer"

            
            updateRobotPosition(&pos, x_vel, y_vel, w, h);      // Mise a jour de la position du robot
            if(shapeNbr!=-1){       // Deplacer le cercle porte par le robot
                shapes[shapeNbr].x = pos.x;
                shapes[shapeNbr].y = pos.y;
            }

            SDL_Delay(delTime);    // Un retard de "delTime"
        }
    }

    free(trace);        // Liberer la liste chainee "trace"

    SDL_DestroyTexture(tex);        // Detruire la texture "tex"    
    SDL_DestroyWindow(window);      // Detruire la "window"
    SDL_Quit();                     // Quitter la SDL
    return 0;
}
