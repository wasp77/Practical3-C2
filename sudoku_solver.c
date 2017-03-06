#include "sudoku.h"
#include <stdio.h>

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

  solve_checker = sudoku_solver(sudoku_board -> board, 0, 0, length);

  if (solve_checker) {
    print_board(sudoku_board -> board, length);
  } else {
    printf("UNSOLVABLE\n");
  }

  free_board(sudoku_board);
  return 0;
}

int sudoku_solver(int** board, int row, int column,int length) {
  validators cell_checker;
  int** new_board;
  if (row == length) {
    return 1;
  }

  if (board[row][column]) {
    if (column < length) {
      if (sudoku_solver(board, row, column++, length)) {
        return 1;
      }
    } else {
      if (sudoku_solver(board, row++, column, length)) {
        return 1;
      }
    }
    return 0;
  }

  for (int i = 1; i < length + 1; i++) {
    new_board = copy_board(board);
    new_board[row][column] = i;
    cell_checker = check_sudoku(new_board, length);
    if (cell_checker != INVALID) {
      if (column < length) {
        if (sudoku_solver(new_board, row, column++, length)) {
          return 1;
        }
      } else {
        if (sudoku_solver(new_board, row++, column, length)) {
          return 1;
        }
      }
      board[row][column] = 0;
    }
  }
  return 0;
}




// for (int i = 0; i < length; i++) {
//   for (int x = 0; x < length; x++) {
//     printf("%3d",board[i][x]);
//   }
//   printf("\n");
// }
