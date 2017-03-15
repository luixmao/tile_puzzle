# Name: Mark Redekopp
# email: redekopp@usc.edu

CC = g++
CFLAGS = -g -Wall
LDFLAGS =

all: puzzle
puzzle : puzzle.o board.o puzzle_move.o puzzle_heur.o puzzle_solver.o
	@echo "Compiling and linking"
	$(CC) $(CFLAGS) puzzle_solver.o puzzle_move.o board.o  puzzle_heur.o puzzle.o -o puzzle

puzzle.o : puzzle_heur.h puzzle_solver.h board.h puzzle.cpp
	$(CC) $(CFLAGS) -c puzzle.cpp

board.o : board.h board.cpp
	$(CC) $(CFLAGS) -c board.cpp

puzzle_solver.o : board.h puzzle_solver.cpp puzzle_solver.h puzzle_move.h puzzle_heur.h
	$(CC) $(CFLAGS) -c puzzle_solver.cpp

puzzle_heur.o : puzzle_heur.h puzzle_heur.cpp
	$(CC) $(CFLAGS) -c puzzle_heur.cpp

puzzle_move.o : puzzle_move.h board.h puzzle_move.cpp
	$(CC) $(CFLAGS) -c puzzle_move.cpp


clean:
	rm -f puzzle *.o *~
tarit:
	tar cvf puzzle_search.tar Makefile puzzle_solver.h puzzle_heur.h puzzle_move.h board.h board.cpp puzzle_solver.cpp puzzle.cpp
	scp puzzle_search.tar redekopp@ee.usc.edu:Sites/ee355/code


