#include "Ball.h"
#include "MyMath.h"

Ball::Ball(float mass, float radius, std::size_t pointCount) 
    : sf::CircleShape(radius, pointCount) {
    	velocity.x = 0.f;
    	velocity.y = 0.f;
    	this->mass = mass;
}

void Ball::updateState(float elapsedTime, sf::Vector2f gField, int windowWidth, int windowHeight){
	velocity.x += gField.x * elapsedTime;
	velocity.y += gField.y * elapsedTime;

	this->setPosition(this->getPosition() + velocity * elapsedTime);
	checkCollision(windowWidth, windowHeight);
}

void Ball::checkCollision(int windowWidth, int windowHeight){
	sf::Vector2f position = this->getPosition();
	float radius = this->getRadius();

	if (position.x <= 0){
		position.x = 0;
		velocity.x = -velocity.x;
	}else if (position.x + 2*radius >= windowWidth){
		position.x = windowWidth - 2*radius;
		velocity.x = -velocity.x;
	}
	if (position.y <= 0){
		position.y = 0;
		velocity.y = -velocity.y;
	}else if (position.y + 2*radius >= windowHeight){
		position.y = windowHeight - 2*radius;
		velocity.y = -velocity.y;
	}
}

float Ball::kineticEnergy(){
	return mass * dotProduct(velocity, velocity) / 2;
}

float Ball::gravitationalPotentialEnergy(int windowWidth, int windowHeight, sf::Vector2f gField){
	sf::Vector2f position = this->getPosition();
	return mass * (gField.x * (windowWidth - position.x) + gField.y * (windowHeight - position.y));
}

float Ball::mechanicalEnergy(int windowWidth, int windowHeight, sf::Vector2f gField){
	return this->kineticEnergy() + this->gravitationalPotentialEnergy(windowWidth, windowHeight, gField);
}
