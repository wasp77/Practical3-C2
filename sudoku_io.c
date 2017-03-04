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
  int box_length = length/length;
  bool incomplete_check = false;
  validators checker;

  for (int row = 0; row < length; row++) {
    for (int column = 0; column < length; column++) {
      if (b[row][column] == 0) {
        incomplete_check = true;
      } else{
        checker = check_column(b, row, column);
        if (checker == INVALID) {
          return INVALID;
        }
        checker = check_row(b, row, column);
        if (checker == INVALID) {
          return INVALID;
        }
      }
    }
  }

  for (int i = 0; i < length; i += box_length) {
    for (int box_row = i; box_row < box_length + i; box_row++) {
      for (int box_column = i; box_column < box_length + i; box_column++) {
        if (b[box_row][box_column] != 0) {
          checker = check_box(b, i, b[box_row][box_column], box_length + i);
          if (checker == INVALID) {
            return INVALID;
          }
        }
      }
    }
  }

  if(incomplete_check == false) {
    return COMPLETE;
  } else {
    return INCOMPLETE;
  }
}

validators check_row(int** b, int row, int column) {
  for (int i = 0; i < row; i++) {
    if(b[row][column] == b[i][column]) {
      return INVALID;
    }
  }
  return COMPLETE;
}

validators check_column(int** b, int row, int column) {
  for (int i = 0; i < column; i++) {
    if(b[row][column] == b[row][i]) {
      return INVALID;
    }
  }
  return COMPLETE;
}

validators check_box(int** b, int start, int value, int length) {
  for (int i = start; i < length; i++) {
    for (int x = start; i < length; i++) {
      if (b[i][x] == value) {
        return INVALID;
      }
    }
  }
  return COMPLETE;
}
