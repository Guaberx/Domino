//
// Created by Guaberx on 18.05.2016.
//

#ifndef PROYECTO_PLAYER_H
#define PROYECTO_PLAYER_H

#include <vector>
#include <string>
#include "Domino.h"
#include "Board.h"
#include <iostream>
#include <backward/auto_ptr.h>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;
//Referencia circular
class Board;

class Player{
public:
    string name;
    int cash;
    vector<Domino> dominoes;//Las fichas del jugador

    Player();
    vector<Domino> getPlayableDominoes(Board* board);//Dice que dominoes pueden ser jugados por el jugador
    void placeDominoe(SDL_Window* window,SDL_Renderer* renderer,Board* board);//Coloca una ficha en el tablero y se quita de 'dominoes'
    void eat(SDL_Window* window,SDL_Renderer*renderer,Board* board);//Come un domino de los dominoes que se pueden comer

    //Graphics
    Graphics* graphics;//Objeto para hacer renderizado de los dominoes
    void rotateDomino(SDL_Window* window,SDL_Renderer* renderer,Board* board, unsigned int idxDomino);

    void update(SDL_Window* window,SDL_Renderer*renderer,Board* board);//Es booleano para usarlo en board

    //Overloadin operators
    bool operator ==(const Player& other){
        for (int i = 0; i < dominoes.size(); ++i) {
            if(dominoes[i]!=other.dominoes[i]){
                return false;
            }
        }
        return true;
    }
    bool operator !=(const Player& other) {
        for (int i = 0; i < dominoes.size(); ++i) {
            if(dominoes[i]!=other.dominoes[i]){
                return true;
            }
        }
        return false;
    }
};

#endif //PROYECTO_PLAYER_H
