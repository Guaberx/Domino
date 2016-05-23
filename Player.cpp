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

vector<Domino> Player::getPlayableDominoes(Board* board) {
    //Dice que dominoes puede colocar el jugador
    vector<Domino> dominoesToPlay;
    if(board->dominoesAtPlay.empty())//Para prevenir si no hay ninguna ficha en el tablero
    {
        //Escojemos las fichas par
        vector<Domino> AnotherTemp;
        Domino tempDomino(0,0);
        for (int i = 0; i < dominoes.size(); ++i) {
            if(dominoes.at(i).getTop() == dominoes.at(i).getBot()){
                AnotherTemp.push_back(dominoes.at(i));//Se ponen las fichas con parejas
            }
        }
        //Escojemos la mayor de las pares
        for (int j = 0; j < AnotherTemp.size(); ++j) {
            if(AnotherTemp.at(j)>tempDomino){
                tempDomino = AnotherTemp.at(j);
            }
        }
        dominoesToPlay.push_back(tempDomino);
    }else{
        int dpt,dpb,dbt,dbb;//dp: dominoes del jugador, db: dominoes del tablero(t:izq, b:der)
        for (int i = 0; i < dominoes.size(); ++i) {
            dpt = dominoes.at(i).getTop();
            dpb = dominoes.at(i).getBot();
            dbt = board->dominoesAtPlay.at(0).getTop();
            dbb = board->dominoesAtPlay.at(board->dominoesAtPlay.size()-1).getBot();
            //Miramos el primero y ultimo de dominoesAtPlay
            if(dpt == dbb || dpt == dbt || dpb == dbb || dpb == dbt){
                //Agregamos al vector el domino jugable
                dominoesToPlay.push_back(dominoes.at(i));
            }
        }
    }
    return dominoesToPlay;
}

int getDominoIdx(vector<Domino> vDominoes, Domino Ddomino){
    for (int i = 0; i < vDominoes.size(); ++i) {
        if(vDominoes.at(i).getTop() == Ddomino.getTop() && vDominoes.at(i).getBot() == Ddomino.getBot()){
            return i;
        }
    }
}

