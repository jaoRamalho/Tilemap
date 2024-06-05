#pragma once
#include <vector>
#include <unordered_set>

#define QT_MAX_ENTIDADES 3 // quantidade maxima de entidades que um no pode ter
#define QT_MAX_NIVEIS 10 // quantidade maxima de niveis que a quadtree pode ter (ALTURA DA ARVORE) (obbs: n está limitado ainda)

class Entidade;

std::vector<sf::RectangleShape> shapes;

class QuadTree{
    private:
        int nivel;
        std::unordered_set<Entidade*> entidades;
        QuadTree* nos[4];
        float posX, posY, largura, altura;
        sf::FloatRect area;

    public:
        QuadTree(float posX, float posY, float largura, float altura, int nivel = 0) : posX(posX), posY(posY), 
        largura(largura), altura(altura), nivel(nivel), area(posX, posY, largura, altura){
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

        void inserir(Entidade* entidade, sf::FloatRect area);
        void dividir();
        void limpar();
        void recuperar(std::unordered_set<Entidade*>* retorno, sf::FloatRect area);
        void atualizar(Entidade* entidade, sf::FloatRect area);
        void remover(Entidade* entidade);

};

void QuadTree::atualizar(Entidade* entidade, sf::FloatRect area){
    if (this->area.intersects(area)) {
        // Se a entidade está no mesmo quadrante, não precisamos fazer nada
        return;
    }

    // Se a entidade se moveu para um quadrante diferente, precisamos removê-la e reinseri-la
    remover(entidade);
    inserir(entidade, area);
}

void QuadTree::remover(Entidade* entidade){
    entidades.erase(entidade);

    if(nos[0] != nullptr){
        for(int i = 0; i < 4; i++){
            nos[i]->remover(entidade);
        }
    }
}


void QuadTree::recuperar(std::unordered_set<Entidade*>* retorno, sf::FloatRect area){
    if(this->area.intersects(area)){
        for(Entidade* e : entidades){
            retorno->insert(e);
        }
        
        if(nos[0] != nullptr){
            for(int i = 0; i < 4; i++){
                nos[i]->recuperar(retorno, area);
            }
        }
    }
}

void QuadTree::dividir(){
    float meiaLargura = largura/2;
    float meiaAltura = altura/2;
    nos[0] = new QuadTree(posX, posY, meiaLargura, meiaAltura, nivel+1);
    
    sf::RectangleShape shape1(sf::Vector2f(meiaLargura, meiaAltura));
    //shape1.setPosition(posX, posY);
    //shape1.setFillColor(sf::Color(20*(nivel+1), 0, 0, 80));
    //shapes.push_back(shape1);
    
    nos[1] = new QuadTree(posX + meiaLargura, posY, meiaLargura, meiaAltura, nivel+1);

    sf::RectangleShape shape2(sf::Vector2f(meiaLargura, meiaAltura));
    //shape2.setPosition(posX + meiaLargura, posY);
    //shape2.setFillColor(sf::Color(20*(nivel+1), 0, 0, 80));
    //shapes.push_back(shape2);

    nos[2] = new QuadTree(posX, posY + meiaAltura, meiaLargura, meiaAltura, nivel+1);

    sf::RectangleShape shape3(sf::Vector2f(meiaLargura, meiaAltura));
    //shape3.setPosition(posX, posY + meiaAltura);
    //shape3.setFillColor(sf::Color(20*(nivel+1), 0, 0, 80));
    //shapes.push_back(shape3);

    nos[3] = new QuadTree(posX + meiaLargura, posY + meiaAltura, meiaLargura, meiaAltura, nivel+1);

    sf::RectangleShape shape4(sf::Vector2f(meiaLargura, meiaAltura));
    //shape4.setPosition(posX + meiaLargura, posY + meiaAltura);
    //shape4.setFillColor(sf::Color(20*(nivel+1), 0, 0, 80));
    //shapes.push_back(shape4);

}

void QuadTree::limpar(){
    entidades.clear();

    if(nos[0] != nullptr)
        for (int i = 0; i < 4; i++){
            nos[i]->limpar();
        }
}

void QuadTree::inserir(Entidade* entidade, sf::FloatRect area) {
    if (nos[0] != nullptr) {
        for(int i = 0; i < 4; i++) {
            if (nos[i]->area.intersects(area)) {
                nos[i]->inserir(entidade, area);
            }
        }
    }

    if (entidades.size() < QT_MAX_ENTIDADES || nivel == QT_MAX_NIVEIS) {
        entidades.insert(entidade);
    } else {
        if (nos[0] == nullptr) {
            dividir();
        }

        for(int i = 0; i < 4; i++) {
            if (nos[i]->area.intersects(area)) {
                nos[i]->inserir(entidade, area);
            }
        }
    }
}