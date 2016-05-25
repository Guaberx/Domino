#include <iostream>
#include <SDL.h>
#include <winsock2.h>
#include <ctime>
#include "Board.h"
#include "Game.h"
#include "Graphics.h"

//First we define the version
//#define SCK_VERSION1 0x0101 //Version 1
#define SCK_VERSION2 0x0202 //Version 2

/*
 * NOTES:
 * Must implement winner function and conditions
 * Must implement Graphics and Events
 * Must implement NET
 */

using namespace std;

int main(int argc, char * argv[]) {
    //TODO: Developer mode, Artificial inteligence, End of game
    //Inicializamos SDL y checkeamos errores
    int njugadores = 0;
    do{
        cout <<"\tCuantos Jugadores van a jugar? ";
        cin >> njugadores;
        cout << endl;
    }while(njugadores<=0 || njugadores>=5);

    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        cout << "Ha salido algo mal en la inicializacion de SDL" << SDL_GetError();
        exit(1);
    }
    if(TTF_Init()!=0){
        cout << "Ha salido algo mal en la inicializacion de TTF" << SDL_GetError();
        exit(1);
    }
    //Creamos la ventana
    SDL_Window* window = SDL_CreateWindow(TITTLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                               RESOLUTION_W,RESOLUTION_H,SDL_WINDOW_OPENGL);
    //Creamos el renderer
    SDL_Renderer* Main_Renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    //Optimizaciones
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(Main_Renderer, RESOLUTION_W, RESOLUTION_H);


    srand(time(NULL));//Initialize random seed for rand()
    Graphics graphics(window,Main_Renderer);
    Game* juego = new Game(window,Main_Renderer,&graphics,njugadores);//Nuevo juego con 3 Jugadores. es un puntero para poder crear juegos nuevos

    //Se meten imagenes para renderizarlas
    GraphicOBJ Background(window,Main_Renderer,"images/Background.png",0,0,RESOLUTION_W,RESOLUTION_H);
    juego->setBackground(&Background);
    /*
     *
     */


    bool isRunning = true;
    SDL_Event ev;

    while(isRunning){
        //Event Handler  |||| Must be inserted in game logic
        while(SDL_PollEvent(&ev) != 0){
            if(ev.type == SDL_QUIT){
                isRunning = false;
            }
        }
        //Game logic
        //Update graficos
        //ADD Graphic object to render TODO It is a must to add the graphicOBJ everyloop!!!!
        juego->update(&isRunning);
        //graphics.render(1);//TA FUNCIONA//El 1 es para que haga flip en las texturas
    }

    SDL_Delay(20);
    //SDL_DestroyRenderer(Main_Renderer);
    //SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;

    /*
    While (the game is not over)
        Check and process any user input;
        Compute AI;
        Move the monsters or enemies;
        Resolve collisions;
        Draw graphics;
        Play sounds;
    End While
     */
}