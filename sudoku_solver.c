#include "sudoku.h"
#include <stdio.h>

int main(void) {
  int length;
  int value;
  int solve_checker;
  scanf("%d", &length);
  length = length * length;
  board_str* sudoku_board = make_board(length);
  for (int row = 0; row < length; row++) {
    for (int column = 0; column < length; column++) {
      scanf("%3d", &value);
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

int sudoku_solver(int** board, int row, int column, int length) {
  validators checker;
  if (all_asigned(board, length)) {
    return 1;
  }

  if (board[row][column] != 0) {
    if (column + 1 == length) {
      if (sudoku_solver(board, row + 1, 0, length)) {
        return 1;
      }
    } else {
      if (sudoku_solver(board, row, column + 1, length)) {
        return 1;
      }
    }
    return 0;
  }

  for (int i = 1; i <= length; i++) {
    board[row][column] = i;
    checker = check_sudoku(board, length);
    if (checker != INVALID) {
      if (column + 1 == length) {
        if (sudoku_solver(board, row + 1, 0, length)) {
          return 1;
        }
      } else {
        if (sudoku_solver(board, row, column + 1, length)) {
          return 1;
        }
      }
      board[row][column] = 0;
    }
  }
}


int all_asigned(int** b, int length) {
  for (int row = 0; row < length; row++) {
    for (int column = 0; column < length; column++) {
      if (b[row][column] == 0) {
        return 0;
      }
    }
  }
  return 1;
}
