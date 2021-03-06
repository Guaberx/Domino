//
// Created by Guaberx on 18.05.2016.
//

#ifndef PROYECTO_BOARD_H
#define PROYECTO_BOARD_H
#define DOMINOESPERPLAYER 5 //El numero de dominoes por jugador
#define CASHPERPLAYER 2000 //La cantidad de dinero por jugador

#include "Player.h"
#include "Domino.h"
#include <vector>
using std::vector;

class Player;

//Help and global functions
void printDominoes(vector<Domino> tempDominoes);//Imprime un vector de dominoes organizadamente
Player bestDominoPlayer(vector<Player>* players);//Escoje el jugador con mayor ficha
Player whosGotTheMagicDomino(vector<Player>* players);//Escoje el jugador con la pareja de domino mayor
int getPlayerIdx(vector<Player>* players, Player* player);//Retorna el index de un jugador

class Board{
    //Los Jugadores tienen un orden para jugar
    vector<Player> players;

    vector<Domino> mixedDominoes();//Revuelve los dominoes
    vector<Player> createPlayers(unsigned int nPlayers);
    void dealDominoes();//Distribuye los dominoes a los jugadores
    void orderOfPlayers();//Define el orden de los jugadores

    //Graphics
    SDL_Window* window;
    SDL_Renderer* renderer;
    Graphics* graphics;

public:
    //El ultimo jugador en poner ficha. se utiliza para ver cuanto le pagan
    int profit;
    Player *lastPlayer;
    bool keepPlaying;//Sirve para terminar el for para poder retroceder una ronda
    bool winner;

    /*Dice si el jugador no ha completado su turno
     *entonces se sigue haciendo el loop hasta que realice una accion(evento)
     */
    //bool playerInTurn;

    //El fondo del tablero. para renderizarlo
    GraphicOBJ* Background;
    //Botones
    GraphicOBJ* SelectOtherDomino;
    GraphicOBJ* DeshacerRonda;

    //Pila: Los dominoes para cojer de la mesa
    vector<Domino> dominoesToEat;
    //Los dominoes que estan en juego en la mesa
    vector<Domino> dominoesAtPlay;//Los dominoes en la mesa que ya se han puesto

    void dominoesAtPlayINSETR(int idx, Domino* whatToADD);
    void dominoesAtPlayERASE(int idx, Domino* whatToADD);
    void dominoesToEatINSETR(int idx, Domino* whatToADD);
    void dominoesToEatERASE(int idx, Domino* whatToADD);

    void booblePrint();//Imprime los jugadores comenzando con el que tiene mas dinero

    void changeBackground(GraphicOBJ *newBackground);

    Board(SDL_Window* window,SDL_Renderer* renderer,Graphics* graphics,unsigned int nPlayers);//CONSTRUCTOR of Board

    void update();//toma los inputs y define que haces. pone a jugar al personaje que le toca el turno si escogido.
};

#endif //PROYECTO_BOARD_H
