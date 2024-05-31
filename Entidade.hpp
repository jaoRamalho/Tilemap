#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>

#define GRAVIDADE 0.735

class Plataforma;
class Jogador;

class Entidade{
    protected:      
        sf::RectangleShape shape;
        float gravidade;
        sf::Vector2f movimento;

        int tipo;
    
    public:
        Entidade(sf::Vector2f posicao, sf::Vector2f tamanho) : gravidade(0), tipo(0){
            shape.setPosition(posicao);
            shape.setSize(tamanho);
            shape.setFillColor(sf::Color::Transparent);
            
        }

        virtual ~Entidade(){}

        const int getTipo() { return tipo; }
       
        void desenhar(sf::RenderWindow* window){ window->draw(shape); }

        void setPosicao(sf::Vector2f posicao){ shape.setPosition(posicao); }
        void setTamanho(sf::Vector2f tamanho){ shape.setSize(tamanho);}
        
        sf::Vector2f getPosicao(){ return shape.getPosition(); }
        sf::Vector2f getTamanho(){ return shape.getSize(); }

        sf::RectangleShape getShape() { return shape; }

        virtual void colidir(Plataforma* plat, sf::FloatRect intersects){}
        virtual void colidir(Jogador* jog, sf::FloatRect intersects){}

        void acelerarGravidade() { if(gravidade <= 15) gravidade += GRAVIDADE; }
        virtual void execute(){}
};

