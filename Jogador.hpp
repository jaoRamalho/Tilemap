#pragma once
#include "Plataforma.hpp"

class Jogador : public Entidade{
    private:

    public:
    Jogador(sf::Vector2f posicao, sf::Vector2f tamanho) : Entidade(posicao, tamanho){
        tipo = 1;
        shape.setFillColor(sf::Color::Red);
    }
    ~Jogador(){}
    
    void execute();
    void colidir(Plataforma* plat, sf::FloatRect intersects);
};

void Jogador::execute(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        shape.move(sf::Vector2f(0, -5));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        shape.move(sf::Vector2f(0, 5));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        shape.move(sf::Vector2f(-5, 0));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        shape.move(sf::Vector2f(5, 0));
    }
}

void Jogador::colidir(Plataforma* plat, sf::FloatRect intersects){
    // Calculate the overlap between the player and the platform
    sf::Vector2f overlap = sf::Vector2f(0, 0);
    if (intersects.width < intersects.height) {
        if (shape.getPosition().x < plat->getPosicao().x) {
            overlap.x = -intersects.width;
        } else {
            overlap.x = +intersects.width;
        }
    } else {
        if (shape.getPosition().y < plat->getPosicao().y) {
            overlap.y = -intersects.height;
        } else {
            overlap.y = +intersects.height;
        }
    }

    // Update the player's position based on the overlap
    shape.move(overlap);
}