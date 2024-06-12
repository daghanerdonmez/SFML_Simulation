#include "MyMath.h"
#include <math.h>
#include "Ball.h"

float dotProduct(sf::Vector2f v1, sf::Vector2f v2){
	return v1.x * v2.x + v1.y * v2.y;
}

//checks if the given Ball is overlapping with any of the given Balls in the vector
int overlap(Ball ball, std::vector<Ball> balls){
	for (std::size_t i = 0; i < balls.size(); i++){
		Ball otherBall = balls[i];
		if (euclidianDistance(ball.getCenterCoordinates(), otherBall.getCenterCoordinates())< (ball.getRadius() + otherBall.getRadius()))
		{
			return i; //return the index of other collided ball
		}
	}

	return -1; //no collision
}

float euclidianDistance(sf::Vector2f p1, sf::Vector2f p2){
	return sqrt(pow((p1.x + p2.x), 2) + pow((p1.y + p2.y), 2));
}

bool outOfBounds(Ball ball, int windowWidth, int windowHeight){
	sf::Vector2f ballPosition = ball.getPosition();
	float radius = ball.getRadius();

	if (ballPosition.x <= 0 || ballPosition.x + 2*radius >= windowWidth || ballPosition.y <= 0 || ballPosition.y + 2*radius >= windowHeight)
	{
		return true;
	}else return false;
}

float totalEnergy(std::vector<Ball> allBalls, int windowWidth, int windowHeight, sf::Vector2f gField){
	float E_tot = 0;
	for (std::size_t i = 0; i < allBalls.size(); i++){
		E_tot += allBalls[i].mechanicalEnergy(windowWidth, windowHeight, gField);
	}
	return E_tot;
}