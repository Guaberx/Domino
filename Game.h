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
    vector<Board*> boardPile;
public:
    Game(unsigned int nPlayers){
        //Se crea un espacio de memoria, para que al salir de la funcion siga existiendo el tablero
        Board* newBoard = new Board(nPlayers);
        boardPile.push_back(newBoard);
    }
    ~Game(){
        boardPile.clear();//Borra todos los estados guardados
    }
};
#endif //PROYECTO_GAME_H
