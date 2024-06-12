#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include "Ball.h"
#include <stdlib.h>
#include "MyMath.h"

const int width = 700;
const int height = 700;
const int ballNumber = 20;
const int velocityRange = 100;

int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "");

    sf::Vector2f gravity(0.f, 500.f);

    //Ball ball(1.f, 5.f, sf::Vector2f(100.f, 100.f), sf::Vector2f(0.f, 0.f));
    //ball.setFillColor(sf::Color::Blue);

    std::vector<Ball> allBalls;
    allBalls.reserve(ballNumber);

    for (std::size_t i = 0; i < ballNumber; i++){
        Ball newBall(1.f, 5.f, sf::Vector2f(rand() % width, rand() % height), sf::Vector2f(rand() % velocityRange, rand() % velocityRange));
        //Ball newBall(1.f, 5.f, sf::Vector2f(100, 300), sf::Vector2f(0, 0));
        newBall.setFillColor(sf::Color::Green);
        allBalls.push_back(newBall);
    }

    sf::Clock clock;

    window.setFramerateLimit(60);

    //void updateScene(float elapsedTime);

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
        window.setTitle("FPS: " + std::to_string(fps));
        //std::cout << "FPS: " << fps << std::endl;

        for (std::size_t i = 0; i < ballNumber; i++){
           allBalls[i].updateState(currentTime, gravity, width, height);
        }

        //ball.updateState(currentTime, gravity, width, height);
        //std::cout << "KE: " << ball.kineticEnergy() << std::endl;
        std::cout << "E_tot = " << totalEnergy(allBalls, width, height, gravity) << std::endl;

        window.clear();
        for (std::size_t i = 0; i < ballNumber; i++){
            window.draw(allBalls[i]);
        }
        //window.draw(ball);
        window.display();
    }

    return 0;
}

