//
// Created by Guaberx on 19.05.2016.
//

/*
 * Los dominos a la derecha en el tablero de juego estan
 * juntos bot <-> top
 * ej:   Lista de dominoes =
 * {
 * dominoNuevo1.bot<->domino1.top,
 * domino1.bot<->domino2.top,
 * domino2.bot<->dominoNuevo2.top
 * }
 * al representarlo asi, nos ahorramos el uso de apuntadores para conectarlos.
 * simplemente tenemos que seguir este diseno.
 */
#include <iostream>
#include "Player.h"


template <class T>
bool is_in(T elem,vector<T>* v){
    for (int i = 0; i < v->size() ; ++i) {
        if(elem == v->at(i)){
            return true;
        }
    }
    return false;
}

Player::Player(){
    cash = CASHPERPLAYER;
}

vector<Domino> Player::getPlayableDominoes(Board board) {
    //Dice que dominoes puede colocar el jugador
    vector<Domino> dominoesToPlay;
    for (int i = 0; i < dominoes.size(); ++i) {
        //Miramos el primero y ultimo de dominoesAtPlay
        if(dominoes.at(i).getBot() == board.dominoesAtPlay.at(0).getTop()
           || dominoes.at(i).getTop() == board.dominoesAtPlay.at(board.dominoesAtPlay.size()-1).getBot()){
            //Agregamos al vector el domino jugable
            dominoesToPlay.push_back(dominoes.at(i));
        }
    }
    return dominoesToPlay;
}

void Player::placeDominoe(Board board){
    //Hacer algun metodo de SDL para que escoja la ficha
    //Mostrar en el chat las fichas disponibles o hacerlo de algun metodo
    vector<Domino> possible = getPlayableDominoes(board);
    int pick;

    cout << "Pick a domino\n";
    printDominoes(possible);
    cin >> pick;
}

void Player::eat(Board board){

}





