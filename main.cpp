#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include "solarsystem.h"
#include "vec2d.h"
#include <cstring>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;
const int SOLARSYSTEM_WIDTH = 10000;

void SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if (dx*dx + dy*dy <= radius*radius) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius) {
    for (int angle = 0; angle < 360; angle++) {
        double radian = angle * 3.14159265 / 180.0;
        int dx = static_cast<int>(radius * cos(radian));
        int dy = static_cast<int>(radius * sin(radian));
        SDL_RenderDrawPoint(renderer, x + dx, y + dy);
    }
}

void initialize_our_ss(SolarSystem &solarSystem, bool include_moon) {
    Color color(255, 255, 255);

    Planet sun("sun", 333000, 696342, 0, color);
    solarSystem.addPlanet(sun);

    color.set(141, 153, 147);
    Planet mercury("mercury", 0.055, 2440, 63.81, color);
    mercury.initializeVelocity(sun);
    solarSystem.addPlanet(mercury);

    color.set(232, 193, 130);
    Planet venus("venus", 0.815, 6052, 107.59, color);
    venus.initializeVelocity(sun);
    solarSystem.addPlanet(venus);

    color.set(99, 175, 255);
    Planet earth("earth", 1, 6371, 151.48, color);
    earth.initializeVelocity(sun);
    solarSystem.addPlanet(earth);

	if(include_moon){
		color.set(141, 153, 147);
    	Planet moon("moon", 0.0123, 1740, 151.88, color);
    	moon.initializeVelocity(earth, include_moon);
    	solarSystem.addPlanet(moon);
	}

    color.set(222, 102, 69);
    Planet mars("mars", 0.107, 3390, 248.84, color);
    mars.initializeVelocity(sun);
    solarSystem.addPlanet(mars);

    color.set(237, 210, 159);
    Planet jupiter("jupiter", 317.8, 69911, 755.91, color);
    jupiter.initializeVelocity(sun);
    solarSystem.addPlanet(jupiter);

    color.set(235, 227, 127);
    Planet saturn("saturn", 95.16, 58232, 1487.8, color);
    saturn.initializeVelocity(sun);
    solarSystem.addPlanet(saturn);

    color.set(199, 252, 249);
    Planet uranus("uranus", 14.54, 25362, 2954.6, color);
    uranus.initializeVelocity(sun);
    solarSystem.addPlanet(uranus);

    color.set(100, 180, 245);
    Planet neptune("neptune", 17.15, 24622, 4475.5, color); 
    neptune.initializeVelocity(sun);
    solarSystem.addPlanet(neptune);
}

