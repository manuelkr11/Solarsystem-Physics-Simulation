#pragma once

#include <string>
#include <vector>

class Planet {
public:
	Planet(const std::string& name, double mass, double radius, double distance)
		: name(name), mass(mass), radius(radius), distance(distance), pos_x(distance), pos_y(0), velocity_x(0), velocity_y(0) {} //TODO velocity
	std::string getName() const;
	double getMass() const;
	double getRadius() const;
	double getDistance() const;
	double getPosX() const;
	double getPosY() const;
	double getVelX() const;
	double getVelY() const;

	double getDistanceX(const Planet&);
	double getDistanceY(const Planet&);
	double calculateGravityForceX(const Planet&);
	double calculateGravityForceY(const Planet&);
	void update(const double, const double);

private:
	std::string name;
	double mass;
	double radius;
	double distance;
	double pos_x;
	double pos_y;
	double velocity_x;
	double velocity_y;
	static const int GRAVITATIONAL_CONSTANT = 100; //TODO
};

class SolarSystem {
public:
	SolarSystem(const std::string & name) : name(name) {}

	std::vector<Planet> getPlanets() const;
	void addPlanet(const Planet&);
	void simulate();

private:
	std::string name;
	std::vector<Planet> planets;
};
