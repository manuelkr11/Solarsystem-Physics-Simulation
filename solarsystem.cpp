#include "solarsystem.h"
#include <iostream>


double GRAVITATIONAL_CONSTANT = 100;

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

int Planet::getRotations() const{
	return rotations;
}

double Planet::getDistance(const Planet& other) const {
    double dx = other.getPosX() - pos_x;
    double dy = other.getPosY() - pos_y;
	double result =  sqrt((dx * dx) + (dy * dy));
    return result;
}

void Planet::initializeVelocity(const Planet& other) {
	double velocity = sqrt(( GRAVITATIONAL_CONSTANT * other.getMass()) / other.getDistance(*this));
	double angle = atan2(pos_y, pos_x);
	velocity_x = velocity * sin(angle);
    velocity_y = velocity * cos(angle);
}

void Planet::resetGravityForces(){
	force_x = 0.;
	force_y = 0;
}

void Planet::addGravityForces(const Planet& other) {
	double distance = this->getDistance(other);
	double force = GRAVITATIONAL_CONSTANT * mass * other.getMass() / (distance*distance); //undirected force
	force_x += force * ((other.getPosX() - pos_x) / distance);
	force_y += force * ((other.getPosY() - pos_y) / distance);
}

void Planet::update(const double inc_step) {
	double old_pos_x = pos_x;
	velocity_x += (force_x * inc_step) / mass;
	velocity_y += (force_y * inc_step) / mass;
	pos_x = pos_x + inc_step * velocity_x;
	pos_y = pos_y + inc_step * velocity_y;
	if(old_pos_x < 0 && pos_x >= 0){
		rotations++;
	}
}


std::vector<Planet> SolarSystem::getPlanets() const { 
	return planets; 
}

void SolarSystem::addPlanet(const Planet& planet) {
	planets.push_back(planet);
}

void SolarSystem::simulate(const double inc_step) {
	#pragma omp parallel num_threads(4)
	#pragma omp for
	for (Planet& planet : planets) {
		if(planet.getName()!="sun") {
			planet.resetGravityForces();
			for(Planet& other_planet : planets) {
				if(other_planet.getName() != planet.getName()) {
					planet.addGravityForces(other_planet);
				}
			}
		}
	}
	for (Planet& planet : planets) {
		planet.update(inc_step);
	}
}