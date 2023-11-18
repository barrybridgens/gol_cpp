// Game of life definitions

const int SC_WIDTH_HEIGHT = 800;
const int TOTAL_ROWS_COLS = 80;
const int CELL_SIZE = (SC_WIDTH_HEIGHT / TOTAL_ROWS_COLS);

int cells[TOTAL_ROWS_COLS][TOTAL_ROWS_COLS];
int new_cells[TOTAL_ROWS_COLS][TOTAL_ROWS_COLS];

const int DEAD = 0;
const int ALIVE = 1;
