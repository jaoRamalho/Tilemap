#pragma once
#include "Plataforma.hpp"

class Jogador : public Entidade{
    private:
        bool pulo;

    public:
    Jogador(sf::Vector2f posicao, sf::Vector2f tamanho, QuadTree* q) : Entidade(posicao, tamanho, q), pulo(false){
        tipo = 1;
        shape.setFillColor(sf::Color::Red);
    }
    ~Jogador(){}
    
    void execute();
    void move();
    void colidir(Plataforma* plat, sf::FloatRect intersects);
};

void Jogador::execute(){
   movimento = {0, gravidade};
   move();

   shape.move(movimento);
   atualizarQuadtree();
}

void Jogador::move(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !pulo) {
        gravidade -= 15;
        pulo = true;
    } else {
        acelerarGravidade();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        movimento.x -= 10;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        movimento.x += 10;
    }
}

void Jogador::colidir(Plataforma* plat, sf::FloatRect intersects){
    // Calculate the overlap between the player and the platform
    sf::Vector2f overlap = sf::Vector2f(0, 0);
    if (intersects.width < intersects.height) {
        if (shape.getPosition().x < plat->getPosicao().x) {
            overlap.x = -intersects.width;
        } else {
            overlap.x = intersects.width;
        }
    } else {
        if (shape.getPosition().y < plat->getPosicao().y) {
            overlap.y = -intersects.height;
            gravidade = 0;
            pulo = false;
        } else {
            overlap.y = intersects.height;
            gravidade = -gravidade;
        }
    }

    // Update the player's position based on the overlap
    shape.move(overlap);
}