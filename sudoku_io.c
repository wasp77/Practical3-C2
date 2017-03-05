#include "sudoku.h"
#include <stdlib.h>
#include <stdio.h>

board_str* make_board(int length) {
  board_str* b = malloc(sizeof(board_str));
  b -> board = make_2DArray(length);
  return b;
}

int** make_2DArray(int length) {
  int **the_array;
  the_array = malloc(length * sizeof(int*));
  for (int i = 0; i < length; i++) {
    the_array[i] = malloc(length * sizeof(int));
  }
  return the_array;
}


void read_sudoku(int row, int column, board_str* b) {
  int output = b -> board[row][column];
  printf("%d\n", output);
}

void write_sudoku(int row, int column, int value, board_str* b) {
  b -> board[row][column] = value;
}

int** copy_board(int** b) {
  int** new_board = b;
  return new_board;
}

void free_board(board_str* b) {
  free(b -> board);
  free(b);
}

void print_board(int** b, int length) {
  for (int row = 0; row < length; row++) {
    for (int column = 0; column < length; column++) {
      printf("%3d", b[row][column]);
    }
    printf("\n");
  }
}

validators check_sudoku(int** b, int length) {
  validators checker;
  bool contains_zero = false;
  int board_row[length];
  int board_column[length];


  for (int row = 0; row < length; row++) {
    for (int column = 0; column < length; column++) {
      board_row[column] = b[row][column];
    }
    checker = check_list(board_row, length);
    if (checker == INVALID) {
      return INVALID;
    } else if (checker == INCOMPLETE) {
      contains_zero = true;
    }
  }

  for (int column = 0; column < length; column++) {
    for (int row = 0; row < length; row++) {
      board_column[row] = b[row][column];
    }
    checker = check_list(board_column, length);
    if (checker == INVALID) {
      return INVALID;
    } else if (checker == INCOMPLETE) {
      contains_zero = true;
    }
  }



  if (contains_zero == true) {
    return INCOMPLETE;
  } else {
    return COMPLETE;
  }


}

validators check_list(int* list, int length) {
  bool contains_zero = false;
  for (int i = 0; i < length; i++) {
    if (list[i] == 0) {
      contains_zero = true;
    } else {
      for (int x = length; x > i; x--) {
        if (list[i] == list[x] && list[x] != 0) {
          return INVALID;
        }
      }
    }
  }

  if (contains_zero == true) {
    return INCOMPLETE;
  } else {
    return COMPLETE;
  }
}
