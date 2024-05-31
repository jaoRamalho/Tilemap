#include <iostream>
#include "Fase.hpp"

int main(){
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!", sf::Style::Fullscreen);
    window.setFramerateLimit(25);
    Fase fase("tiled/mapa.tmj", &window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {   
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
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