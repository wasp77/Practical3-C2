#include "sudoku.h"
#include <stdio.h>

static bool invalid = false;
static bool answer = false;
static bool multiple = false;

int main(void) {
  int length;
  int value;
  int** solved_board;

  scanf("%d", &length);
  length = length * length;
  board_str* sudoku_board = make_board(length);

  for (int row = 0; row < length; row++) {
    for (int column = 0; column < length; column++) {
      scanf("%*[ \n\t]%d", &value);
      write_sudoku(row, column, value, sudoku_board);
    }
  }

  solved_board = sudoku_solver(sudoku_board -> board, length);

  if (invalid == true) {
    printf("UNSOLVABLE\n");
  } else if (multiple == true) {
    printf("MULTIPLE\n");
  } else {
    print_board(solved_board, length);
  }


  free_board(sudoku_board);
  return 0;
}

int** sudoku_solver(int** board, int length) {
  switch (check_sudoku(board, length)) {
    case INVALID:
        invalid = true;
        return board;
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
    case COMPLETE:
        if (answer == false) {
          answer = true;
          return board;
        }
  }
  multiple = true;
  return board;
}
