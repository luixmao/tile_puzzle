#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include "puzzle_solver.h"
#include "puzzle_move.h"
#include "puzzle_heur.h"
#include "board.h"
#include <queue>
#include <deque>

using namespace std;


// Constructor (makes a copy of the Board and stores it in _b)
PuzzleSolver::PuzzleSolver(const Board &b): b_(b), expansions_(0){ }

PuzzleSolver::~PuzzleSolver(){
}
// Return how many expansions were performed in the search
int PuzzleSolver::getNumExpansions()
{
  return expansions_; 
}

//return path for solutions
deque<int> PuzzleSolver::get_solutions(){
  return solutions;
}


// Run the A* search returning -1 if no solution exists or
//  the number of moves in the solution
int PuzzleSolver::run(PuzzleHeuristic *ph){

  bool solved= false;// whether there it has solution
  //create lists:
  PuzzleMoveHeap openlist;
  BoardSet closedlist; //boards that are already checked
  deque<PuzzleMove*> garbagelist; //to delete puzzle moves
  deque<Board*> erraseBoard; //to delete boards

  //initialize to the starting board
  PuzzleMove* Pmove;
  Pmove = new PuzzleMove(b_); 

  
  //compute heuristics, not g_ already initialized
  //PuzzleManhattanHeuristic com;
  Pmove->g_ = 0;
  Pmove->h_ = ph->compute(b_.getTiles(), b_.getSize());


  //put in intial board
  openlist.push(Pmove);

  //run search until there is not more elements
  while(!openlist.empty() ){  
 
    //if it is solved break the loop
    if(  openlist.top()->b_->solved() ) {
      solved =true; //to know that it is solved
      //find tile solutions backwards ( from solution to input board ) :
      PuzzleMove* previous = openlist.top();
      //track back until the parent muve is null, which would be our initial board
      while( previous->prev_ != NULL){
        solutions.push_front(previous->tileMove_);//store tile moved into solutions
        previous= previous->prev_;
      }
      break;
    }

    //current top of priority queue is parent puzzle move of derivations
    PuzzleMove* parent=openlist.top();

    garbagelist.push_back(parent);    //add to puzzle_move 

    //since it is not solved, find the derivations of parent move returned into the map
    map<int,Board*> mapMoves= parent->b_->potentialMoves();
    map<int,Board*>::iterator it;
    for( it= mapMoves.begin(); it!=mapMoves.end() ; it++ ){

      //store boards to delete
      erraseBoard.push_back(it->second);

      bool already_found=false;//flag to know if it is inside
      //check that it is not on closedlist before:
      BoardSet::iterator it_moves;
      for(it_moves = closedlist.begin(); it_moves!=closedlist.end(); ++it_moves){
         if( **it_moves ==*(it->second) ){ //compare the boards they are pointing at
         already_found=true;
         break; //exit for loop
         }    
      }

      if(already_found){ //continue with next item in the map iteration if the board was already checked
         continue;  
      }     
  
      //if not repeated create new puzzleMove
      expansions_++; 

      //make new puzzle move
      Pmove = new PuzzleMove(it->first, it->second, parent); //where: it->first = tile value ;  it->second = pointer to board ;  parent = pointer to previous puzzle move

      //compute heuristics for the derived case
      Pmove->h_ = ph->compute(Pmove->b_->getTiles(), Pmove->b_->getSize());
      Pmove->g_ = Pmove->prev_->g_ +1; // g_ = parent's g_ +1
      Pmove->f_ = Pmove->g_ + Pmove->h_ ;
      //put derivation into open list
      openlist.push(Pmove);
      closedlist.insert(Pmove->b_);       //add boards into close list
    }
    
    //once finished with the parent move put into close list 
    openlist.pop();                              //remove puzzle_move from open list
  }

  //put left overs into garbage list
  while(!openlist.empty() ){  
    garbagelist.push_back( openlist.top() );    //add left over puzzle_move into close list 
    openlist.pop();      
  }

  //delete dynamic allocated data:
  //errase Boards
  deque<Board*>::iterator it_board;
  for(it_board = erraseBoard.begin(); it_board!=erraseBoard.end();++it_board){
      delete *it_board;
  }

  //delete the puzzle moves 
  deque<PuzzleMove*>::iterator it_moves;
  for(it_moves = garbagelist.begin(); it_moves!=garbagelist.end(); ++it_moves){
    delete *it_moves; //delete moves
  }

  //return -1 or the number of expanisions depending on wether it was solved or not
  if (solved==true){
    return expansions_;}
  else {
    return -1;
  }
}
