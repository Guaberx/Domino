//
// Created by Guaberx on 18.05.2016.
//

#ifndef PROYECTO_DOMINO_H
#define PROYECTO_DOMINO_H

class Domino{
    unsigned int top;
    unsigned int bot;
public:
    Domino(unsigned int top, unsigned int bot):top(top),bot(bot){}
    unsigned int getTop();//Retorna el valor de la cara de arriba del domino
    unsigned int getBot();//Retorna el valor de la cara de abajo domino
    void setTop(unsigned int topNew);
    void setBot(unsigned int botNew);


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
