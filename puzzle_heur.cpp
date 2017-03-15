#include "puzzle_heur.h"
#include <iostream>
#include <cmath>
using namespace std;


int PuzzleManhattanHeuristic::compute(int *tiles, int size){
int dim = static_cast<int>(sqrt(size)); //find dimension
int sum = 0; //keep sum of total manhattan heuristic

//go slot by slot, looking for each index how far the corresponding tile is located
for(int i=1; i < size; i++){ //excluding first position
  int present_row, present_col;
  for (int j=0; j<size; j++){ //search for current location of tile= current index
    if (i==tiles[j]){
      present_row = j/dim;
      present_col = j % dim;
      break;
    }
  }
  int index_row = i/dim;
  int index_col = i % dim;
  sum += abs(present_row- index_row)+abs(present_col-index_col); //add all the distances 
}

return sum;
}

//find out of place tiles
int PuzzleOutOfPlaceHeuristic::compute(int *tiles, int size){
int sum=0;
//go slot by slot, looking if it is on place
for(int i=1; i < size; i++){ //excluding first position
  if(i!=tiles[i]){
    sum++;
  }
}

return sum;
}





