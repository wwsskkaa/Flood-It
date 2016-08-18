#include "cell.h"
#include "game.h"
using namespace std;

/*
Cell - implements a single cell in the grid
*/
void Cell::notifyNeighbours() const {
   for(int i = 0 ; i < numNeighbours ; i++)
   {
      if(neighbours[i] != NULL)
      {
         neighbours[i]->notify(state, prevState);
      }
   }
}  // Tell all of my neighbours that I have been switched.

void Cell::notifyGame() const  {
   game->notify(row, column, prevState, state);
}

/*
ctor
*/
Cell::Cell():state(0),prevState(0),numNeighbours(0),row(0),column(0),game(NULL)
{}

/*
getter for state
*/
int Cell::getintState() const{
   return state;
}

/*
getter for state in char
*/
char Cell::getState() const{
   return state + '0';
}

/*
setter for prevState and state
*/
void Cell::setState(const int& change){
   prevState = state;
   state = change;
}

/*
setter for co-ordinates of the cell
*/
void Cell::setCoords(const int r, const int c){
   row = r;
   column = c;
}
/*
setter for game
*/
void Cell::setGame(Game * g){
   game = g;
}

/*
update the neighbours array with a new added neighbour
*/
void Cell::addNeighbour(Cell *neighbour){
   neighbours[numNeighbours] = neighbour;
   numNeighbours++; //increment number of neighbors
}

/*
* Intended to be called only by the game class for changing the state of the 0 0 cell
*/
void Cell::notify( const int & change){
   if(state != change)
   {//only makes sense to set state  if state is different from change state
      setState(change);
      MakeNotify();
   }
}

/*
* Intended to be called by Cells to notify their neighbors
* only the neighbours which share the same state will be set and updated
  it only makes sense if only set and notify when the state is different from the change state
*/
void Cell::notify( const int & current, const int & previous){
   if(state != current && state == previous)
   {
      setState(current);
      MakeNotify();
   }
}

/*
notify game and neighbours
*/
void Cell::MakeNotify(){
   notifyGame();
   notifyNeighbours();
}        
