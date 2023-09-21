#include "solarsystem.h"

double GRAVITATIONAL_CONSTANT = 100.0;

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

Color Planet::getColor() const {
	return color;
}

double Planet::getDistance(const Planet& other) const {
    double dx = other.getPosX() - pos_x;
    double dy = other.getPosY() - pos_y;
    return sqrt(dx * dx + dy * dy);
}

void Planet::initializeVelocity(const Planet& other) {
	velocity_x = 0.;
	velocity_y = sqrt(GRAVITATIONAL_CONSTANT * other.getMass() / this->getDistance(other));
}

void Planet::resetGravityForces(){
	force_x = 0.;
	force_y = 0;
}

void Planet::addGravityForces(const Planet& other) {
	//force = GRAVITATIONAL_CONSTANT * mass * other.getMass() / sqrt(getDistanceX(other) * getDistanceX(other) + getDistanceY(other) * getDistanceY(other)); //TODO sqrt
	//TODO direction!
}

void Planet::update(const double inc_step) {
	//TODO velocity anpassen und Umdrehungen zaehlen
	pos_x = pos_x + inc_step * velocity_x;
	pos_y = pos_y + inc_step * velocity_y;
}


std::vector<Planet> SolarSystem::getPlanets() const { 
	return planets; 
}

void SolarSystem::addPlanet(const Planet& planet) {
	planets.push_back(planet);
}

void SolarSystem::simulate(const double inc_step) {
	for (Planet& planet : planets) {
		planet.update(inc_step);
	}
}