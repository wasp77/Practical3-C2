#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int length;
  int value;
  scanf("%d", &length);
  length = length * length; // Square the length to get the full size
  board_str* sudoku_board = make_board(length);
  for (int row = 0; row < length; row++) {
    for (int column = 0; column < length; column++) {
      scanf("%3d", &value); // Read in the sudoku with a padding of 3
      write_sudoku(row, column, value, sudoku_board); // Createt the board
    }
  }
  printf("\n");
  print_board(sudoku_board -> board, length); // Print out given board
  printf("\n");
  switch (check_sudoku(sudoku_board -> board, length)) { // Check if invalid, incomplete, or complete
    case INVALID:
        printf("INVALID\n");
        break;
    case INCOMPLETE:
        printf("INCOMPLETE\n");
        break;
    case COMPLETE:
        printf("COMPLETE\n");
        break;
    default:
        printf("ERROR COMPUTING");
  }
  free_board(sudoku_board); // Free up allocated memory
  return 0;
}
