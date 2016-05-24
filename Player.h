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
    bool ate;//Si ya comio una ficha en su turno
    string name;
    int cash;
    vector<Domino> dominoes;//Las fichas del jugador

    Player();
    vector<Domino> getPlayableDominoes(Board* board);//Dice que dominoes pueden ser jugados por el jugador
    bool placeDominoe(SDL_Window* window,SDL_Renderer* renderer,Board* board, Domino* pickedDomino);//Coloca una ficha en el tablero y se quita de 'dominoes'
    void eat(SDL_Window* window,SDL_Renderer*renderer,Board* board);//Come un domino de los dominoes que se pueden comer

    //Graphics
    void rotateDomino(SDL_Window* window,SDL_Renderer* renderer,Board* board, unsigned int idxDomino);

    void renderPlayerDominoes(Graphics* graphics){
        //Mete todos los objetos a renderizar en graphics
        for (int i = 0; i < dominoes.size(); ++i) {
            graphics->imagesToRenderPUSH_BACK(*dominoes.at(i).getGraphicOBJ());
        }
    }
    //TODO
    void update(SDL_Window* window,SDL_Renderer*renderer,Graphics* grafics,Board* board);//Es booleano para usarlo en board

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
