#include <iostream>
#include "Fase.hpp"
#include <vector>
int main(){
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!", sf::Style::Fullscreen);
    //window.setFramerateLimit(25);
    Fase fase("tiled/mapa.tmj", &window);

    sf::Clock clock;
    clock.restart();
    int frames = 0;
    std::vector<int> nf;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {   
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type == sf::Event::Closed)
                window.close();
        }

        frames++;
        if(clock.getElapsedTime().asSeconds() >= 1){
            nf.push_back(frames);
            frames = 0;
            clock.restart();
        }

        window.clear(sf::Color::White);
        fase.executar();
        fase.desenhar();
        window.display();
    }

    int numFramesMedio = 0;
    for(auto f : nf){
        numFramesMedio += f;
    }

    std::cout<< "Média de frames: " << numFramesMedio/nf.size() << std::endl;

    return 0;
}