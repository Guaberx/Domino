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
bool is_in(T* elem,vector<T>* v){
    for (int i = 0; i < v->size() ; ++i) {
        if(*elem == v->at(i)){
            return true;
        }
    }
    return false;
}

Player::Player(){
    cash = CASHPERPLAYER;
    ate = false;
    playerInTurn = true;
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

int getDominoIdx(vector<Domino>* vDominoes, Domino* Ddomino){
    for (int i = 0; i < vDominoes->size(); ++i) {
        if(vDominoes->at(i) == *Ddomino){
            return i;
        }
    }
}

void Player::rotateDomino(SDL_Window* window,SDL_Renderer* renderer,Board* board, unsigned int idxDomino){
    //Escoje la imagen del domino correspondiente
    string imagePath;
    switch (dominoes.at(idxDomino).getTop()){
        case 0:
            switch (dominoes.at(idxDomino).getBot()) {
                case 0:
                    imagePath = "images/dominoes/00.png";
                    break;
                case 1:
                    imagePath = "images/dominoes/10.png";
                    break;
                case 2:
                    imagePath = "images/dominoes/20.png";
                    break;
                case 3:
                    imagePath = "images/dominoes/30.png";
                    break;
                case 4:
                    imagePath = "images/dominoes/40.png";
                    break;
                case 5:
                    imagePath = "images/dominoes/50.png";
                    break;
                case 6:
                    imagePath = "images/dominoes/60.png";
                    break;
            }
            break;
        case 1:
            switch (dominoes.at(idxDomino).getBot()){
                case 0:
                    imagePath = "images/dominoes/10.png";
                    break;
                case 1:
                    imagePath = "images/dominoes/11.png";
                    break;
                case 2:
                    imagePath = "images/dominoes/12.png";
                    break;
                case 3:
                    imagePath = "images/dominoes/13.png";
                    break;
                case 4:
                    imagePath = "images/dominoes/14.png";
                    break;
                case 5:
                    imagePath = "images/dominoes/15.png";
                    break;
                case 6:
                    imagePath = "images/dominoes/16.png";
                    break;
            }
            break;
        case 2:
            switch (dominoes.at(idxDomino).getBot()){
                case 0:
                    imagePath = "images/dominoes/20.png";
                    break;
                case 1:
                    imagePath = "images/dominoes/21.png";
                    break;
                case 2:
                    imagePath = "images/dominoes/22.png";
                    break;
                case 3:
                    imagePath = "images/dominoes/23.png";
                    break;
                case 4:
                    imagePath = "images/dominoes/24.png";
                    break;
                case 5:
                    imagePath = "images/dominoes/25.png";
                    break;
                case 6:
                    imagePath = "images/dominoes/26.png";
                    break;
            }
            break;
        case 3:
            switch (dominoes.at(idxDomino).getBot()){
                case 0:
                    imagePath = "images/dominoes/30.png";
                    break;
                case 1:
                    imagePath = "images/dominoes/31.png";
                    break;
                case 2:
                    imagePath = "images/dominoes/32.png";
                    break;
                case 3:
                    imagePath = "images/dominoes/33.png";
                    break;
                case 4:
                    imagePath = "images/dominoes/34.png";
                    break;
                case 5:
                    imagePath = "images/dominoes/35.png";
                    break;
                case 6:
                    imagePath = "images/dominoes/36.png";
                    break;
            }
            break;
        case 4:
            switch (dominoes.at(idxDomino).getBot()){
                case 0:
                    imagePath = "images/dominoes/40.png";
                    break;
                case 1:
                    imagePath = "images/dominoes/41.png";
                    break;
                case 2:
                    imagePath = "images/dominoes/42.png";
                    break;
                case 3:
                    imagePath = "images/dominoes/43.png";
                    break;
                case 4:
                    imagePath = "images/dominoes/44.png";
                    break;
                case 5:
                    imagePath = "images/dominoes/45.png";
                    break;
                case 6:
                    imagePath = "images/dominoes/46.png";
                    break;
            }
            break;
        case 5:
            switch (dominoes.at(idxDomino).getBot()){
                case 0:
                    imagePath = "images/dominoes/50.png";
                    break;
                case 1:
                    imagePath = "images/dominoes/51.png";
                    break;
                case 2:
                    imagePath = "images/dominoes/52.png";
                    break;
                case 3:
                    imagePath = "images/dominoes/53.png";
                    break;
                case 4:
                    imagePath = "images/dominoes/54.png";
                    break;
                case 5:
                    imagePath = "images/dominoes/55.png";
                    break;
                case 6:
                    imagePath = "images/dominoes/56.png";
                    break;
            }
            break;
        case 6:
            switch (dominoes.at(idxDomino).getBot()){
                case 0:
                    imagePath = "images/dominoes/60.png";
                    break;
                case 1:
                    imagePath = "images/dominoes/61.png";
                    break;
                case 2:
                    imagePath = "images/dominoes/62.png";
                    break;
                case 3:
                    imagePath = "images/dominoes/63.png";
                    break;
                case 4:
                    imagePath = "images/dominoes/64.png";
                    break;
                case 5:
                    imagePath = "images/dominoes/65.png";
                    break;
                case 6:
                    imagePath = "images/dominoes/66.png";
                    break;
            }
            break;
    }
    dominoes.at(idxDomino).setTexture(window,renderer,imagePath);//TODO
}

bool Player::placeDominoe(SDL_Window* window,SDL_Renderer* renderer,Board* board, Domino* pickedDomino){
    //Hacer algun metodo de SDL para que escoja la ficha
    //Mostrar en el chat las fichas disponibles o hacerlo de algun metodo
    vector<Domino> possible = getPlayableDominoes(board);

    //La ficha que comienza el juego
    if(board->dominoesAtPlay.empty()){//En el caso que se este comenzando la partida. el movimiento es automatico
        cout << name << " ha comenzado la partida con la fica: " << possible.at(0).getTop() <<", " << possible.at(0).getBot() << endl;
        board->dominoesAtPlayINSETR(0,&possible.at(0));//Se agrega el domino al tablero
        dominoes.erase(dominoes.begin()+getDominoIdx(&dominoes,&possible.at(0)));//Borramos el domino correcpondiente del jugador
        playerInTurn = false;
        return true;
    }
    cout << name << " :\n";
    //printDominoes(dominoes);
    printDominoes(board->dominoesAtPlay);

    if(!is_in(pickedDomino,&possible)){
        return false;
    }

    int possibleIdx = getDominoIdx(&possible,pickedDomino);
    int dominoesIdx = getDominoIdx(&dominoes,pickedDomino);

    playerInTurn = false;
    ate = false;

    //Booleanos para comprovar las conexiones con las fichas del tablero
    bool top_top, bot_top, top_bot, bot_bot;
    top_top = dominoes.at(dominoesIdx).getTop() == board->dominoesAtPlay.at(0).getTop();//top<->top primer elemento (0)
    bot_top = dominoes.at(dominoesIdx).getBot() == board->dominoesAtPlay.at(0).getTop();//bot<->top primer elemento (0)
    top_bot = dominoes.at(dominoesIdx).getTop() == board->dominoesAtPlay.at(board->dominoesAtPlay.size()-1).getBot();//top<->bot ultimo elemento (1)
    bot_bot = dominoes.at(dominoesIdx).getBot() == board->dominoesAtPlay.at(board->dominoesAtPlay.size()-1).getBot();//bot<->bot ultimo elemento (1)

    //Checkea a que lado poner la ficha
    bool pickingDomino = true;
    SDL_Event ev1;
    cout << "Escoja un lado para poner su domino!" << endl;
    while(pickingDomino){
        while(SDL_PollEvent(&ev1) != 0) {
            if (ev1.type == SDL_QUIT) exit(0);
            if (ev1.type == SDL_MOUSEBUTTONDOWN) {
                GraphicOBJ* tempGraphicOBJ = board->dominoesAtPlay.at(board->dominoesAtPlay.size()-1).getGraphicOBJ();
                //Si el mouse da click a la derecha de las fichas.
                if(ev1.button.x > tempGraphicOBJ->getDestRect()->x + tempGraphicOBJ->getDestRect()->w){
                    if(top_bot || bot_bot){
                        //TODO AQUI LOGICA DE QUE HACE AL VALIDAR ESTE LADO
                        if(dominoes.at(dominoesIdx).getBot() == board->dominoesAtPlay.at(board->dominoesAtPlay.size()-1).getBot()){
                            //Se cambia el orden de los valores del domino para que se inserte correctamente
                            short tempDominoNumber = dominoes.at(dominoesIdx).getTop();
                            dominoes.at(dominoesIdx).setTop(dominoes.at(dominoesIdx).getBot());
                            dominoes.at(dominoesIdx).setBot(tempDominoNumber);

                            //Se cambia la textura del domino //TODO
                            rotateDomino(window,renderer,board,dominoesIdx);
                        }
                        //Insertamos el domino en el tablero
                        board->dominoesAtPlayINSETR(board->dominoesAtPlay.size(),&dominoes.at(dominoesIdx));
                        //Borramos el domino de nuestras fichas
                        dominoes.erase(dominoes.begin()+dominoesIdx);
                        //Actualizamos el ultimo jugador
                        board->lastPlayer = this;
                        pickingDomino = false;
                        break;
                    }
                    //Si el mouse da click a la izquierda de las fichas.
                }else if(ev1.button.x < tempGraphicOBJ->getDestRect()->x){
                    if(top_top || bot_top){
                        //TODO AQUI LOGICA DE QUE HACE AL VALIDAR ESTE LADO
                        if(dominoes.at(dominoesIdx).getTop() == board->dominoesAtPlay.at(0).getTop()){
                            //Se cambia el orden de los valores del domino para que se inserte correctamente
                            short tempDominoNumber = dominoes.at(dominoesIdx).getTop();
                            dominoes.at(dominoesIdx).setTop(dominoes.at(dominoesIdx).getBot());
                            dominoes.at(dominoesIdx).setBot(tempDominoNumber);

                            //Se cambia la textura del domino //TODO
                            rotateDomino(window,renderer,board,dominoesIdx);
                        }
                        //Insertamos el domino en el tablero
                        board->dominoesAtPlayINSETR(0,&dominoes.at(dominoesIdx));
                        //Borramos el domino de nuestras fichas
                        dominoes.erase(dominoes.begin()+dominoesIdx);
                        //Actualizamos el ultimo jugador
                        board->lastPlayer = this;
                        pickingDomino = false;
                        break;
                    }
                }
            }
            SDL_Delay(50);
        }
    }
    cout << "FUNCTION ENDS!!!\n";
    /*//Escoje a que lado se pone la ficha

    //Poner ficha en el tablero
    switch (pick){
        case 0://El 0 es para agregar a la izquierda
            //En el caso que esten invertidos para conectarse. se cambian
            if(dominoes.at(idxDomino).getTop() == board->dominoesAtPlay.at(0).getTop()){
                //Se cambia el orden de los valores del domino para que se inserte correctamente
                short tempDominoNumber = dominoes.at(idxDomino).getTop();
                dominoes.at(idxDomino).setTop(dominoes.at(idxDomino).getBot());
                dominoes.at(idxDomino).setBot(tempDominoNumber);

                //Se cambia la textura del domino //TODO
                rotateDomino(window,renderer,board,idxDomino);
            }
            board->dominoesAtPlayINSETR(0,&dominoes.at(idxDomino));
            break;
        case 1://El 1 es para agregar a la derecha
            //En el caso que esten invertidos para conectarse. se cambian
            if(dominoes.at(idxDomino).getBot() == board->dominoesAtPlay.at(board->dominoesAtPlay.size()-1).getBot()){
                //Se cambia el orden de los valores del domino para que se inserte correctamente
                short tempDominoNumber = dominoes.at(idxDomino).getTop();
                dominoes.at(idxDomino).setTop(dominoes.at(idxDomino).getBot());
                dominoes.at(idxDomino).setBot(tempDominoNumber);

                //Se cambia la textura del domino //TODO
                rotateDomino(window,renderer,board,idxDomino);
            }
            board->dominoesAtPlayINSETR(board->dominoesAtPlay.size(),&dominoes.at(idxDomino));
            break;
    }
    dominoes.erase(dominoes.begin()+getDominoIdx(dominoes,possible.at(0)));//Borramos el domino correcpondiente del jugador
*/}

void Player::eat(SDL_Window* window,SDL_Renderer*renderer,Board* board){
    //El jugador se come el primer domino de la pila de dominoes para comer
    Domino tempDomino(0,0);
    tempDomino = board->dominoesToEat.at(0);
    dominoes.push_back(tempDomino);
    //DominoesToEat.Pop()
    board->dominoesToEat.erase(board->dominoesToEat.begin()+0);
    ate = true;
}


void Player::eventHandler(SDL_Window* window,SDL_Renderer*renderer,Graphics* graphics,Board* board){
    /*
     * Esta Funcion Maneja los Eventos
     */

    //Este caso solo se va a dar con el jugador que tenga la ficha que comienza
    if(board->dominoesAtPlay.empty()){
        placeDominoe(window,renderer,board,NULL);
        playerInTurn = false;
    }else{
        if(getPlayableDominoes(board).empty()){//No puede poner ficha
            if(ate){
                cash-=500;
                board->profit+=500;
                playerInTurn = false;
                ate = false;//reseteamos si ha comido fucha porque termina su turno
            }else
                eat(window,renderer,board);
        }else{//Osea puede poner ficha
            SDL_Event ev;
            while(SDL_PollEvent(&ev) != 0) {
                if (ev.type == SDL_QUIT) exit(0);
                if (ev.type == SDL_MOUSEBUTTONDOWN) {
                    //Para las imagenes
                    for (int k = 0; k < dominoes.size(); ++k) {
                        //Si se encuentra dentro de las dimensiones del objeto
                        if (ev.button.x >= dominoes.at(k).getGraphicOBJ()->getDestRect()->x && ev.button.x < dominoes.at(
                                k).getGraphicOBJ()->getDestRect()->x + dominoes.at(k).getGraphicOBJ()->getDestRect()->w
                            && ev.button.y >= dominoes.at(k).getGraphicOBJ()->getDestRect()->y && ev.button.y <= dominoes.at(
                                k).getGraphicOBJ()->getDestRect()->y + dominoes.at(k).getGraphicOBJ()->getDestRect()->h) {
                            //TODO AQUI LO QUE PASA!!!
                            cout<<"si nena\n";
                            placeDominoe(window,renderer,board,&dominoes.at(k));
                        }
                    }
                }
            }
        }
    }
}

void Player::objectsModifier(Graphics* graphics,Board* board){
    /*
     * Esta Funcion Actualiza GraphicOBJ de las fichas del jugador y del tablero
     */

    //Render Dominoes
    int modifier = DOMINOSIZE_W+DISTANCEINBETWEEN;//Sirve para colocar los objetos en la pantalla ordenadamente
    for (int j = 0; j < dominoes.size(); ++j) {
        int wOfRect = dominoes.at(j).getGraphicOBJ()->getDestRect()->w;
        int hOfRect = dominoes.at(j).getGraphicOBJ()->getDestRect()->h;
        dominoes.at(j).getGraphicOBJ()->modifyDestRect(300+modifier,450,wOfRect,hOfRect);
        modifier += DOMINOSIZE_W+DISTANCEINBETWEEN;
    }

    //Render DominoesAtPlay
    modifier = DOMINOSIZE_W+DISTANCEINBETWEEN;
    for (int j = 0; j < board->dominoesAtPlay.size(); ++j) {
        int wOfRect = board->dominoesAtPlay.at(j).getGraphicOBJ()->getDestRect()->w;
        int hOfRect = board->dominoesAtPlay.at(j).getGraphicOBJ()->getDestRect()->h;
        board->dominoesAtPlay.at(j).getGraphicOBJ()->modifyDestRect(300+modifier,300,wOfRect,hOfRect);
        modifier += DOMINOSIZE_W+DISTANCEINBETWEEN;
    }

    //We add the dominoes graphicOBJS to graphics
    renderPlayerDominoes(graphics);
    //We add the dominoes graphicOBJS to graphics
    for (int i = 0; i < board->dominoesAtPlay.size(); ++i) {
        graphics->imagesToRenderPUSH_BACK(*board->dominoesAtPlay.at(i).getGraphicOBJ());
    }

}


void Player::update(SDL_Window* window,SDL_Renderer*renderer,Graphics* graphics,Board* board) {
    /*
     * Esta funcion hace el uldate.
     * Primero toma lee los eventos, luego modifica los objetos para mostrarlos en pantalla correctamente
     * y luego los renderiza
     */
    playerInTurn = true;
    while (playerInTurn){
        eventHandler(window,renderer,graphics,board);
        objectsModifier(graphics,board);
        //We render the OBJs
        graphics->render(1);
    }
}