void Player::placeDominoe(Board* board){
    //Hacer algun metodo de SDL para que escoja la ficha
    //Mostrar en el chat las fichas disponibles o hacerlo de algun metodo
    vector<Domino> possible = getPlayableDominoes(board);

    //La ficha que comienza el juego
    if(board->dominoesAtPlay.empty()){//En el caso que se este comenzando la partida. el movimiento es automatico
        cout << name << " ha comenzado la partida con la fica: " << possible.at(0).getTop() <<", " << possible.at(0).getBot() << endl;
        board->dominoesAtPlayINSETR(0,&possible.at(0));//Se agrega el domino al tablero
        dominoes.erase(dominoes.begin()+getDominoIdx(dominoes,possible.at(0)));//Borramos el domino correcpondiente del jugador
        return;
    }

    //Escoje la ficha a poner
    int pick = -1;//Se inicializa en -1 para poder entrar al do while
    do{
        cout << name << " Pick a domino!\n";
        cout << "\n\tFichas que tienes:\n";
        printDominoes(dominoes);
        cout << "\n\tDominos que sirven:\n";
        printDominoes(possible);
        cout << "\nEscoje un domino: ";
        cin >> pick;
    }while (pick>possible.size()-1);//             POR ALGUNA RAZON FUNCIONA :|. si le pongo pick<0 falla. O.o


    //Escoje a que lado se pone la ficha
    int idxDomino = getDominoIdx(dominoes,possible.at(pick));//POPO
    bool top_top, bot_top, top_bot, bot_bot;
    top_top = dominoes.at(idxDomino).getTop() == board->dominoesAtPlay.at(0).getTop();//top<->top primer elemento (0)
    bot_top = dominoes.at(idxDomino).getBot() == board->dominoesAtPlay.at(0).getTop();//bot<->top primer elemento (0)
    top_bot = dominoes.at(idxDomino).getTop() == board->dominoesAtPlay.at(board->dominoesAtPlay.size()-1).getBot();//top<->bot ultimo elemento (1)
    bot_bot = dominoes.at(idxDomino).getBot() == board->dominoesAtPlay.at(board->dominoesAtPlay.size()-1).getBot();//bot<->bot ultimo elemento (1)
    pick = -1;//Reseteamos pick
    do{
        cout << name << " Ha escojido escojido:\n";
        cout << "\t" << dominoes.at(idxDomino).getTop() << "," << dominoes.at(idxDomino).getBot() << endl;
        cout << "\tDominoes en el tablero:\n";
        printDominoes(board->dominoesAtPlay);
        cout << name << " Pick a side, 0:Left  1:Right\n";
        cin >> pick;
        if (pick == 0 &&(top_top || bot_top)){
            break;
        }
        if (pick == 1 &&(top_bot || bot_bot)){
            break;
        }
    }while (true);

    //Poner ficha en el tablero
    switch (pick){
        case 0://El 0 es para agregar a la izquierda
            if(dominoes.at(idxDomino).getTop() == board->dominoesAtPlay.at(0).getTop()){
                //Se cambia el orden de los valores del domino para que se inserte correctamente
                short tempDominoNumber = dominoes.at(idxDomino).getTop();
                dominoes.at(idxDomino).setTop(dominoes.at(idxDomino).getBot());
                dominoes.at(idxDomino).setBot(tempDominoNumber);
            }
            board->dominoesAtPlayINSETR(0,&dominoes.at(idxDomino));
            break;
        case 1://El 1 es para agregar a la derecha
            if(dominoes.at(idxDomino).getBot() == board->dominoesAtPlay.at(board->dominoesAtPlay.size()-1).getBot()){
                //Se cambia el orden de los valores del domino para que se inserte correctamente
                short tempDominoNumber = dominoes.at(idxDomino).getTop();
                dominoes.at(idxDomino).setTop(dominoes.at(idxDomino).getBot());
                dominoes.at(idxDomino).setBot(tempDominoNumber);
            }
            board->dominoesAtPlayINSETR(board->dominoesAtPlay.size(),&dominoes.at(idxDomino));
            break;
    }
    dominoes.erase(dominoes.begin()+getDominoIdx(dominoes,possible.at(0)));//Borramos el domino correcpondiente del jugador
}

void Player::eat(Board* board){
    //El jugador se come el primer domino de la pila de dominoes para comer
    Domino tempDomino(0,0);
    tempDomino = board->dominoesToEat.at(0);
    dominoes.push_back(tempDomino);
    //DominoesToEat.Pop()
    board->dominoesToEat.erase(board->dominoesToEat.begin()+0);
    //We check again
    if(board->dominoesAtPlay.at(0).getTop()== tempDomino.getTop() || board->dominoesAtPlay.at(0).getTop()==tempDomino.getBot()
            || board->dominoesAtPlay.at(board->dominoesAtPlay.size()-1).getBot()==tempDomino.getBot()
               || board->dominoesAtPlay.at(board->dominoesAtPlay.size()-1).getBot()==tempDomino.getTop()){

        //Si la ficha que comio la puede jugar. entonces la juega
        placeDominoe(board);
        board->lastPlayer = this;
    }else{
        //En el caso que no le sirva la ficha. paga
        cash-=500;
        board->profit+=500;
    }
}

void Player::update(Board* board) {
    //Si el jugador come una ficha y le funciona, puede ponerla. sino, pasa y paga
    //El jugador solo reclama el dinero cuando no ha comido.
    //es decir que si como y puede poner la ficha, igual no reclama el dinero. solo lo reclama cuanto juega de una
    if(getPlayableDominoes(board).empty()){
        cout << name << " Ate a Domino" << endl;
        eat(board);
    }else{
        cash+=board->profit;
        board->profit = 0;
        placeDominoe(board);
        board->lastPlayer = this;
    }
}





