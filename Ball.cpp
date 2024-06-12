#include "Ball.h"
#include "MyMath.h"

Ball::Ball(float mass, float radius, sf::Vector2f initialPosition, sf::Vector2f initialVelocity, std::size_t pointCount)
    : sf::CircleShape(radius, pointCount) {
    	previousVelocity = initialVelocity;
    	velocity = initialVelocity;
    	this -> setPosition(initialPosition);
    	this->mass = mass;
}

void Ball::updateState(float elapsedTime, sf::Vector2f gField, int windowWidth, int windowHeight){
	previousVelocity.x = velocity.x;
	previousVelocity.y = velocity.y;
	velocity.x += gField.x * elapsedTime;
	velocity.y += gField.y * elapsedTime;

	sf::Vector2f position = this->getPosition();
	float radius = this->getRadius();

	sf::Vector2f destinedPosition = position + ((velocity + previousVelocity) / 2.f * elapsedTime);
	sf::Vector2f velocityAtCollision = previousVelocity;
	float timeOfCollision;

	if (destinedPosition.x <= 0 && destinedPosition.y <= 0){
		//top left
	}else if(destinedPosition.x <= 0 && destinedPosition.y + 2*radius >= windowHeight){
		//bottom left
	}else if(destinedPosition.x + 2*radius >= windowWidth && destinedPosition.y <= 0){
		//top right
	}else if(destinedPosition.x + 2*radius >= windowWidth && destinedPosition.y + 2*radius >= windowHeight){
		//bottom right
	}else if (destinedPosition.x <= 0){
		//only left bound
		destinedPosition.y = destinedPosition.y;
		destinedPosition.x = -(destinedPosition.x);
		timeOfCollision =  -(position.x) / ((velocity.x + previousVelocity.x) / 2.f);
		velocityAtCollision.x += gField.x * timeOfCollision;
		velocity.x = -(velocityAtCollision.x - (velocity.x - velocityAtCollision.x));
	}else if (destinedPosition.x + 2*radius >= windowWidth){
		//only right bound
		destinedPosition.y = destinedPosition.y;
		destinedPosition.x = windowWidth - (destinedPosition.x + 2*radius - windowWidth) - 2*radius;
		timeOfCollision = (windowWidth - (position.x + 2*radius)) / ((velocity.x + previousVelocity.x) / 2.f);
		velocityAtCollision.x += gField.x * timeOfCollision;
		velocity.x = -(velocityAtCollision.x - (velocity.x - velocityAtCollision.x));
	}else if (destinedPosition.y <= 0){
		//only upper bound
		destinedPosition.x = destinedPosition.x;
		destinedPosition.y = -(destinedPosition.y);
		timeOfCollision =  -(position.y) / ((velocity.y + previousVelocity.y) / 2.f);
		velocityAtCollision.y += gField.y * timeOfCollision;
		velocity.y = -(velocityAtCollision.y - (velocity.y - velocityAtCollision.y));
	}else if (destinedPosition.y + 2*radius >= windowHeight){
		//only lower bound
		//std::cout << "previousVelocity.y : " << previousVelocity.y <<std::endl;
		//std::cout << "velocity.y : " << velocity.y <<std::endl;
		//std::cout << "position.y : " << position.y <<std::endl;
		//std::cout << "destinedPosition.y : " << destinedPosition.y <<std::endl;
		destinedPosition.x = destinedPosition.x;
		destinedPosition.y = windowHeight - (destinedPosition.y + 2*radius - windowHeight) - 2*radius;
		timeOfCollision = (windowHeight - (position.y + 2*radius)) / ((velocity.y + previousVelocity.y) / 2.f);
		velocityAtCollision.y += gField.y * timeOfCollision;
		velocity.y = -(velocityAtCollision.y - (velocity.y - velocityAtCollision.y));
		//previousVelocity.y = 123123123123123123;
		//std::cout << "elapsedTime : " << elapsedTime <<std::endl;
		//std::cout << "timeOfCollision : " <<timeOfCollision <<std::endl;
		//std::cout << "velocityAtCollision.y : " << velocityAtCollision.y <<std::endl;
		//std::cout << "velocity.y : " << velocity.y <<std::endl;
	}

	this->setPosition(destinedPosition);
	//checkCollision(windowWidth, windowHeight);
}

void Ball::checkCollision(int windowWidth, int windowHeight){
	sf::Vector2f position = this->getPosition();
	float radius = this->getRadius();

	if (position.x <= 0){
		//position.x = 0;
		velocity.x = -velocity.x;
		previousVelocity.x = -previousVelocity.x;
	}else if (position.x + 2*radius >= windowWidth){
		//position.x = windowWidth - 2*radius;
		velocity.x = -velocity.x;
		previousVelocity.x = -previousVelocity.x;
	}
	if (position.y <= 0){
		//position.y = 0;
		velocity.y = -velocity.y;
		previousVelocity.y = -previousVelocity.y;
	}else if (position.y + 2*radius >= windowHeight){
		//position.y = windowHeight - 2*radius;
		velocity.y = -velocity.y;
		previousVelocity.y = -previousVelocity.y;
	}

	//this->setPosition(position);
	//the position update in this function messes up with the
	//conservation of energy so I commented it out for now
	//however without it high velocities are a problem.
	//objects can glitch into walls.
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

sf::Vector2f Ball::getCenterCoordinates(){
	float radius = getRadius();
	return getPosition() + sf::Vector2f(radius, radius);
}
