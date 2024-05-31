#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>

class Plataforma;
class Jogador;

class Entidade{
    protected:      
        sf::RectangleShape shape;
        int tipo;
    
    public:
        Entidade(sf::Vector2f posicao, sf::Vector2f tamanho){
            shape.setPosition(posicao);
            shape.setSize(tamanho);
            shape.setFillColor(sf::Color::Transparent);
            tipo = 0;
            
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


        virtual void execute(){}
};

