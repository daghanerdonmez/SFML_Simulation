#ifndef MYMATH_H
#define MYMATH_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Ball.h"

float dotProduct(sf::Vector2f v1, sf::Vector2f v2);

//checks if the given Ball is overlapping with any of the given Balls in the vector
int overlap(Ball ball, std::vector<Ball> balls);

float euclidianDistance(sf::Vector2f p1, sf::Vector2f p2);

float totalEnergy(std::vector<Ball> allBalls, int windowWidth, int windowHeight, sf::Vector2f gField);

#endif