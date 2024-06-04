#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "nlohmann/json.hpp"
#include "Jogador.hpp"
#include <vector>
#include <fstream>
#include <string>

class Tilemap{
    private:
        nlohmann::json mapa; 
        std::vector<Entidade*>* entidades;
        sf::Texture* textura_mapa;
        QuadTree* q;

    public:
        Tilemap(QuadTree* q) : q(q){}
        ~Tilemap(){}

        void carregarMapa(std::string mapJson);
        Entidade* criarEntidade (sf::Vector2f posicao, sf::Vector2f tamanho, int tipo);
        void criarMapa(std::string caminhoMapa, std::vector<Entidade*>* entidades, sf::Texture* textura_mapa);
        nlohmann::json getMapa(){ return mapa; }
};

void Tilemap::carregarMapa(std::string mapJson) {
    std::ifstream arquivo(mapJson);
    
    if(!arquivo.is_open()){
        std::cerr << "Erro ao abrir o mapa" << std::endl;
        return;
    }

    arquivo >> mapa;
    arquivo.close();
}

void Tilemap::criarMapa(std::string caminhoMapa, std::vector<Entidade*>* entidades, sf::Texture* textura_mapa) {
    carregarMapa(caminhoMapa);  // carrega arquivo json
    this->entidades = entidades;
    
    //.json tenha o mesmo nome do .png e ambos estejam na mesma pasta
    this->textura_mapa = textura_mapa;
    textura_mapa->loadFromFile(caminhoMapa.substr(0, caminhoMapa.find_last_of(".")) + ".png");

    // Pega as informações do mapa
    int sizeTiled = mapa["tilewidth"];
    int width = mapa["width"];
    int height = mapa["height"];
    
    int indice = 0;

    //Loop para criar as entidades 0 = vazio, -1 = jogador e outros valores são entidades diversas
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int tileId = mapa["layers"][0]["data"][indice++];
            if(tileId != 0){
                sf::Vector2f posicao(x * sizeTiled, y * sizeTiled);
                sf::Vector2f tamanho(sizeTiled, sizeTiled);
                entidades->push_back(criarEntidade(posicao, tamanho, tileId));
            }
        }
    }
}

Entidade* Tilemap::criarEntidade(sf::Vector2f posicao, sf::Vector2f tamanho, int tipo) {
    if (tipo == -1) {
        return new Jogador(posicao, tamanho, q);
    }
    else {
        return new Plataforma(posicao, tamanho, q);
    }
}
