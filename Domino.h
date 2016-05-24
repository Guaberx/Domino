//
// Created by Guaberx on 18.05.2016.
//

#ifndef PROYECTO_DOMINO_H
#define PROYECTO_DOMINO_H
#define DOMINOSIZE_W 25
#define DOMINOSIZE_H 60

#include <SDL.h>
#include "Graphics.h"

class Domino{
    unsigned int top;
    unsigned int bot;
    GraphicOBJ* graphicOBJ;
public:
    Domino(unsigned int top, unsigned int bot):top(top),bot(bot){
    }
    void createDominoImage(SDL_Window* window, SDL_Renderer* renderer,string imagePath){
        //Crea un nuevo GraphicOBJ
        //Inicializamos el domino con su Graphic object
        graphicOBJ = new GraphicOBJ(window,renderer,imagePath,100,100,DOMINOSIZE_W,DOMINOSIZE_H);
    }
    unsigned int getTop();//Retorna el valor de la cara de arriba del domino
    unsigned int getBot();//Retorna el valor de la cara de abajo domino
    void setTop(unsigned int topNew);
    void setBot(unsigned int botNew);


    GraphicOBJ* getGraphicOBJ(){
        return graphicOBJ;
    }

    void graphicOBJToRenderer(Graphics* graphics){
        graphics->imagesToRenderPUSH_BACK(*graphicOBJ);
    }

    void setTexture(SDL_Window* window,SDL_Renderer* renderer,string imagePath){
        //Para cambiar la ficha de domino(Greaficamente)
        graphicOBJ->setTextureFromPath(window,renderer,imagePath);
    }


    //Operator overloading so it can compare
    bool operator > (const Domino& other){
        if(top>other.top){
            return true;
        }
        if(top == other.top)
            if(bot>other.bot){
                return true;
            }
        return false;
    }
    bool operator == (const Domino& other){
        return top==other.top && bot==other.bot;
    }
    bool operator != (const Domino& other){
        return !(top==other.top && bot==other.bot);
    }
};

#endif //PROYECTO_DOMINO_H
