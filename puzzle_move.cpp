#include "board.h"
#include "puzzle_move.h"
#include <iostream>
#include "puzzle_heur.h"

using namespace std;

PuzzleMove::PuzzleMove(Board &b): b_(&b), prev_(NULL), g_(0),h_(0),f_(0){
} 

PuzzleMove::PuzzleMove(int tile, Board *b, PuzzleMove *parent):tileMove_(tile),b_(b), prev_(parent),g_(parent->g_+1),h_(0),f_(0){
}

PuzzleMove::~PuzzleMove(){
}

// comparison operators for PuzzleMoves based on f distance 
bool PuzzleMove::operator<(const PuzzleMove& p) const{
  if (f_<p.f_) {return true;}

  return false;
}

bool PuzzleMove::operator>(const PuzzleMove& p) const{
  if (f_>p.f_) {return true;}

  return false;
}
  bool PuzzleMove::operator==(const PuzzleMove& p) const{
  if (f_==p.f_) {return true;}

  return false;
}

