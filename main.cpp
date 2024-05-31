#include <iostream>
#include "Fase.hpp"

int main(){
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    window.setFramerateLimit(25);
    Fase fase("tiled/mapa.tmj", &window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        fase.executar();
        fase.desenhar();
        window.display();
    }
    return 0;
}