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

Vector2D Planet::getPos() const { 
	return pos; 
}

Vector2D Planet::getVel() const { 
	return velocity;
}

Color Planet::getColor() const {
	return color;
}

int Planet::getRotations() const{
	return rotations;
}

double Planet::getDistance(const Planet& other) const {
	Vector2D delta = other.getPos() - pos;
    return delta.norm();
}

void Planet::initializeVelocity(const Planet& other) {
	double velocity_abs = sqrt(( GRAVITATIONAL_CONSTANT * other.getMass()) / other.getDistance(*this));
	double angle = atan2(pos.y, pos.x);
	velocity = velocity_abs * Vector2D(sin(angle), cos(angle));
}

void Planet::resetGravityForces(){
	force.rst();
}

void Planet::addGravityForces(const Planet& other) {
	double distance = this->getDistance(other);
	double force_abs = GRAVITATIONAL_CONSTANT * mass * other.getMass() / (distance*distance); //undirected force
	force += ((force_abs * (other.getPos() - pos)) / distance);
}

void Planet::update(const double inc_step) {
	double old_pos_x = pos.x;
	velocity += (force * inc_step) / mass;
	pos += velocity * inc_step;
	if(old_pos_x < 0 && pos.x >= 0){
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