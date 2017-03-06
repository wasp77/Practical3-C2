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
  validators row_checker;
  validators column_checker;
  validators box_checker;

  bool contains_zero = false;

  int board_row[length];
  int board_column[length];
  int* box;

  int box_length = length / length;


  for (int row = 0; row < length; row++) {
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

  for (int column = 0; column < length; column++) {
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


  for(int row = 0; row < length; row += box_length) {
    for(int column = 0; column < length; column += box_length) {
      box = get_box(b, row, column, box_length);
       for (int i = 0; i < length; i++) {
         printf("%d ", box[i]);
       }
       printf("\n");
      box_checker = check_list(box,length);
      if (box_checker == INVALID) {
        return INVALID;
      }
      free(box);
    }
  }

  if (contains_zero == true) {
    return INCOMPLETE;
  } else {
    return COMPLETE;
  }


}

int* get_box (int** board, int start_row, int start_column, int length) {
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

validators check_list(int* list, int length) {
  bool contains_zero = false;
  for (int i = 0; i < length; i++) {
    for (int x = i + 1; x < length; x++) {
      if (list[i] == 0) {
        contains_zero = true;
        break;
      }
      if (list[i] == list[x]) {
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
