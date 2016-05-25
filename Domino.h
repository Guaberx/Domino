//
// Created by Guaberx on 18.05.2016.
//

#ifndef PROYECTO_DOMINO_H
#define PROYECTO_DOMINO_H
#define DOMINOSIZE_W 33
#define DOMINOSIZE_H 80
#define DISTANCEINBETWEEN 5

#include <SDL.h>
#include "Graphics.h"

class Domino{
    unsigned int top;
    unsigned int bot;
    GraphicOBJ* graphicOBJ;
public:
    Domino(unsigned int top, unsigned int bot);
    void createDominoImage(SDL_Window* window, SDL_Renderer* renderer,string imagePath);

    unsigned int getTop();//Retorna el valor de la cara de arriba del domino
    unsigned int getBot();//Retorna el valor de la cara de abajo domino
    void setTop(unsigned int topNew);
    void setBot(unsigned int botNew);


    GraphicOBJ* getGraphicOBJ();

    void graphicOBJToRenderer(Graphics* graphics);

    void setTexture(SDL_Window* window,SDL_Renderer* renderer,string imagePath);


    //Operator overloading so it can compare
    bool operator > (const Domino& other);
    bool operator == (const Domino& other);
    bool operator != (const Domino& other);
};

#endif //PROYECTO_DOMINO_H
