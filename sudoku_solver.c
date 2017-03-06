#include "sudoku.h"
#include <stdio.h>
static int answers;

int main(void) {
  int length;
  int value;
  int solve_checker = 0;

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
  if (solve_checker == 0) {
    printf("UNSOLVABLE\n");
  } else if (solve_checker == 1) {
    printf("MULTIPLE\n");
  } else {
    print_board(sudoku_board -> board, length);
  }
  free_board(sudoku_board);
  return 0;
}

int sudoku_solver(int** board, int length) {
  validators check_board;
  check_board = check_sudoku(board, length);
  if (check_board == INVALID) {
    return 0;
  }
  if (check_board == INCOMPLETE) {
    for (int row = 0; row < length; row++) {
      for (int column = 0; column < length; column++) {
        if (board[row][column] == 0) {
          for (int i = 0; i <= length; i++) {
            int** updated_board = copy_board(board);
            updated_board[row][column] = i;
            sudoku_solver(updated_board, length);
          }
        }
      }
    }
  }
  if (check_board == COMPLETE) {
    answers++;
  }
  if (answers > 1) {
    return 1;
  }
}




// for (int i = 0; i < length; i++) {
//   for (int x = 0; x < length; x++) {
//     printf("%3d",board[i][x]);
//   }
//   printf("\n");
// }
