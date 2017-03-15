#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <cstdlib>
#include "board.h"
using namespace std;


/** Init a board of given size and scramble it with numInitMoves 
 * by moving the space tile with a randomly chosen direction N, W, S, E
 * some of which may be invalid, in which case we skip that move 
 * 
 *  @param size Number of tiles for the game.  \
 *      Should be a perfect square (4, 16, 25)
 *  @param numInitMoves Number of tile moves to attempt to scramble the board
 *  @param seed Use to seed the random number generator (srand) 
 */
Board::Board(int size, int numInitMoves, int seed )
{
  size_ = size; 
  tiles_ = new int[size_];
  dim = static_cast<int>(sqrt(size_)); //make data
  srand(seed); 
  for(int i=0; i < size_; i++){
    tiles_[i] = i;
  }
  int blankLoc = 0;
  for(int i=0; i < numInitMoves; i++){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < size_){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      tiles_[blankLoc] = tiles_[randNeighbor];
      tiles_[randNeighbor] = 0;
      blankLoc = randNeighbor;
    }
  }
//to know where index of 0 is 
for(int i=0; i<size_; i++){ 
  if(tiles_[i]==0){
    index_0=i;
  }
}

}


bool Board::operator<(const Board& rhs) const
{
  if(size_ < rhs.size_){
    return true;
  }
  bool val = false;
  for(int i=0; i < size_; i++){
    if(tiles_[i] < rhs.tiles_[i]){
       //val = true;
       //break;
       return true;
     }
     else if(tiles_[i] > rhs.tiles_[i]){
       //break;
       return false;
     }
  }
  return val;
}


//////  code /////

//destructor
Board::~Board() {
 delete [] tiles_ ; 

}

//another constructor to make deep copy
Board::Board(const Board &b){

if (! (this==&b) ) {  //if not self assignment, then copy
  tiles_ = new int[b.size_];  //allocate new memory
  //make deep copy, element by element 
  for(int i=0; i<b.size_;i++){ 
    tiles_[i]=b.tiles_[i];
  }
}
//copy size, dimension and index of 0
size_=b.size_;
dim = b.dim;
index_0=b.index_0;
}

//return tiles
int* Board::getTiles()
{
  return tiles_;
}
//return size
int Board::getSize(){
  return size_;
}

//create potential boards and return to 
map<int, Board*> Board::potentialMoves(){
map<int, Board*> mapMoves; //create map
int possible_tile=0; //possible tiles to move

//find the adyacent tiles to 0
if (index_0/dim !=0) { //if 0 is not on top
  possible_tile=tiles_[index_0-dim]; //possible to move up
  mapMoves[possible_tile]= new Board(*this); //initialize a new board with current board
  mapMoves[possible_tile]->move(possible_tile); // make move on new board
}

if (index_0/dim != dim-1) { //if 0 is not on bottom
  possible_tile=tiles_[index_0+dim]; //possible to down up 
  mapMoves[possible_tile]= new Board(*this); //initialize a new board with current board
  mapMoves[possible_tile]->move(possible_tile); // make move on new board
}

if (index_0% dim !=0) { //if 0 is not on left
  possible_tile=tiles_[index_0-1]; //possible to left
  mapMoves[possible_tile]= new Board(*this); //initialize a new board with current board
  mapMoves[possible_tile]->move(possible_tile); // make move on new board
}

if (index_0 % dim != dim-1) { //if 0 is not on right
  possible_tile=tiles_[index_0+1]; //possible to move right
  mapMoves[possible_tile]= new Board(*this); //initialize a new board with current board
  mapMoves[possible_tile]->move(possible_tile); // make move on new board
} 


return mapMoves;
} 

//print out board
ostream& operator<<(ostream& os,  Board& bb) 
{
  //get tiles and dimension
  int* tiles=  bb.getTiles(); 
  int dim = static_cast<int>(sqrt(bb.getSize() ));
  //prin one by one setting the width
  for(int i =0; i< bb.getSize(); i++){
    if (tiles[i]==0){
      os << setw(3)<< " ";} // if 0, display space
    else{
      os << setw(3) << tiles[i]; //set width
    }
    if( ! ( (i+1)%dim ) ){
      os << endl;
     }
  }
 return os;
}

//compare operator for boards
bool Board::operator==(const Board& rhs) const
{
//check tile by tile if they are equal
for(int i=0; i<size_; i++){
  if(tiles_[i]!=rhs.tiles_[i]){
    return false;  //it's false if one of the elements is different
  }
}
//if all tiles are equal return true
return true;
}

//comperare that they are not eual
bool Board::operator!=(const Board& rhs) const
{
//if a single tile is different return true
for(int i=0; i<size_; i++){ 
  if(tiles_[i]!=rhs.tiles_[i]){
    return true;  //it's true if one of the elements is different
  }
}
//if all tiles are equal return false 
return false; 
}

void Board::move(int val)
{

vector<int> myVec; //vectore to store all the possible moves
int index_val; //input of the value 0 to move to

//find the index for the input value
for(int i=0; i<size_; i++){ 
  if(tiles_[i]==val){
    index_val=i; 
  }
}

int possible_tile=0; //posible tiles to move to

//find possible moves and store them into the vector
if (index_0/dim !=0) { //if 0 is not on top
  possible_tile=tiles_[index_0-dim]; //possible to move up
  myVec.push_back(possible_tile); //store in vector
}

if (index_0/dim != dim-1) { //if 0 is not on bottom
  possible_tile=tiles_[index_0+dim]; //possible to down up 
  myVec.push_back(possible_tile);
}

if (index_0% dim !=0) { //if 0 is not on left
  possible_tile=tiles_[index_0-1]; //possible to left
  myVec.push_back(possible_tile);
}

if (index_0 % dim != dim-1) { //if 0 is not on right
  possible_tile=tiles_[index_0+1]; //possible to move right
  myVec.push_back(possible_tile);
} 

//check if the value is one of the possibilities
bool valid=false; //whether the move is possible or not
vector<int>::iterator it; //iterate over all possible values to see if input is one of them
for (it=myVec.begin(); it!=myVec.end(); ++it){
  if(*it==val){
    valid=true;
  }
}

//if is not in the vector it is not valid
if(!valid){ 
  cout << " Not a valid Move! " <<endl;
  return;
}

//if it is valid, swap
tiles_[index_0]=val; //swap
tiles_[index_val]=0; 
index_0=index_val; // update index of 0
}

//check if the board is the solution
bool Board::solved(){
for(int i=0; i<size_; i++){ 
  if(tiles_[i]!=i){
    return false;
  }
}
return true;
}


//assignment operator to make a deep copy
Board& Board::operator=(const Board& rhs)  {
  if ( this==&rhs ) { return *this;} //if not self assignment, then copy
  if ( tiles_  ) {//if initialized delete the one before and alocate a new one
    delete tiles_;
  }   
 //make new alocation and copy data over
  tiles_ = new int[rhs.size_];  
  for(int i=0; i<rhs.size_;i++){
    tiles_[i]=rhs.tiles_[i];
  }
  size_=rhs.size_;
  dim = rhs.dim;
  index_0=rhs.index_0;
  return *this;
}
