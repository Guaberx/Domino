//
// Created by Guaberx on 22.05.2016.
//
#ifndef PROYECTO_GRAPHICS_H
#define PROYECTO_GRAPHICS_H
#define RESOLUTION_W 960
#define RESOLUTION_H 540
#define TITTLE "Super Awesome Domino"

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "GraphicOBJ.h"

//Game.h porque es lo que vamos a renderizar

class Graphics{
    SDL_Window* window;
    SDL_Renderer* Main_Renderer;
    vector<GraphicOBJ> imagesToRender;
public:
    Graphics(SDL_Window* window1, SDL_Renderer* renderer);

    ~Graphics();
    void imagesToRenderPUSH_BACK(GraphicOBJ obj);

    void render(bool clearVector);

    vector<GraphicOBJ> getVector();

    void cleanVector();
};

#endif //PROYECTO_GRAPHICS_H
