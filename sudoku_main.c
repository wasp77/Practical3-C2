#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int length;
  int value;
  scanf("%d", &length);
  length = length * length;
  board_str* sudoku_board = make_board(length);
  for (int row = 0; row < length; row++) {
    for (int column = 0; column < length; column++) {
      scanf("%*[ \n\t]%d", &value);
      write_sudoku(row, column, value, sudoku_board);
    }
  }
  printf("\n");
  print_board(sudoku_board -> board, length);
  printf("\n");
  switch (check_sudoku(sudoku_board -> board, length)) {
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
  free_board(sudoku_board);
  return 0;
}
