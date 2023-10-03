#pragma once

#include <string>
#include <vector>
#include "color.h"
#include <cmath>
#include <omp.h>
#include "vec2d.h"

extern double GRAVITATIONAL_CONSTANT;

class Planet {
public:
	Planet(const std::string& name, double mass, double radius, double distance, Color color)
		: name(name), mass(mass), radius(radius), distance(distance), pos(Vector2D(distance, 0)), velocity(Vector2D(0, 0)), color(color), rotations(0) {}
	std::string getName() const;
	double getMass() const;
	double getRadius() const;
	double getDistance() const;
	Vector2D getPos() const;
	Vector2D getVel() const;
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
	Vector2D pos;
	Vector2D velocity;
	Vector2D force;
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
