#include <iostream>
#include <cstdlib>
#include <deque>
#include <map>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

using namespace std;


int main(int argc, char *argv[])
{

  if(argc < 3){
    cerr << "Usage: ./puzzle size initMoves seed" << endl;
    return 1;
  }

  int size, initMoves, seed;

  size = atoi(argv[1]);
  initMoves = atoi(argv[2]);
  seed = atoi(argv[3]);

  Board b(size,initMoves,seed);

  //**** Implement the gameplay here

int inputTile=0; //input of tile to move
deque<int> solutions;  //deque with a A* algorith path
int num_expansions=0; //number of expansions created by the A*
/*
int heu=1; //flag to set heuristic
cout << " Default heuristic = Manhattan  "<<endl;
cout << " Please enter '1' or '2' for what heuristic to use ( 1=Manhattan or 2=out of place ): "<<endl;

cin >> heu;
//set heuristic to use depending on input:
PuzzleHeuristic* heuristic;
PuzzleHeuristic* temp;  
if(heu==2){   
  PuzzleOutOfPlaceHeuristic man;   
    temp=&man;  
}   
else{  
  PuzzleManhattanHeuristic man;  
    heuristic=&man;  
}   
*/

//run loop until the puzzle not solved
while( !b.solved() ){
  cout << b <<endl;
  cout << "Enter move or -1 for a cheat: "; //ask user to enter
  cin >> inputTile;
  cout << endl;
  //run cheat if input=-1
  if (inputTile==-1){
    //call A* algorith 
    PuzzleSolver solve(b); 
    //declare the heuristic: can use manhatan or out of place
    PuzzleHeuristic* heuristic;
    PuzzleManhattanHeuristic man;  
    heuristic=&man;  
    num_expansions=solve.run(heuristic);
    if ( num_expansions==-1 ) { //return error if there is no path found
      cout<< " no solution possible" <<endl;; 
      return 1;
    } 
    solutions = solve.get_solutions(); //obtain sequence of steps to solve
    cout << "Try this sequence: "; 
    //iterate over solutions to print out the path
    deque<int>::iterator it_deq;
    for( it_deq= solutions.begin(); it_deq !=solutions.end(); it_deq++ ){
      cout << " " << *it_deq ;
    }
    cout<<endl;
    cout << "(Expansions = "<< num_expansions << ")"<<endl;
    continue;//continue with next iteration
  }
  b.move(inputTile);
}

cout << b <<endl;
cout<< "Congratulations! you have solved the puzzle"<<endl;

  return 0;
}
