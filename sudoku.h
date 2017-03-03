typedef struct board_str {
  int** board;
} board_str;

board_str* make_board(int length);
void read_sudoku(int row, int column, board_str* b);
void write_sudoku(int row, int column, int value, board_str* b);
void free_board(board_str* b);
int** make_2DArray(int length);
void print_board(int** b, int length);
int** copy_board(int** b);

typedef enum validators {INVAlID, INCOMPLETE, COMPLETE} validators;
validators check_sudoku(int** b, int length);
typedef enum bool {false, true} bool;

int sudoku_solver(int** board, int length);
