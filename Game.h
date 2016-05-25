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
    Graphics* graphics;
public:
    Game(SDL_Window* window, SDL_Renderer* renderer,Graphics* graphicsI, unsigned int nPlayers);
    ~Game();

    void update();
};

#endif //PROYECTO_GAME_H
