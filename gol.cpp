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
  bool run = false;
  bool stop = false;
  bool game_running = false;
  int x, y;
  int row, col;
  int generations = 0;
  int neighbours = 0;

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
	if (e.key.keysym.sym == SDLK_r) { run = true; }
	if (e.key.keysym.sym == SDLK_s) { stop = true; }
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

    // Clear window
    //
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw Grid
    //
    draw_grid(renderer);
      
    // Game logic
    //
    if (run)
    {
      game_running = true;
      run = false;
    }
    if (stop)
    {
      game_running = false;
      stop = false;
    }

    if (game_running)
    {
      generations++;
      
      for (x=0; x<TOTAL_ROWS_COLS; x++)
      {
	for (y=0; y<TOTAL_ROWS_COLS; y++)
	{
	  // Count neighbours
	  neighbours = 0;
	  // Left
	  if (x > 0)
	  {
	    if (cells[x - 1][y] == ALIVE) { neighbours = neighbours + 1; }
	  }
	  // Right
	  if (x < (TOTAL_ROWS_COLS - 1))
	  {
	    if (cells[x + 1][y] == ALIVE) { neighbours = neighbours + 1; }
	  }
	  // Above
	  if (y < (TOTAL_ROWS_COLS - 1))
	  {
	    if (cells[x][y + 1] == ALIVE) { neighbours = neighbours + 1; }
	  }
	  // Below
	  if (y > 0)
	  {
	    if (cells[x][y - 1] == ALIVE) { neighbours = neighbours + 1; }
	  }
	  // Down and left
	  if ((x > 1) && (y > 0))
	  {
	    if (cells[x - 1][y - 1] == ALIVE) { neighbours = neighbours + 1; }
	  }
	  // Up and left
	  if ((x > 1) && (y < (TOTAL_ROWS_COLS - 1)))
	  {
	    if (cells[x - 1][y + 1] == ALIVE) { neighbours = neighbours + 1; }
	  }
	  // Up and right
	  if ((x < (TOTAL_ROWS_COLS - 1)) && (y < (TOTAL_ROWS_COLS - 1)))
	  {
	    if (cells[x + 1][y + 1] == ALIVE) { neighbours = neighbours + 1; }
	  }
	  // Down and right
	  if ((x < (TOTAL_ROWS_COLS - 1)) && (y > 0))
	  {
	    if (cells[x + 1][y - 1] == ALIVE) { neighbours = neighbours + 1; }
	  }
	  
	  //  Live / Die / Born Logic
	  if (cells[x][y] == ALIVE)
	  {
	    if (neighbours < 2)
	    {
	      new_cells[x][y] = DEAD;
	    }
	    else
	    {
	      if (((neighbours == 2) || (neighbours == 3)))
	      {
		new_cells[x][y] = ALIVE;
	      }
	      else
	      {
		if (neighbours > 3)
		{
		  new_cells[x][y] = DEAD;
		}
		else
		{
		  new_cells[x][y] = DEAD;
		}
	      }
	    }
	  }
	  else
	  {
	    if (neighbours == 3)
	      new_cells[x][y] = ALIVE;
	    else
	      new_cells[x][y] = DEAD;
	  }
	}
      }
      std::copy(&new_cells[0][0], (&new_cells[0][0] + (TOTAL_ROWS_COLS * TOTAL_ROWS_COLS)), &cells[0][0]);
    }
    
    // Draw Cells
    //
    draw_cells(renderer);
  
    // Display
    //
    SDL_RenderPresent(renderer);
    
    if (game_running) SDL_Delay(sleep_time);
  }
  printf("Generations = %d\n", generations);
}
