//
// Created by Guaberx on 18.05.2016.
//

#include "Domino.h"
#include "Board.h"
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

Board::Board(unsigned int nPlayers){
    //Constructor
    dominoesToEat = mixedDominoes();
    players = createPlayers(nPlayers);
    dealDominoes();
    orderOfPlayers();
}

//Esta Funcion Globalmente sirve
void printDominoes(vector<Domino> tempDominoes){
    //Imprime los dominoes de un vector de dominoes
    int organizer = 0;
    std::cout << "\tFichas del Juego:"<<std::endl<<"\t";
    for (int k = 0; k < tempDominoes.size(); ++k) {
        std::cout << tempDominoes[k].getTop() << "," << tempDominoes[k].getBot() << "  ";
        organizer++;
        if(organizer>tempDominoes.size()/2-1){//Para ordenar la impresion
            std::cout<<std::endl<<"\t";
            organizer = 0;
        }
    }
    std::cout<<std::endl;
}

vector<Domino> Board::mixedDominoes(){
    //Crear Los Dominoes
    vector<Domino> tempDominoes;
    vector<Domino> tempDominoesToReturn;
    Domino tempDomino(0,0);
    int nDominoes = 28;//Hay 28 fichas en el juego
    for (int i = 0; i <= 6; ++i) {//*******Volver constante tal vez
        for (int j = 0; j <= i; ++j) {
            tempDomino.setTop(i);
            tempDomino.setBot(j);
            tempDominoes.push_back(tempDomino);
        }
    }
    int randomNumber;
    while(!tempDominoes.empty()){
        //Generamos un numero aleatorio entre.  arithmetic exeption, por eso el condicionante
        nDominoes==0? randomNumber=0:randomNumber = rand()%nDominoes;
        //Metemos en el vector a retornar un elemento aleatorio
        tempDomino = tempDominoes[randomNumber];
        tempDominoesToReturn.push_back(tempDomino);
        //Eliminamos ese elemento del vector ordenado
        tempDominoes.erase(tempDominoes.begin()+randomNumber);
        //Actualizamos nDominoes
        nDominoes--;
    }
    return  tempDominoesToReturn;
}

vector<Player> Board::createPlayers(unsigned int nPlayers){
    vector<Player> tempPlayers;
    Player newPlayer;
    string nombre;
    for (int i = 0; i < nPlayers; ++i) {
        nombre = "Player ";
        newPlayer.name = nombre += (i+49);//Nombre del jugador. no hay jugador 0. alt 49 = 1, 50 = 2...
        tempPlayers.push_back(newPlayer);
    }
    return tempPlayers;
}

void Board::dealDominoes(){
    int dealN = 0;
    while (dealN<DOMINOESPERPLAYER){//La cantidad de dominoes que se le reparten a cada jugador
        for (int i = 0; i < players.size(); ++i) {
            //Se come el primer domino de la dominoesToEar
            players[i].dominoes.push_back(dominoesToEat[0]);
            //Se quita el elemento de dominoesToEat que se comio el jugador
            dominoesToEat.erase(dominoesToEat.begin());
        }
        dealN++;//Se actualiza el contador
    }
    std::cout << "\n\tSe han repartido los dominoes a todos los Jugadores" << std::endl;
    /*for (int j = 0; j < players.size(); ++j) {
        std::cout << "\n\t" << players.at(j).name <<": \n";//j+1 porque no hay jugador 0
        printDominoes(players[j].dominoes);
    }*/
    std::cout << std::endl;
}

Player bestDominoPlayer(vector<Player>* players){
    //Escoje el jugador con mayor ficha. se utiliza en caso de que ninguno tenga una ficha par
    Player first = players->at(0);//El primer Jugador
    vector<Domino> greatestDominoes;//Guarda el domino mas grande de cada jugador
    Domino tempDomino(0,0);//El primer domino del primer Jugador

    for (int i = 0; i < players->size(); ++i) {
        tempDomino = players->at(i).dominoes.at(0);
        //Se escoje la ficha mayor de cada jugador
        for (int j = 0; j < players->at(i).dominoes.size(); ++j) {
            if(players->at(i).dominoes.at(j)>tempDomino){
                tempDomino = players->at(i).dominoes.at(j);
            }
        }
        greatestDominoes.push_back(tempDomino);
        tempDomino.setTop(0);tempDomino.setBot(0);//Reiniciamos la ficha temp;
    }
    //printDominoes(greatestDominoes);

    //Controller es un index para conseguir al jugador en el vector
    int controller = 0;//Para tener un index del mayor domino(el que comienza primero de los Jugadores)
    for (int k = 0; k < greatestDominoes.size(); ++k) {
        if(greatestDominoes.at(k)>greatestDominoes.at(controller)){
            controller = k;
        }
    }

    first = players->at(controller);
    //printDominoes(first.dominoes);

    return first;
}

Player whosGotTheMagicDomino(vector<Player>* players){
    //Retorna el jugador con la ficha par mas alta
    //Encuentra quien tiene el 6,6 o el 5,5 o el 4,4...
    int controller = 6;//Para buscar el 6,6. luego se resta y busca el 5,5...
    Domino tempDomino(controller,controller);
    while(controller>=0){
        for (int i = 0; i < players->size(); ++i) {
            //Buscamos entre los dominoes de cada jugador
            for (int j = 0; j < players->at(i).dominoes.size(); ++j) {
                if(players->at(i).dominoes.at(j) == tempDomino){
                    return players->at(i);
                }
            }
        }
        controller--;
        tempDomino.setTop(controller);
        tempDomino.setBot(controller);
    }
    Player nullPlayer; nullPlayer.name = "null";
    return nullPlayer;//Utilizamos para comprobar si ninguno tenia una ficha par
}

int getPlayerIdx(vector<Player>* players, Player* player){
    //Consigue el indice en el vector de un jugador
    //Pasamos apuntadores para optimizar memoria
    for (int i = 0; i < players->size(); ++i) {
        for (int j = 0; j < players->at(i).dominoes.size(); ++j) {
            if(player->dominoes.at(0) == players->at(i).dominoes.at(j)){
                return i;
            }
        }
    }
}

void Board::orderOfPlayers(){
    //Ordena el vector de jugadores "players" dependiendo de sus fichas
    vector<Player> tempPlayers = players;
    Player popo;//Para definir el orden de los jugadores. se ordenan dependiendo de su fuca mas alta
    players.clear();
    while (!tempPlayers.empty()){
        //Logica para escoger turnos
        popo = whosGotTheMagicDomino(&tempPlayers);
        if(popo.name == "null"){
            popo = bestDominoPlayer(&tempPlayers);
        }
        //
        tempPlayers.erase(tempPlayers.begin()+getPlayerIdx(&tempPlayers,&popo));
        players.push_back(popo);
        //printDominoes(popo.dominoes);
    }

}

