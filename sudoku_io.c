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
      printf("  %d  ", b[row][column]);
    }
    printf("\n");
  }
}

validators check_sudoku(int** b, int length) {
  bool contains_zero = false;
  for (int row = 0; row < length; row++) {
    for (int column = 0; column < length; column++) {
      if (b[row][column] == 0) {
        contains_zero = true;
      }
      if (column > 0) {
        for (int i = 0; i < column; i++) {
          if (b[row][column] == b[row][i] && b[row][column] != 0) {
            return INVAlID;
          }
        }
      }
      if (row > 0) {
        for (int x = 0; x < row; x++) {
          if(b[row][column] == b[x][column] && b[row][column] != 0) {
            return INVAlID;
          }
        }
      }
    }
  }
  if (contains_zero == false) {
    return COMPLETE;
  } else {
    return INCOMPLETE;
  }
}