int main( int argc, char *argv[] ) {

	bool include_moon = false;
	for (int i = 1; i < argc; i++) {
        if (std::strcmp(argv[i], "--moon") == 0) {
            std::cout << "The --moon argument was used." << std::endl;
            include_moon = true;
            break;
        }
    }

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_Window* window = SDL_CreateWindow("Solar System Physics Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	SolarSystem solarSystem("Earth's Solar System");
	initialize_our_ss(solarSystem, include_moon);
	int last_planet = solarSystem.getPlanets().size() - 1;

	bool quit = false;
	SDL_Event e;

	bool userPressedZoomInKey = false;
	bool userPressedZoomOutKey = false;
	bool userPressedSpeedUpKey = false;
	bool userPressedSpeedDownKey = false;
	bool userPressedEarthKey = false;

	double zoomFactor = 1;
	double step_speed = 0.0001;
	bool earth_focus = false;

	int refresh_rate = 500;
	int refresh_count = 0;

	while (!quit) {
		refresh_count++;

		while (SDL_PollEvent(&e)) {
        	if (e.type == SDL_QUIT) {
            	quit = true;
        	} else if (e.type == SDL_KEYDOWN) {
            	if (e.key.keysym.sym == SDLK_m) {
                	userPressedZoomInKey = true;
            	} else if (e.key.keysym.sym == SDLK_n) {
                	userPressedZoomOutKey = true;
            	} else if (e.key.keysym.sym == SDLK_k) {
                	userPressedSpeedUpKey = true;
            	} else if (e.key.keysym.sym == SDLK_j) {
                	userPressedSpeedDownKey = true;
            	} else if (e.key.keysym.sym == SDLK_h) {
                	userPressedEarthKey = true;
            	} else if (e.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
				}
			}
		}
		if (userPressedZoomInKey) {
    		zoomFactor += 0.1;
    		userPressedZoomInKey = false;
		}
		if (userPressedZoomOutKey) {
			zoomFactor -= 0.1;
			userPressedZoomOutKey = false;
		}
		if (userPressedSpeedUpKey) {
			step_speed = std::max(step_speed * 1.3, 0.001);
			userPressedSpeedUpKey = false;
		}
		if (userPressedSpeedDownKey) {
			step_speed = std::min(step_speed /= 1.3, 0.0000001);
			userPressedSpeedDownKey = false;
		}
		if (userPressedEarthKey) {
			if(earth_focus){
				earth_focus = false;
				zoomFactor = 1;
			}
			else{
				earth_focus = true;
				zoomFactor = 1000;
			}
			userPressedEarthKey = false;
		}
		zoomFactor = std::max(0.1, zoomFactor);

		if(refresh_count >= refresh_rate){
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			Vector2D earth_pos;
			if(earth_focus){
				for (const Planet& planet : solarSystem.getPlanets()) {
					if(planet.getName() == "earth"){
						earth_pos = ((planet.getPos() * SCREEN_WIDTH * 0.9) / SOLARSYSTEM_WIDTH * zoomFactor);
					}
				}
			}

			for (const Planet& planet : solarSystem.getPlanets()) {

				Vector2D pos = (((planet.getPos() * SCREEN_WIDTH * 0.9) / SOLARSYSTEM_WIDTH) * zoomFactor) + (Vector2D(SCREEN_WIDTH, SCREEN_HEIGHT) / 2);
				pos -= earth_pos;

				int radius;
				if(planet.getName() == "sun"){
					radius = std::max(1, static_cast<int>(planet.getRadius() / 150000 * zoomFactor));
				}
				else{
					radius = std::max(1, static_cast<int>(planet.getRadius() / 7000 * zoomFactor));
				}
				if(earth_focus){
					radius = radius / 50.;
				}

				int orbit_radius = ((planet.getDistance() * SCREEN_WIDTH * 0.9) / SOLARSYSTEM_WIDTH * zoomFactor);

				SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
				SDL_RenderDrawCircle(renderer, (SCREEN_WIDTH/2)-earth_pos.x, (SCREEN_HEIGHT/2)-earth_pos.y, orbit_radius);

				SDL_SetRenderDrawColor(renderer, planet.getColor().r, planet.getColor().g, planet.getColor().b, 255);
				SDL_RenderFillCircle(renderer, static_cast<int>(pos.x), static_cast<int>(pos.y), radius);
			}

			SDL_RenderPresent(renderer);

			refresh_count = 0;
		}

		solarSystem.simulate(step_speed);

	}

	std::ofstream outputFile("results.txt");
	if (!outputFile.is_open()) {
		std::cerr << "Error opening the file." << std::endl;
		return 1;
	}

	float earth_rot = 0.;
	for(const Planet& planet : solarSystem.getPlanets()){
		if(planet.getName() == "earth"){
			earth_rot = std::atan2(planet.getPos().y, planet.getPos().x);
    		earth_rot = earth_rot / (2 * M_PI);
   			if (earth_rot < 0) {
    			earth_rot += 1;
    		}
			earth_rot += static_cast<float>(planet.getRotations());
		}
	}

	for(const Planet& planet : solarSystem.getPlanets()){
		if(planet.getName() != "sun" && planet.getName() != "moon"){
			double rotations = std::atan2(planet.getPos().y, planet.getPos().x);
			
			rotations = rotations / (2 * M_PI);
			if (rotations < 0) {
				rotations += 1;
			}
			rotations += static_cast<float>(planet.getRotations());
			outputFile << planet.getName() << ": " << earth_rot / rotations << std::endl;
		}
	}

	outputFile.close();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0; 
	
}