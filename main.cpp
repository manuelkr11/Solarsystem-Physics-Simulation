#include <iostream>
#include <SDL2/SDL.h>
#include "solarsystem.h"

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;
const int SOLARSYSTEM_WIDTH = 10000; //TODO

void SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // Horizontaler Abstand vom Mittelpunkt
            int dy = radius - h; // Vertikaler Abstand vom Mittelpunkt
            if (dx*dx + dy*dy <= radius*radius) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

int main( int argc, char *argv[] ) {
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
	Color color(255, 255, 255);
	Planet sun("Sun", 333000, 696342, 0, color);
	solarSystem.addPlanet(sun);

	color.set(255,0,0);
	Planet mercury("mercury", 0.055, 2440, 63.81, color);
	mercury.initializeVelocity(sun);
	solarSystem.addPlanet(mercury);

	color.set(255,0,0);
	Planet venus("venus", 0.815, 6052, 107.59, color);
	venus.initializeVelocity(sun);
	solarSystem.addPlanet(venus);

	color.set(255,0,0);
	Planet earth("earth", 1, 6371, 151.48, color);
	earth.initializeVelocity(sun);
	solarSystem.addPlanet(earth);

	color.set(255,0,0);
	Planet mars("mars", 0.107, 3390, 248.84, color);
	mars.initializeVelocity(sun);
	solarSystem.addPlanet(mars);

	color.set(255,0,0);
	Planet jupiter("jupiter", 317.8, 69911, 755.91, color);
	jupiter.initializeVelocity(sun);
	solarSystem.addPlanet(jupiter);

	color.set(255,0,0);
	Planet saturn("saturn", 95.16, 58232, 1487.8, color);
	saturn.initializeVelocity(sun);
	solarSystem.addPlanet(saturn);

	color.set(0,0,255);
	Planet uranus("uranus", 14.54, 25362, 2954.6, color);
	uranus.initializeVelocity(sun);
	solarSystem.addPlanet(uranus);

	color.set(0,255,0);
	Planet neptune("neptune", 17.15, 24622, 4475.5, color);	
	neptune.initializeVelocity(sun);
	solarSystem.addPlanet(neptune);

	bool quit = false;
	SDL_Event e;

	bool userPressedZoomInKey = false;
	bool userPressedZoomOutKey = false;
	double zoomFactor = 1;

	while (!quit) {
		while (SDL_PollEvent(&e)) {
        	if (e.type == SDL_QUIT) {
            	quit = true;
        	} else if (e.type == SDL_KEYDOWN) {
            	if (e.key.keysym.sym == SDLK_n) {
                	userPressedZoomInKey = true;
            	} else if (e.key.keysym.sym == SDLK_m) {
                	userPressedZoomOutKey = true;
            	} else if (e.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		if (userPressedZoomInKey) {
    		zoomFactor += 0.1;
    		userPressedZoomInKey = false;
		}
		if (userPressedZoomOutKey) {
			zoomFactor -= 0.1;
			userPressedZoomOutKey = false;
		}
		zoomFactor = std::max(0.1, zoomFactor);

		for (const Planet& planet : solarSystem.getPlanets()) {
			double x = ((planet.getPosX() * SCREEN_WIDTH * 0.9) / SOLARSYSTEM_WIDTH * zoomFactor) + SCREEN_WIDTH / 2 ; //TODO
			double y = ((planet.getPosY() * SCREEN_WIDTH * 0.9) / SOLARSYSTEM_WIDTH * zoomFactor) + SCREEN_HEIGHT / 2; //TODO

			int radius;
			if(planet.getName() == "Sun"){
				radius = std::max(1, static_cast<int>(planet.getRadius() / 150000 * zoomFactor));
			}
			else{
				radius = std::max(1, static_cast<int>(planet.getRadius() / 5000 * zoomFactor));
			}
			
			int r = planet.getColor().r;
			int g = planet.getColor().g;
			int b = planet.getColor().b;


			SDL_SetRenderDrawColor(renderer, r, g, b, 255);
			SDL_RenderFillCircle(renderer, static_cast<int>(x), static_cast<int>(y), radius);
		}

		SDL_RenderPresent(renderer);

		solarSystem.simulate(0.001);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0; 

}