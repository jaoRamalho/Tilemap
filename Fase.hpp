#pragma once
#include "tilemap.hpp"
#include "GerenciadorColisao.hpp"

class Fase{
    private:
        sf::RenderWindow* window;
        GerenciadorColisao* gerenColisao;
        Tilemap tilemap;
        std::vector<Entidade*> entidades;
        sf::Texture textura_mapa;
        sf::Sprite sprite_mapa;
        QuadTree quadtree;

    public:
        Fase(std::string tilemapFase, sf::RenderWindow* window);
        ~Fase();

        void executeEntidades();
        void executar();
        void desenhar();
};

Fase::Fase(std::string tilemapFase, sf::RenderWindow* window) : quadtree(0, 0, 1920, 1080), tilemap(&quadtree){
    gerenColisao = GerenciadorColisao::getInstancia(&quadtree);
    this->window = window;
    tilemap.criarMapa(tilemapFase, &entidades, &textura_mapa);
    sprite_mapa.setTexture(textura_mapa);

    for (auto entidade : entidades) {
        quadtree.inserir(entidade, entidade->getShape().getGlobalBounds());
    }
}

Fase::~Fase() {
    
}

void Fase::executeEntidades() {
    for (auto entidade : entidades) {
        entidade->execute();
    }
}
void Fase::executar() {
    executeEntidades();
    gerenColisao->executar(&entidades);
    //gerenColisao->executarBruto(&entidades);
}

void Fase::desenhar() {
    window->draw(sprite_mapa);  
    for (auto entidade : entidades) {
        entidade->desenhar(window);
    }   
}