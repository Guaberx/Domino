#include <iostream>
#include <SDL.h>
#include <winsock2.h>
#include <ctime>
#include "Board.h"
#include "Game.h"

//First we define the version
//#define SCK_VERSION1 0x0101 //Version 1
#define SCK_VERSION2 0x0202 //Version 2

using namespace std;
//Optimiza los surfaces para el tamano adecuado. utilizar al usar una imagen o algo con surface!!!!
SDL_Surface* OptimizeSurface(std::string filePath, SDL_Surface* windowSurface){
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());

    if(surface == NULL){
        cout << "Error cargando Surface: " << SDL_GetError() << endl;
    }else{
        //Se convierte al formato correcto para usarlo
        //BMP vienen normalmente en 24 bits. pero vamos a usar diferentes en la pantalla
        //Por lo que toca cambiarle el formato.
        optimizedSurface = SDL_ConvertSurface(surface,windowSurface->format,0);
        if(optimizedSurface == NULL){
            cout << "Error cargando Surface: " << SDL_GetError() << endl;
            }
    }
    SDL_FreeSurface(surface);//Borramos el contenido del apuntador
    surface = NULL;//Buenas practicas
    return optimizedSurface;
}

int main(int argc, char * argv[]) {
    string string1 = "TEST";
    const char* charstring = string1.c_str();//Transforma un string en un char*
    int repeticiones = strlen(charstring);//Consigue el lenght de un char[]

    srand(time(NULL));//Initialize random seed for rand()
    Game* juego = new Game(3);//Nuevo juego con 3 Jugadores. es un puntero para poder crear juegos nuevos
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        cout << "Ha salido algo mal en la inicializacion de SDL" << SDL_GetError();
        exit(1);
    }

    SDL_Window* MyWindow = NULL;
    SDL_Surface* windowSurface = NULL;
    SDL_Surface* imageSurface = NULL;

    MyWindow = SDL_CreateWindow("Super Awesome Domino",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,680,420,SDL_WINDOW_OPENGL);

    windowSurface = SDL_GetWindowSurface(MyWindow);
    imageSurface = SDL_LoadBMP("TEMPLATE-24.bmp");

    //QUICENO!!!!!!
    SDL_Renderer * renderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture *testTEXT = SDL_CreateTextureFromSurface(renderer,imageSurface);
    SDL_Rect * rect = new SDL_Rect();
    rect -> x = 0;
    rect -> y = 0;
    rect -> w = 500;
    rect -> h = 500;
    //Para clip en SDL_RenderCopy
    SDL_Rect* rectForResize = new SDL_Rect();
    rectForResize -> x = 0;
    rectForResize -> y = 0;
    rectForResize -> w = 640;
    rectForResize -> h = 480;
    //////////////

    bool isRunning = true;
    SDL_Event ev;

    while(isRunning){
        while(SDL_PollEvent(&ev) != 0){
            if(ev.type == SDL_QUIT){
                isRunning = false;
            }
            if(ev.type == SDL_MOUSEBUTTONDOWN){
                cout <<"\n\tQuieres pene?";
            }
        }

        //QUICENO!!!!!
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderCopy(renderer,testTEXT,rect,rectForResize);
        SDL_RenderPresent(renderer);
        ////////////////
        //SDL_BlitSurface(imageSurface,NULL,windowSurface,NULL);

        //SDL_UpdateWindowSurface(MyWindow);

    }


    SDL_Delay(20);


    SDL_FreeSurface(imageSurface);//Como es memoria dinamica. Borramos imageSurface
    SDL_DestroyWindow(MyWindow);//Como es memoria dinamica. Borramos MyWindow
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