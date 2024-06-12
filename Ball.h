#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Ball : public sf::CircleShape {

private:
	float mass;
	sf::Vector2f previousVelocity;
	sf::Vector2f velocity;

public:
	Ball(float mass, float radius = 0, sf::Vector2f initialPosition = sf::Vector2f(100.f, 100.f), sf::Vector2f initialVelocity = sf::Vector2f(0.f, 0.f), std::size_t pointCount = 30);
	void updateState(float elapsedTime, sf::Vector2f gField, int windowWidth, int windowHeight);
	void checkCollision(int windowWidth, int windowHeight);
	float kineticEnergy();
	float gravitationalPotentialEnergy(int windowWidth, int windowHeight, sf::Vector2f gField);
	float mechanicalEnergy(int windowWidth, int windowHeight, sf::Vector2f gField);
	sf::Vector2f getCenterCoordinates();
};

#endif