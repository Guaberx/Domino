//
// Created by Guaberx on 24.05.2016.
//
#include "Game.h"

Game::Game(SDL_Window* window, SDL_Renderer* renderer,Graphics* graphicsI, unsigned int nPlayers){
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

void Game::update() {
    //Metemos en la pila el estado del juego cada ronda. si es para cada evento, seria en en board.cpp.update();
    boardPile.push_back(boardPile.at(0));//Se guardan los estados del juego
    boardPile.at(0).update();//el ultimo elemento para trabajarlo como pila
}

