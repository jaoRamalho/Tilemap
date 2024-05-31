#pragma once
#include "Entidade.hpp"
#include <vector>
#include <unordered_set>

#define QT_MAX_ENTIDADES 6 // quantidade maxima de entidades que um no pode ter
#define QT_MAX_NIVEIS 10 // quantidade maxima de niveis que a quadtree pode ter (ALTURA DA ARVORE) (obbs: n está limitado ainda)

class QuadTree{
    private:

        int nivel;
        std::vector<Entidade*> entidades;
        QuadTree* nos[4];
        float posX, posY, largura, altura;
        sf::FloatRect area;

    public:
        QuadTree(float posX, float posY, float largura, float altura, int nivel = 0){
            this->posX = posX;
            this->posY = posY;
            this->largura = largura;
            this->altura = altura;
            this->nivel = nivel;
            area = sf::FloatRect(posX, posY, largura, altura);

            for(int i = 0; i < 4; i++)
                nos[i] = nullptr;
        }

        ~QuadTree(){
            limpar();
            for(int i = 0; i < 4; i++)
                if(nos[i]!= nullptr){
                    delete nos[i];
                    nos[i] = nullptr;
                }
        }

        void inserir(Entidade* entidade);
        void dividir();
        void limpar();
        void recuperar(std::unordered_set<Entidade*>* retorno, Entidade* entidade);
};

void QuadTree::recuperar(std::unordered_set<Entidade*>* retorno, Entidade* entidade){
    if(entidades.size() > 0 && area.intersects(entidade->getShape().getGlobalBounds())){
        for(Entidade* e : entidades){
            retorno->insert(e);
        }
        
        if(nos[0] != nullptr){
            for(int i = 0; i < 4; i++){
                nos[i]->recuperar(retorno, entidade);
            }
        }
    }
}

void QuadTree::dividir(){
    float meiaLargura = largura/2;
    float meiaAltura = altura/2;
    nos[0] = new QuadTree(posX, posY, meiaLargura, meiaAltura, nivel+1);
    nos[1] = new QuadTree(posX + meiaLargura, posY, meiaLargura, meiaAltura, nivel+1);
    nos[2] = new QuadTree(posX, posY + meiaAltura, meiaLargura, meiaAltura, nivel+1);
    nos[3] = new QuadTree(posX + meiaLargura, posY + meiaAltura, meiaLargura, meiaAltura, nivel+1);
}

void QuadTree::limpar(){
    entidades.clear();

    for (int i = 0; i < 4; i++){
        if(nos[i] != nullptr){
            nos[i]->limpar();
        }
    }
}

void QuadTree::inserir(Entidade* ent){
    if(entidades.size() < QT_MAX_ENTIDADES){
        entidades.push_back(ent);
        return;
    }
    
    if(nos[0] == nullptr){
        dividir();
    }

    sf::FloatRect shape = ent->getShape().getGlobalBounds();
    for(int i = 0; i < 4; i++){
        if(shape.intersects(nos[i]->area)){
            nos[i]->inserir(ent);
            return;
        }
    }

    entidades.push_back(ent);
}