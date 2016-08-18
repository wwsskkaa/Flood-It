#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "cell.h"
/*
 * Abstract class to allow Game to send noticiations to a registered object
 */
class GameNotification {
  public:
    virtual void notify(int row, int column, unsigned int state) = 0;
};

const int NUMCOLOR = 5;

class Game {
  Cell **theGrid;  // The actual grid (2 dimensional array of Cell OBJECTS).
  int gridSize;    // Size of the grid.

  /*
   * The following field helps track how the game has progressed.
   * The field should track how many Cells of the grid are of each color.
   * Whenever a Cell changes color, the corresponding color count should be updated.
   */
  unsigned int colours[NUMCOLOR];
  GameNotification *notification;  // object registered for notifications
  // Add private members, if necessary.

  void clearGame();   // Frees the grid.
  void initNeighbours(const int ro,const int col,const int last);

 public:
  Game();
  ~Game();
  void printColours();
  /*
   * Receive update notification from Cells.
   */
  void notify(int row, int column, unsigned int oldState, unsigned int newState);
  int getGridSize();
  void updateColours(const int & increstate, const int & decrestate);  
  /* 
   * The following method is used to determine if the game has been won.
   * An, inefficient implementation would be to use nested for loops to determine 
   * that all Cells in theGrid are of the same color.
   * A more efficient approach is to compute this information during the game as 
   * Cells change colors using the colors array from above.
   */
  bool isWon() const;
  Cell* findNeighbours(const std::string n, const int i, const int j);
  void init(int n, GameNotification *gameNotification); // Sets up an n x n grid.  Clears old grid, if necessary.
  void change(const int & state);  // Changes (0,0) and all appropriate neighbours to state
  void init(int row, int column, int state); //Called by Controller:init in response to initialization requests when game is in init mode
};

#endif
