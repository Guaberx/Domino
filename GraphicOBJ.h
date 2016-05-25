//
// Created by Guaberx on 24.05.2016.
//

#ifndef PROYECTO_GRAPHICOBJ_H
#define PROYECTO_GRAPHICOBJ_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::vector;

class GraphicOBJ{
    SDL_Rect srcR;//Source image rectangle
    SDL_Rect DestR;//Destination rectangle
    SDL_Texture* texture;//We use this one to render on the screen
public:
    GraphicOBJ(SDL_Window* window, SDL_Renderer* renderer,string imagePath, int x, int y, int w, int h);
    ~GraphicOBJ();
    SDL_Rect* getSrcRect();
    SDL_Rect* getDestRect();
    void modifySrcRect(int x, int y, int w, int h);
    void modifyDestRect(int x, int y, int w, int h);

    SDL_Texture* getTexture();
    void setTextureFromPath(SDL_Window* window,SDL_Renderer* renderer,string imagePath);

    //Optimiza los surfaces para el tamano adecuado. utilizar al usar una imagen o algo con surface!!!!
    SDL_Surface* OptimizeSurface(std::string filePath, SDL_Surface* windowSurface);
};

#endif //PROYECTO_GRAPHICOBJ_H
