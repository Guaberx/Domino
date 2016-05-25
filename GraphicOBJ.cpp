//
// Created by Guaberx on 24.05.2016.
//

#include "GraphicOBJ.h"

GraphicOBJ::GraphicOBJ(SDL_Window* window, SDL_Renderer* renderer,string imagePath, int x, int y, int w, int h){
    angle = 0;
    modifySrcRect(x,y,w,h);
    modifyDestRect(x,y,w,h);
    //Make the texture
    setTextureFromPath(window,renderer,imagePath);
}

GraphicOBJ::GraphicOBJ(SDL_Window* window, SDL_Renderer* renderer,string fountPath,int size,string text){
    angle = 0;
    SDL_Color clfg = {255,255,255,0};//Se puede cambiar luego para recibir mas colores
    TTF_Font* fount = TTF_OpenFont(fountPath.c_str(),size);
    SDL_Surface* fountSurface = TTF_RenderText_Solid(fount,text.c_str(),clfg);
    texture = SDL_CreateTextureFromSurface(renderer,fountSurface);
    //Rect
    DestR.x = DestR.y = 0;
    SDL_QueryTexture(texture,NULL,NULL,&DestR.w,&DestR.h);

    SDL_FreeSurface(fountSurface);
}

GraphicOBJ::~GraphicOBJ(){
}
SDL_Rect* GraphicOBJ::getSrcRect(){
    return &srcR;
}
SDL_Rect* GraphicOBJ::getDestRect(){
    return &DestR;
}
int* GraphicOBJ::getAngle(){
    return &angle;
}

void GraphicOBJ::modifySrcRect(int x, int y, int w, int h){
    //Define rect for size, position of the image src
    DestR.x = x;
    DestR.y = y;
    DestR.w = w;
    DestR.h = h;
}
void GraphicOBJ::modifyDestRect(int x, int y, int w, int h){
    //Define rect for size, position of the image dest
    DestR.x = x;
    DestR.y = y;
    DestR.w = w;
    DestR.h = h;
}

SDL_Texture* GraphicOBJ::getTexture(){
    return texture;
}
void GraphicOBJ::setTextureFromPath(SDL_Window* window,SDL_Renderer* renderer,string imagePath){//DANGER MAYBE
    //We load a surface
    SDL_Surface* windowSurfaceTemp = SDL_GetWindowSurface(window);
    SDL_Surface* loadingSurface = OptimizeSurface(imagePath, windowSurfaceTemp);
    texture = SDL_CreateTextureFromSurface(renderer,loadingSurface);
    SDL_FreeSurface(loadingSurface);
    SDL_FreeSurface(windowSurfaceTemp);
}


//Optimiza los surfaces para el tamano adecuado. utilizar al usar una imagen o algo con surface!!!!
    SDL_Surface* GraphicOBJ::OptimizeSurface(std::string filePath, SDL_Surface* windowSurface){
    SDL_Surface* optimizedSurface = NULL;
    //SDL_RWops* test; test = SDL_RWFromFile(filePath.c_str(),"rb");//TODO HAD TO DO SOME CHANGES CUZ OF DLL
    //SDL_Surface* surface = IMG_LoadPNG_RW(test);
    SDL_Surface* surface = NULL;
    surface = IMG_Load(filePath.c_str());
    int imageFlags = IMG_INIT_JPG;

    //if(IMG_Init(imageFlags) != imageFlags){
    if((IMG_Init(imageFlags) && imageFlags)){
        cout << "Ha ocurrido un error cargando la imagen: " << filePath << " " << IMG_GetError << endl;
    }

    if(surface == NULL){
        cout << "Error cargando Surface: " << filePath << " " << SDL_GetError() << endl;
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
