//
// Created by Guaberx on 24.05.2016.
//

#include "Graphics.h"

Graphics::Graphics(SDL_Window* window1, SDL_Renderer* renderer){
    window = window1;
    Main_Renderer = renderer;

}

Graphics::~Graphics(){
    for (int i = 0; i < imagesToRender.size(); ++i) {
        SDL_DestroyTexture(imagesToRender.at(i).getTexture());
    }
}
void Graphics::imagesToRenderPUSH_BACK(GraphicOBJ obj){
    imagesToRender.push_back(obj);
}

void Graphics::render(bool clearVector){
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

vector<GraphicOBJ> Graphics::getVector(){
    return imagesToRender;
}

void Graphics::cleanVector(){
    imagesToRender.clear();
}
