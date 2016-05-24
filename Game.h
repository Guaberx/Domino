//
// Created by Guaberx on 18.05.2016.
//

#ifndef PROYECTO_GAME_H
#define PROYECTO_GAME_H

#include <vector>
#include "Board.h"

using std::vector;

class Game{
    /*
     Funciona como una pila para los estados del juego.
     Cada tablero es un estado del juego, por lo que se actualiza el tablero
    cada vez que hay un evento.
     */
    vector<Board> boardPile;
public:
    Game(SDL_Window* window, SDL_Renderer* renderer, unsigned int nPlayers){
        //Se crea un espacio de memoria, para que al salir de la funcion siga existiendo el tablero
        Board newBoard(window,renderer,nPlayers);
        boardPile.push_back(newBoard);
        //update();
    }
    ~Game(){
        boardPile.clear();//Borra todos los estados guardados
    }

    void update();
};

void Game::update() {
    //Metemos en la pila el estado del juego cada ronda. si es para cada evento, seria en en board.cpp.update();
    boardPile.push_back(boardPile.at(0));//Se guardan los estados del juego
    cout << endl << "Mesa de la ronda anterior\n";
    printDominoes(boardPile.at(0).dominoesAtPlay);
    cout << endl;
    boardPile.at(0).update();//el ultimo elemento para trabajarlo como pila
}


#endif //PROYECTO_GAME_H
