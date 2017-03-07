#include "sudoku.h"
#include <stdlib.h>
#include <stdio.h>

board_str* make_board(int length) {
  board_str* b = malloc(sizeof(board_str)); // Allocate memory for the board
  b -> board = make_2DArray(length);
  return b;
}

int** make_2DArray(int length) { // Alocate the 2D array bearing in mind it is a pointer to a pointer
  int **the_array;
  the_array = malloc(length * sizeof(int*));
  for (int i = 0; i < length; i++) {
    the_array[i] = malloc(length * sizeof(int));
  }
  return the_array;
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
      printf("%3d", b[row][column]); // Print out cell with a padding of 3
    }
    printf("\n");
  }
}

validators check_sudoku(int** b, int length) { // Check whether the given sudoku is invalid, incomplete, or complete
  validators row_checker;
  validators column_checker;
  validators box_checker;

  bool contains_zero = false;

  int board_row[length];
  int board_column[length];
  int* box;

  int box_length = unsquare(length); // Get the length of a box


  for (int row = 0; row < length; row++) { // check each row
    for (int column = 0; column < length; column++) {
      board_row[column] = b[row][column];
    }

    row_checker = check_list(board_row, length);
    if (row_checker == INVALID) {
      return INVALID;
    }
    if (row_checker == INCOMPLETE && contains_zero != true) {
      contains_zero = true;
    }

  }

  for (int column = 0; column < length; column++) { // Check each column
    for (int row = 0; row < length; row++) {
      board_column[row] = b[row][column];
    }

    column_checker = check_list(board_column, length);
    if (column_checker == INVALID) {
      return INVALID;
    }
    if (column_checker == INCOMPLETE && contains_zero != true) {
      contains_zero = true;
    }

  }


  for(int row = 0; row < length; row += box_length) { // Check that each box does not contain multiples
    for(int column = 0; column < length; column += box_length) {
      box = get_box(b, row, column, box_length); // Get the array containing the elements
      box_checker = check_list(box,length); // Check the given box
      if (box_checker == INVALID) {
        return INVALID;
      }
      free(box); // Free up allocated memory of a box after use
    }
  }

  if (contains_zero == true) {
    return INCOMPLETE;
  } else {
    return COMPLETE;
  }


}

int* get_box (int** board, int start_row, int start_column, int length) { // Return an array holding the elements of a given box
  int* the_box = malloc(sizeof(int) * (length*length));
  int counter = 0;
  for (int row = start_row; row < length + start_row; row++) {
    for (int column = start_column; column < length + start_column; column++) {
      the_box[counter] = board[row][column];
      counter++;
    }
  }
  return the_box;
}

validators check_list(int* list, int length) { // Check that the given array does not contain repeat values
  bool contains_zero = false;
  for (int i = 0; i < length; i++) {
    for (int x = i + 1; x < length; x++) {
      if (list[i] == 0) { // Cell is zero and therefore it is an incomplete sudoku
        contains_zero = true;
        break;
      }
      if (list[i] == list[x]) { // Duplicate in the list therefor incomplete
        return INVALID;
      }
    }
  }

  if (contains_zero == true) {
    return INCOMPLETE;
  } else {
    return COMPLETE;
  }

}

int unsquare(int num) {
  for (int i = 0; i < num; i++) {
    if ((i*i) == num) {
      return i;
    }
  }
}
