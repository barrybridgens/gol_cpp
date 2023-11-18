// Game of Life
//
// by Barry Bridgens
//

#include <SDL2/SDL.h>
#include <unistd.h>

#include "gol.h"


// Initialise Cells
//
void init_cells()
{
  int row, col;
  
  for (row=0; row<TOTAL_ROWS_COLS; row++)
  {
    for (col=0; col<TOTAL_ROWS_COLS; col++)
    {
      cells[row][col] = DEAD;
    }
  }
  std::copy(&cells[0][0], &cells[0][0]+TOTAL_ROWS_COLS*TOTAL_ROWS_COLS, &new_cells[0][0]);
}

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

// Draw Cells
//
void draw_cells(SDL_Renderer * r)
{
  int row, col;
  SDL_Rect rect;

  rect.w = CELL_SIZE;
  rect.h = CELL_SIZE;
  SDL_SetRenderDrawColor(r, 10, 200, 10, 255);
  
  for (row=0; row<TOTAL_ROWS_COLS; row++)
  {
    for (col=0; col<TOTAL_ROWS_COLS; col++)
    {
      if (cells[row][col] == ALIVE)
      {
	rect.x = col * CELL_SIZE;
	rect.y = row * CELL_SIZE;
	SDL_RenderFillRect(r, &rect);
      }
    }
  }    
}

// Clear Cells
//
void clear_cells()
{
  int row, col;
  
  for (row=0; row<TOTAL_ROWS_COLS; row++)
  {
    for (col=0; col<TOTAL_ROWS_COLS; col++)
    {
      cells[row][col] = DEAD;
    }
  }
  std::copy(&cells[0][0], &cells[0][0]+TOTAL_ROWS_COLS*TOTAL_ROWS_COLS, &new_cells[0][0]);
}

// Main
//
int main()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  auto window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SC_WIDTH_HEIGHT, SC_WIDTH_HEIGHT, 0);
  auto renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Event e;

  useconds_t sleep_time = 250;
  bool button = false;
  int row, col;

  init_cells();
  
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
	  if (e.type == SDL_MOUSEBUTTONDOWN) { button = true; }
	  if (e.type == SDL_MOUSEBUTTONUP) { button = false; }
	  if (e.type == SDL_MOUSEMOTION)
	  {
	    col = e.motion.x / CELL_SIZE;
	    row = e.motion.y / CELL_SIZE;
            if ((button) && (cells[row][col] == DEAD)) { cells[row][col] = ALIVE; }
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

      draw_cells(renderer);

      usleep(sleep_time);

      // Display
      //
      SDL_RenderPresent(renderer);
      SDL_Delay(25);
    }
}
