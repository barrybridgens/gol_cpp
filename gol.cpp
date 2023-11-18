#include <SDL2/SDL.h>

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	auto window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
	auto renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event e;

	SDL_Rect rect{500, 500, 10, 10};
	
	bool running = true;

	while(running)
	{
		// Check input
		//
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT) { running = false; }
		}

		// Stuff!
		//

		// Clear window
		//
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Draw
		//
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		//SDL_RenderFillRect(renderer, &rect);
		SDL_RenderDrawRect(renderer, &rect);
		SDL_RenderDrawLine(renderer, 400, 400, 450, 450);

		// Display
		//
		SDL_RenderPresent(renderer);
		SDL_Delay(25);
	}
}
