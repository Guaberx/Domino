//
// Created by Guaberx on 18.05.2016.
//

#ifndef PROYECTO_BOARD_H
#define PROYECTO_BOARD_H
#define DOMINOESPERPLAYER 5

#include "Player.h"
#include <vector>

class Board{
    //Pila: Los dominoes para cojer de la mesa
    vector<Domino> dominoesToEat;
    //Los Jugadores tienen un orden para jugar
    vector<Player> players;
    //Los dominoes que estan en juego en la mesa
    vector<Domino> dominoesAtPlay;

    vector<Domino> mixedDominoes();//Revuelve los dominoes
    vector<Player> createPlayers(unsigned int nPlayers);
    void dealDominoes();//Distribuye los dominoes a los jugadores
    void orderOfPlayers();//Define el orden de los jugadores

public:
    Board(unsigned int nPlayers);//INITIALIZATION of Board
};

#endif //PROYECTO_BOARD_H
