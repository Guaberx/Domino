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
    GraphicOBJ(SDL_Window* window, SDL_Renderer* renderer,string imagePath, int x, int y, int w, int h){
        modifySrcRect(x,y,w,h);
        modifyDestRect(x,y,w,h);
        //Make the texture
        setTextureFromPath(window,renderer,imagePath);
    }
    ~GraphicOBJ(){
        //Free memory
    }
    SDL_Rect* getSrcRect(){
        return &srcR;
    }
    SDL_Rect* getDestRect(){
        return &DestR;
    }

    void modifySrcRect(int x, int y, int w, int h){
        //Define rect for size, position of the image src
        DestR.x = x;
        DestR.y = y;
        DestR.w = w;
        DestR.h = h;
    }
    void modifyDestRect(int x, int y, int w, int h){
        //Define rect for size, position of the image dest
        DestR.x = x;
        DestR.y = y;
        DestR.w = w;
        DestR.h = h;
    }

    SDL_Texture* getTexture(){
        return texture;
    }
    void setTextureFromPath(SDL_Window* window,SDL_Renderer* renderer,string imagePath){//DANGER MAYBE
        //We load a surface
        SDL_Surface* windowSurfaceTemp = SDL_GetWindowSurface(window);
        SDL_Surface* loadingSurface = OptimizeSurface(imagePath, windowSurfaceTemp);
        texture = SDL_CreateTextureFromSurface(renderer,loadingSurface);
        SDL_FreeSurface(loadingSurface);
        SDL_FreeSurface(windowSurfaceTemp);
    }

    //Optimiza los surfaces para el tamano adecuado. utilizar al usar una imagen o algo con surface!!!!
    static SDL_Surface* OptimizeSurface(std::string filePath, SDL_Surface* windowSurface){
        SDL_Surface* optimizedSurface = NULL;
        //SDL_RWops* test; test = SDL_RWFromFile(filePath.c_str(),"rb");//TODO HAD TO DO SOME CHANGES CUZ OF DLL
        SDL_Surface* surface = IMG_Load(filePath.c_str());//IMG_LoadPNG_RW(test);
        int imageFlags = IMG_INIT_JPG;
        //if(IMG_Init(imageFlags) != imageFlags){
        if((IMG_Init(imageFlags) && imageFlags)){
            cout << "Ha ocurrido un error cargando la imagen: " << filePath << " " << IMG_GetError << endl;
        }

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

    void render(bool clearVector){
        //clartVector defines if the render itself is going to clear imagesToRender vector(1:clean, 0:not clean)
        //Screen render
        //First we blit the objects
        if(window == NULL || Main_Renderer == NULL){
            cout <<"Se ha producido un error renderizando"<<endl;
            exit(1);
        }
        for (int i = 0; i < imagesToRender.size(); ++i) {
            SDL_RenderCopy(Main_Renderer,imagesToRender.at(i).getTexture(),
                           NULL,imagesToRender.at(i).getDestRect());
        }
        //The function that makes a flip
        SDL_RenderPresent(Main_Renderer);
        SDL_Delay(20);
        if(clearVector)
            cleanVector();
    }

    vector<GraphicOBJ> getVector(){
        return imagesToRender;
    }

    void cleanVector(){
        imagesToRender.clear();
    }
};

#endif //PROYECTO_GRAPHICS_H
