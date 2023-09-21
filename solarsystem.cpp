#include "solarsystem.h"

std::string Planet::getName() const { 
	return name; 
}

double Planet::getMass() const { 
	return mass; 
}

double Planet::getRadius() const { 
	return radius; 
}

double Planet::getDistance() const { 
	return distance; 
}

double Planet::getPosX() const { 
	return pos_x; 
}

double Planet::getPosY() const { 
	return pos_y; 
}

double Planet::getVelX() const { 
	return velocity_x; 
}

double Planet::getVelY() const { 
	return velocity_y; 
}

double Planet::getDistanceX(const Planet& other) {
	return other.getPosX() - pos_x;
}

double Planet::getDistanceY(const Planet& other) {
	return other.getPosY() - pos_y;
}

double Planet::calculateGravityForceX(const Planet& other) {
	double force = 0.;
	//force = GRAVITATIONAL_CONSTANT * mass * other.getMass() / sqrt(getDistanceX(other) * getDistanceX(other) + getDistanceY(other) * getDistanceY(other)); //TODO sqrt
	return force; //TODO direction!
}

double Planet::calculateGravityForceY(const Planet& other) {
	double force = 0.;
	//force = GRAVITATIONAL_CONSTANT * mass * other.getMass() / sqrt(getDistanceX(other) * getDistanceX(other) + getDistanceY(other) * getDistanceY(other)); //TODO sqrt
	return force; //TODO direction!
}

void Planet::update(double force_x, double force_y) {
	// F(t) = m * dv(t)/dt  ->  dv(t) = (F(t)*dt) / m

}

std::vector<Planet> SolarSystem::getPlanets() const { 
	return planets; 
}

void SolarSystem::addPlanet(const Planet& planet) {
	planets.push_back(planet);
}