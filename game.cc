#include "game.h"
using namespace std;

/*
Frees the grid.
*/
void Game::clearGame()
{
   for (int i = 0; i < gridSize; ++i) {
      delete [] theGrid[i];
   }
   delete [] theGrid;
   theGrid = NULL;
}

/*
ctor 
*/
Game:: Game():theGrid(NULL),gridSize(0),notification(NULL)
{}

/*
dtor
Basically it is the same code used in clearGame()
but I personally don't understand the use of clearGame()
if we cannot even restart a new game after finishing one 
so I decided just do the same code again for dtor
*/
Game:: ~Game()
{
   for ( int i = 0; i < gridSize; i++)
   {
      delete[] theGrid[i];
   }
   delete[] theGrid ;
   theGrid = NULL;
}

/*
getter for private field gridSize
*/
int Game::getGridSize()
{
   return gridSize;
}

/*
* Receive update notification from Cells.
*/
void Game::notify(int row, int column, unsigned int oldState, unsigned int newState)
{
   updateColours(newState, oldState); //updates colours array
   notification->notify(row,column,newState); //make a notification of changing state
}

/*
isWon()
The game is won if all the cells in the grid have the same color
*/
bool Game::isWon() const
{
   bool won = false;
   unsigned int totalcellamount = gridSize * gridSize;
   for(int i = 0 ; i < NUMCOLOR ; i++)
   {
      if(colours[i] == totalcellamount)
      {
         won = true;
      }
   }
   return won;
}

/*
init:
Sets up an n x n grid.  Clears old grid, if necessary.
*/
void Game::init(int n, GameNotification *gameNotification)
{
   //if theGrid is not NULL, then clear the grid first
   if(theGrid != NULL)
   {
        clearGame();
   }
   notification = gameNotification;
   colours[0] = n * n;
   for(int a = 1 ; a < NUMCOLOR ; a++)
   {
      colours[a] = 0;
   }
   gridSize = n;
   theGrid = new Cell *[gridSize];
   for ( int i = 0 ; i < gridSize; i++)
   { // each row
      theGrid[i] = new Cell [gridSize]; //allocate n columns
      for ( int j = 0 ; j < gridSize; j++)
      {
        //each column in theGrid[i]
        theGrid[i][j].setGame(this);
        theGrid[i][j].setCoords(i,j);
      }
   }
   /*
     need to go thru the grid again to set the neighbours
   */
   for ( int i = 0 ; i < gridSize; i++)
   { // each row
      for ( int j = 0 ; j < gridSize; j++)
      {
        initNeighbours(i,j,n);
      }
   }
}

Cell* Game::findNeighbours(const string n, const int i, const int j)
{
   if(n == "above")
   {
	return &theGrid[i - 1][j];
   }
   else if(n == "below")
   {
	return &theGrid[i + 1][j];
   }
   else if(n == "left")
   {
	return &theGrid[i][j - 1];
   }
   else//right
   {
	return &theGrid[i][j + 1];
   }
}

void Game::initNeighbours(const int i,const int j,const int n)
{
   if(i != 0)
   {
      theGrid[i][j].addNeighbour(findNeighbours("above",i,j));
   }
   if(j != 0)
   {
      theGrid[i][j].addNeighbour(findNeighbours("left",i,j));
   }
   if(i != n - 1)
   {
      theGrid[i][j].addNeighbour(findNeighbours("below",i,j));
   }
   if(j != n - 1)
   {
      theGrid[i][j].addNeighbour(findNeighbours("right",i,j));
   }
}

/*
Changes (0,0) and all appropriate neighbours to state
*/
void Game::change(const int & state)
{
   theGrid[0][0].notify(state);
}

void Game::init(int row, int column, int state)
{
      updateColours(state,theGrid[row][column].getintState());
      theGrid[row][column].setState(state); //set the cell state
      notification->notify(row,column,state); // need to make notification of changing state
}  //Called by Controller:init in response to initialization requests when game is in init mode

void Game::updateColours(const int & increstate, const int & decrestate)
{
   colours[increstate] += 1;
   colours[decrestate] -= 1;
}
                                                  
