#include <iostream>
#include <SDL2/SDL.h>
#include "solarsystem.h"

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 900;
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
	Planet sun("Sun", 333000, 696342, 0);
	Planet mercury("mercury", 0.055, 2440, 63.81);
	Planet venus("venus", 0.815, 6052, 107.59);
	Planet earth("earth", 1, 6371, 151.48);
	Planet mars("mars", 0.107, 3390, 248.84);
	Planet jupiter("jupiter", 317.8, 69911, 755.91);
	Planet saturn("saturn", 95.16, 58232, 1487.8);
	Planet uranus("uranus", 14.54, 25362, 2954.6);
	Planet neptune("neptune", 17.15, 24622, 4475.5);

	solarSystem.addPlanet(sun);
	solarSystem.addPlanet(mercury);
	solarSystem.addPlanet(venus);
	solarSystem.addPlanet(earth);
	solarSystem.addPlanet(mars);
	solarSystem.addPlanet(jupiter);
	solarSystem.addPlanet(saturn);
	solarSystem.addPlanet(uranus);
	solarSystem.addPlanet(neptune);

	bool quit = false;
	SDL_Event e;

	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//solarSystem.simulate();

		for (const Planet& planet : solarSystem.getPlanets()) {
			double x = (planet.getPosX() * SCREEN_WIDTH * 0.9) / SOLARSYSTEM_WIDTH + SCREEN_WIDTH / 2; //TODO
			double y = (planet.getPosY() * SCREEN_WIDTH * 0.9) / SOLARSYSTEM_WIDTH + SCREEN_HEIGHT / 2; //TODO

			int radius;
			if(planet.getName() == "Sun"){
				radius = 1;
			}
			else{
				radius = std::max(1, static_cast<int>(planet.getRadius() / 5000));
			}
			
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderFillCircle(renderer, static_cast<int>(x), static_cast<int>(y), radius);
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0; 

}