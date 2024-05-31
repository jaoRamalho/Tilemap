#pragma once
#include "Entidade.hpp"

class Plataforma : public Entidade{
    private:

    public:
    Plataforma(sf::Vector2f posicao, sf::Vector2f tamanho) : Entidade(posicao, tamanho){
        tipo = 2;
        shape.setFillColor(sf::Color::Green);
    }
    ~Plataforma(){}
    
    void execute(){}
};