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

int main(int argc, char * argv[]) {
    srand(time(NULL));//Initialize random seed for rand()
    Game juego(3);
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        cout << "Ha salido algo mal en la inicializacion de SDL";
        exit(1);
    }

    SDL_Window* MyWindow;
    MyWindow = NULL;
    MyWindow = SDL_CreateWindow("Window Name :p",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,680,420,SDL_WINDOW_OPENGL);
    SDL_Rect src;

    SDL_Surface * window = SDL_CreateRGBSurfaceFrom(NULL, 680, 420, 32, 0, 100, 0, 0, 0);
    src.x = 0;
    src.y = 0;
    src.w = 680;
    src.h = 420;

    SDL_FillRect(window,&src,0);
	system("pause");
    return 0;
}




























