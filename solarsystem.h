#pragma once

#include <string>
#include <vector>
#include "color.h"
#include <cmath>
#include <omp.h>

extern double GRAVITATIONAL_CONSTANT;

class Planet {
public:
	Planet(const std::string& name, double mass, double radius, double distance, Color color)
		: name(name), mass(mass), radius(radius), distance(distance), pos_x(distance), pos_y(0), velocity_x(0), velocity_y(0), color(color), rotations(0) {}
	std::string getName() const;
	double getMass() const;
	double getRadius() const;
	double getDistance() const;
	double getPosX() const;
	double getPosY() const;
	double getVelX() const;
	double getVelY() const;
	Color getColor() const;
	int getRotations() const;

	void initializeVelocity(const Planet&);
	double getDistance(const Planet&) const;
	void resetGravityForces();
	void addGravityForces(const Planet&);
	void update(const double);

private:
	std::string name;
	double mass;
	double radius;
	double distance;
	double pos_x;
	double pos_y;
	double velocity_x;
	double velocity_y;
	double force_x;
	double force_y;
	int rotations;
	Color color;
};

class SolarSystem {
public:
	SolarSystem(const std::string & name) : name(name) {}

	std::vector<Planet> getPlanets() const;
	void addPlanet(const Planet&);
	void simulate(const double);

private:
	std::string name;
	std::vector<Planet> planets;
};
