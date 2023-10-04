#include "solarsystem.h"
#include <iostream>

double GRAVITATIONAL_CONSTANT = 100;

Planet::Planet(const std::string& name, double mass, double radius, double distance, Color color)
		: name(name), mass(mass), radius(radius), distance(distance), pos(Vector2D(distance, 0)), 
		velocity(Vector2D(0, 0)), color(color), rotations(0) {}

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

void Planet::initializeVelocity(const Planet& other, bool moon) {
	double velocity_abs = sqrt(( GRAVITATIONAL_CONSTANT * other.getMass()) / other.getDistance(*this));
	double angle = atan2(pos.y-other.getPos().y, pos.x-other.getPos().x);
	velocity = velocity_abs * Vector2D(sin(angle), cos(angle));
	if(moon){
		velocity += other.getVel();
	}
}

void Planet::resetGravityForces(){
	force.rst();
}

void Planet::addGravityForces(const Planet& other) {
	double distance = this->getDistance(other);
	double force_abs = GRAVITATIONAL_CONSTANT * mass * other.getMass() / (distance*distance);
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