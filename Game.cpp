//
// Created by Guaberx on 24.05.2016.
//
#include "Game.h"

Game::Game(SDL_Window* window, SDL_Renderer* renderer,Graphics* graphicsI, unsigned int nPlayers)
:window(window),renderer(renderer){
//Se crea el objero Graphics para hacer renderizados y lo relacionado con lo visual
graphics = graphicsI;
//Se crea un espacio de memoria, para que al salir de la funcion siga existiendo el tablero
Board newBoard(window,renderer,graphics,nPlayers);//TODO Probar Graphics local o global
boardPile.push_back(newBoard);
//update();
}
Game::~Game(){
    boardPile.clear();//Borra todos los estados guardados
}

void Game::update(bool* Gamestate) {
    //Metemos en la pila el estado del juego cada ronda. si es para cada evento, seria en en board.cpp.update();
    boardPile.push_back(boardPile.at(0));//Se guardan los estados del juego
    boardPile.at(0).update();//el ultimo elemento para trabajarlo como pila
    if(boardPile.at(0).winner){
        boardPile.at(0).booblePrint();
        int pick;
        do{
            cout << "\n1: Nuevo Juego    2: Salir\n";
            cin >> pick;
            if(pick == 1 || pick == 2)break;
        }while (true);
        switch (pick){
            case 1:
                boardPile.clear();
                int nPlayers;
                do{
                    cout << "\nIntroduzca El Numero de Jugadores:\n";
                    cin >> nPlayers;
                    if(nPlayers>0 && nPlayers<5)break;
                }while (true);
                boardPile.push_back(Board(window,renderer,graphics,nPlayers));
                break;
            case 2:
                *Gamestate = false;//Sale del juego
                break;
        }
    }
    else if(!boardPile.at(0).keepPlaying){
        boardPile.erase(boardPile.begin());//Borramos el primer elemento
    }
}

void Game::setBackground(GraphicOBJ *background) {
    boardPile.at(0).Background = background;
}



