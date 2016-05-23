//
// Created by Guaberx on 22.05.2016.
//

#ifndef PROYECTO_GRAPHICS_H
#define PROYECTO_GRAPHICS_H
#define RESOLUTION_W 960
#define RESOLUTION_H 540
#define TITTLE "Super Awesome Domino"

//Game.h porque es lo que vamos a renderizar
#include <SDL.h>
#include <cstdlib>
//Optimiza los surfaces para el tamano adecuado. utilizar al usar una imagen o algo con surface!!!!
SDL_Surface* OptimizeSurface(std::string filePath, SDL_Surface* windowSurface){
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());

    if(surface == NULL){
        cout << "Error cargando Surface: " << SDL_GetError() << endl;
    }else{
        //Se convierte al formato correcto para usarlo
        //BMP vienen normalmente en 24 bits. pero vamos a usar diferentes en la pantalla
        //Por lo que toca cambiarle el formato.
        optimizedSurface = SDL_ConvertSurface(surface,windowSurface->format,0);
        if(optimizedSurface == NULL){
            cout << "Error cargando Optimized Surface: " << SDL_GetError() << endl;
        }
    }
    SDL_FreeSurface(surface);//Borramos el contenido del apuntador
    surface = NULL;//Buenas practicas
    return optimizedSurface;
}

class GraphicOBJ{
    SDL_Surface* loadingSurface;
    SDL_Rect srcR;//Source image rectangle
    SDL_Rect DestR;//Destination rectangle
    SDL_Texture* texture;//We use this one to render on the screen
public:
    GraphicOBJ(SDL_Window* window, SDL_Renderer* Main_Renderer,string imagePath, int x, int y, int w, int h){
        //We load a surface
        SDL_Surface* windowSurfaceTemp = SDL_GetWindowSurface(window);
        loadingSurface = OptimizeSurface(imagePath, windowSurfaceTemp);//MAYBE SGV
        //Define rect for size, position of the image src
        srcR.x = x;
        srcR.y = y;
        srcR.w = w;
        srcR.h = h;
        //Define rect for size, position of the image dest
        DestR.x = x;
        DestR.y = y;
        DestR.w = w;
        DestR.h = h;
        //Make the texture
        texture = SDL_CreateTextureFromSurface(Main_Renderer,loadingSurface);
        //Free surface
        SDL_FreeSurface(loadingSurface);
    }
    ~GraphicOBJ(){
        //Free memory
    }
    SDL_Surface* getSurface(){
        return loadingSurface;
    }
    SDL_Rect* getSrcRect(){
        return &srcR;
    }
    SDL_Rect* getDestRect(){
        return &DestR;
    }

    SDL_Texture* getTexture(){
        return texture;
    }
};

class Graphics{
    SDL_Window* window;
    SDL_Renderer* Main_Renderer;
    vector<GraphicOBJ> imagesToRender;
public:
    Graphics(SDL_Window* window1, SDL_Renderer* renderer){
        window = window1;
        Main_Renderer = renderer;
    }

    ~Graphics(){
        for (int i = 0; i < imagesToRender.size(); ++i) {
            SDL_DestroyTexture(imagesToRender.at(i).getTexture());
        }
    }
    void imagesToRenderPUSH_BACK(GraphicOBJ obj){
        imagesToRender.push_back(obj);
    }

    void render(){
        //Screen render
        //First we blit the objects
        for (int i = 0; i < imagesToRender.size(); ++i) {
            SDL_RenderCopy(Main_Renderer,imagesToRender.at(i).getTexture(),
                           imagesToRender.at(i).getSrcRect(),imagesToRender.at(i).getDestRect());
        }
        //The function that makes a flip
        SDL_RenderPresent(Main_Renderer);
    }
};

#endif //PROYECTO_GRAPHICS_H
