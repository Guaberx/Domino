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
    string string1 = "TEST";
    const char* charstring = string1.c_str();//Transforma un string en un char*
    int repeticiones = strlen(charstring);//Consigue el lenght de un char[]

    //Inicializamos SDL y checkeamos errores
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        cout << "Ha salido algo mal en la inicializacion de SDL" << SDL_GetError();
        exit(1);
    }
    //Creamos la ventana
    SDL_Window* window = SDL_CreateWindow(TITTLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                               RESOLUTION_W,RESOLUTION_H,SDL_WINDOW_OPENGL);
    //Creamos el renderer
    SDL_Renderer* Main_Renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    srand(time(NULL));//Initialize random seed for rand()
    Game* juego = new Game(3);//Nuevo juego con 3 Jugadores. es un puntero para poder crear juegos nuevos
    Graphics graphics(window,Main_Renderer);

    //Se meten imagenes para renderizarlas
    GraphicOBJ Background(window,Main_Renderer,"images/Background.png",0,0,RESOLUTION_W,RESOLUTION_H);
    GraphicOBJ popo(window,Main_Renderer,"images/Ball.bmp",0,0,253,196);
    GraphicOBJ popo2(window,Main_Renderer,"images/Ball.bmp",300,200,253,196);
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
            if(ev.type == SDL_MOUSEBUTTONDOWN){
                //Para las imagenes
                if(ev.button.x >= popo.getDestRect()->x && ev.button.x <popo.getDestRect()->x+popo.getDestRect()->w
                        && ev.button.y >= popo.getDestRect()->y && popo.getDestRect()->y + popo.getDestRect()->h){
                    cout <<"\n\tPresionaste el tablero?";
                }
            }
        }
        //Game logic
        //Update graficos
        //ADD Graphic object to render
        graphics.imagesToRenderPUSH_BACK(Background);
        graphics.imagesToRenderPUSH_BACK(popo);
        graphics.imagesToRenderPUSH_BACK(popo2);
        //Remder
        graphics.render();//TA FUNCIONA
        //Clean graphics objects
        graphics.cleanVector();
        //juego->update();
    }

    SDL_Delay(20);
    //SDL_DestroyRenderer(Main_Renderer);
    //SDL_DestroyWindow(window);
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