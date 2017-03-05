#include "sudoku.h"
#include <stdio.h>
static int answers = 0;

int main(void) {
  int length;
  int value;
  validators solve_checker;
  scanf("%d", &length);
  length = length * length;
  board_str* sudoku_board = make_board(length);
  for (int row = 0; row < length; row++) {
    for (int column = 0; column < length; column++) {
      scanf("%*[ \n\t]%d", &value);
      write_sudoku(row, column, value, sudoku_board);
    }
  }

  solve_checker = sudoku_solver(sudoku_board -> board, length);
  if (solve_checker == INVALID) {
    printf("UNSOLVABlE\n");
  }
  if (solve_checker == INCOMPLETE) {
    printf("MULTIPLE\n");
  }
  free_board(sudoku_board);
  return 0;
}

validators sudoku_solver(int** board, int length) {
  switch (check_sudoku(board, length)) {
    case INVALID:
        return INVALID;
        break;
    case INCOMPLETE:
        for (int row = 0; row < length; row++) {
          for (int column = 0; column < length; column++) {
            if (board[row][column] == 0) {
              for (int i = 1; i <= length; i++) {
                int** updated_board = copy_board(board);
                updated_board[row][column] = i;
                sudoku_solver(updated_board, length);
              }
            }
          }
        }
        break;
    case COMPLETE:
        answers++;
   }
   if (answers > 1) {
     return INCOMPLETE;
   } else {
     print_board(board, length);
   }

}
