#pragma once
#include "tilemap.hpp"
#include "QuadTree.hpp"

class GerenciadorColisao{
    private:
        QuadTree* quadtree;
        std::unordered_map<int, std::function<void(Entidade*, Entidade*, sf::FloatRect)>> mapaColisoes;
        static GerenciadorColisao* instancia;
        GerenciadorColisao();

    public:
        ~GerenciadorColisao();

        void criarMapaColisoes();
        static GerenciadorColisao* getInstancia();
        void executar(std::vector<Entidade*>* entidades);
        void verificarColisao(Entidade* ent1, Entidade* ent2, sf::FloatRect rect1);
};

GerenciadorColisao* GerenciadorColisao::instancia = nullptr;
GerenciadorColisao::GerenciadorColisao(){
    criarMapaColisoes();
    quadtree = new QuadTree(0, 0, 1920, 1080);
}

GerenciadorColisao::~GerenciadorColisao(){
}

GerenciadorColisao* GerenciadorColisao::getInstancia(){
    if(instancia == nullptr)
        instancia = new GerenciadorColisao();
    return instancia;
}


void GerenciadorColisao::verificarColisao(Entidade* ent1, Entidade* ent2, sf::FloatRect rect1){
    sf::FloatRect rect2 = ent2->getShape().getGlobalBounds();
    sf::FloatRect intersects;
    if(rect1.intersects(rect2, intersects)){
        mapaColisoes[ent2->getTipo()](ent1, ent2, intersects);
        mapaColisoes[ent1->getTipo()](ent2, ent1, intersects);
    }
}

void GerenciadorColisao::executar(std::vector<Entidade*>* entidades){
    for(auto ent : *entidades){
        quadtree->inserir(ent);
    }

    for(Entidade* ent : *entidades){
        std::unordered_set<Entidade*> retorno;
        quadtree->recuperar(&retorno, ent);
        sf::FloatRect entBounds = ent->getShape().getGlobalBounds();
        int tipo1 = ent->getTipo();
        for(Entidade* e : retorno){
            int tipo2 = e->getTipo();
            if(ent != e && !(tipo2 == 2 && tipo1 == 2)){
                //verificar se houve colisao
                verificarColisao(ent, e, entBounds);
            }
        }
    }

    quadtree->limpar();
}

void GerenciadorColisao::criarMapaColisoes(){
    mapaColisoes[1] = [](Entidade* ent, Entidade* jogador, sf::FloatRect intersect){ ent->colidir(dynamic_cast<Jogador*>(jogador), intersect);};
    mapaColisoes[2] = [](Entidade* ent, Entidade* plataforma, sf::FloatRect intersect){ ent->colidir(dynamic_cast<Plataforma*>(plataforma), intersect);};

}