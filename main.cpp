#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include "Ball.h"

const int width = 400;
const int height = 400;


int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "");

    sf::Vector2f gravity(0.f, 100);

    Ball ball(1.f, 50.f);
    ball.setFillColor(sf::Color::Blue);
    ball.setPosition(50,50);

    sf::Clock clock;

    //window.setFramerateLimit(500);

    void updateScene(float elapsedTime);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float currentTime = clock.restart().asSeconds();
        float fps = 1.0f / currentTime;
        window.setTitle(std::to_string(fps));
        //std::cout << "FPS: " << fps << std::endl;

        ball.updateState(currentTime, gravity, width, height);
        //std::cout << "KE: " << ball.kineticEnergy() << std::endl;
        std::cout << "E = " << ball.mechanicalEnergy(width, height, gravity) << std::endl;

        window.clear();
        window.draw(ball);
        window.display();
    }

    return 0;
}

