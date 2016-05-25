//
// Created by Guaberx on 19.05.2016.
//
#include "Domino.h"

Domino::Domino(unsigned int top, unsigned int bot):top(top),bot(bot){}

void Domino::createDominoImage(SDL_Window* window, SDL_Renderer* renderer,string imagePath){
    //Crea un nuevo GraphicOBJ
    //Inicializamos el domino con su Graphic object
    graphicOBJ = new GraphicOBJ(window,renderer,imagePath,100,100,DOMINOSIZE_W,DOMINOSIZE_H);
}

unsigned int Domino::getTop(){
    return top;
}
unsigned int Domino::getBot(){
    return bot;
}
void Domino::setTop(unsigned int topNew){
    top = topNew;
}
void Domino::setBot(unsigned int botNew){
    bot = botNew;
}

GraphicOBJ* Domino::getGraphicOBJ(){
    return graphicOBJ;
}

void Domino::graphicOBJToRenderer(Graphics* graphics){
    graphics->imagesToRenderPUSH_BACK(*graphicOBJ);
}

void Domino::setTexture(SDL_Window* window,SDL_Renderer* renderer,string imagePath){
    //Para cambiar la ficha de domino(Greaficamente)
    graphicOBJ->setTextureFromPath(window,renderer,imagePath);
}


//Operator overloading so it can compare
bool Domino::operator > (const Domino& other){
    if(top>other.top){
        return true;
    }
    if(top == other.top)
    if(bot>other.bot){
        return true;
    }
    return false;
}
bool Domino::operator == (const Domino& other){
    return top==other.top && bot==other.bot;
}
bool Domino::operator != (const Domino& other){
    return !(top==other.top && bot==other.bot);
}


