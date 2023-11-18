// Game of Life
//
// by Barry Bridgens
//

#include <SDL2/SDL.h>

#include "gol.h"


// Draw Grid
//
void draw_grid(SDL_Renderer * r)
{
  int row, col;
  SDL_Rect rect;

  rect.w = CELL_SIZE;
  rect.h = CELL_SIZE;
  SDL_SetRenderDrawColor(r, 150, 150, 150, 255);
  
  for (row=0; row<TOTAL_ROWS_COLS; row++)
  {
    for (col=0; col<TOTAL_ROWS_COLS; col++)
    {
      rect.x = col * CELL_SIZE;
      rect.y = row * CELL_SIZE;
      //SDL_RenderFillRect(renderer, &rect);
      SDL_RenderDrawRect(r, &rect);
    }
  }    
}
  

// Main
//
int main()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  auto window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SC_WIDTH_HEIGHT, SC_WIDTH_HEIGHT, 0);
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
	  if (e.type == SDL_KEYDOWN)
	    {
	      if (e.key.keysym.sym == SDLK_q) { running = false; }
	    }
	}

      // Stuff!
      //

      // Clear window
      //
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);

      // Draw
      //
      draw_grid(renderer);

      // Display
      //
      SDL_RenderPresent(renderer);
      SDL_Delay(25);
    }
}
