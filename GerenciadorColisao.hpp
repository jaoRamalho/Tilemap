#pragma once
#include "tilemap.hpp"
#include "QuadTree.hpp"

class GerenciadorColisao{
    private:
        QuadTree* quadtree;
        std::unordered_map<int, std::function<void(Entidade*, Entidade*, sf::FloatRect)>> mapaColisoes;
        static GerenciadorColisao* instancia;
        GerenciadorColisao(QuadTree* quadtree);

    public:
        ~GerenciadorColisao();

        void criarMapaColisoes();
        static GerenciadorColisao* getInstancia(QuadTree* quadtree);
        void executar(std::vector<Entidade*>* entidades);
        void verificarColisao(Entidade* ent1, Entidade* ent2);
        void executarBruto(std::vector<Entidade*>* entidades);
};

GerenciadorColisao* GerenciadorColisao::instancia = nullptr;
GerenciadorColisao::GerenciadorColisao(QuadTree* quadtree) : quadtree(quadtree){
    criarMapaColisoes();
}

GerenciadorColisao::~GerenciadorColisao(){
    quadtree->limpar();
    delete quadtree;
    quadtree = nullptr;
}

GerenciadorColisao* GerenciadorColisao::getInstancia(QuadTree* quadtree){
    if(instancia == nullptr)
        instancia = new GerenciadorColisao(quadtree);
    return instancia;
}


void GerenciadorColisao::verificarColisao(Entidade* ent1, Entidade* ent2){
    sf::FloatRect rect2 = ent2->getShape().getGlobalBounds();
    sf::FloatRect rect1 = ent1->getShape().getGlobalBounds();
    sf::FloatRect intersects;
    if(rect1.intersects(rect2, intersects)){
        mapaColisoes[ent2->getTipo()](ent1, ent2, intersects);
        mapaColisoes[ent1->getTipo()](ent2, ent1, intersects);
    }
    ent1->setColor();
    ent2->setColor();
}

void GerenciadorColisao::executar(std::vector<Entidade*>* entidades){
    int cont = 0;
    std::vector<Entidade*> entidadesCopia = *entidades;
    
    for(Entidade* ent : *entidades){
        std::unordered_set<Entidade*> retorno;
        quadtree->recuperar(&retorno, ent->getShape().getGlobalBounds());
        int tipo1 = ent->getTipo();
        for(Entidade* e : retorno){
            int tipo2 = e->getTipo();
            if(ent != e){
                //verificar se houve colisao
                verificarColisao(ent, e);
            }
            cont++;
        }
    }
    //std::cout << cont << std::endl;
}

void GerenciadorColisao::executarBruto(std::vector<Entidade*>* entidades){
    int cont = 0;
    for(int i = 0; i < entidades->size(); i++){
        Entidade* ent1 = entidades->at(i);
        for(int j = i + 1; j < entidades->size(); j++){
            Entidade* ent2 = entidades->at(j);
            if(ent1 != ent2){
                verificarColisao(ent1, ent2);
            }
            cont++;
        }
    }
    //std::cout << cont << std::endl;
}


void GerenciadorColisao::criarMapaColisoes(){
    mapaColisoes[1] = [](Entidade* ent, Entidade* jogador, sf::FloatRect intersect){ ent->colidir(dynamic_cast<Jogador*>(jogador), intersect);};
    mapaColisoes[2] = [](Entidade* ent, Entidade* plataforma, sf::FloatRect intersect){ ent->colidir(dynamic_cast<Plataforma*>(plataforma), intersect);};

}