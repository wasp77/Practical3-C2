sudoku_check : sudoku_main.o sudoku_io.o
	clang sudoku_main.o sudoku_io.o -o sudoku_check

sudoku_solver : sudoku_solver.o sudoku_io.o
	clang sudoku_solver.o sudoku_io.o -o sudoku_solver

sudoku_main.o : sudoku_main.c sudoku.h
	clang -Wall -Wextra sudoku_main.c -c

sudoku_io.o : sudoku_io.c sudoku.h
	clang -Wall -Wextra sudoku_io.c -c

sudoku_solver.o : sudoku_solver.c sudoku.h
	clang -Wall -Wextra sudoku_solver.c -c

clean :
	rm -f sudoku_main.o sudoku_io.o sudoku_solver.o sudoku_check sudoku_solver
