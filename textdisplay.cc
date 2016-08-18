#include <iostream>
#include <sstream>
#include "textdisplay.h"
using namespace std;

  TextDisplay::TextDisplay(int n): View(n)
  {
   theDisplay = new char *[n]; 
   for ( int i = 0 ; i < n; i++)
   { // each row
      theDisplay[i] = new char [n]; //allocate n columns
      for ( int j = 0 ; j < n; j++) 
      { 
	//each column in theDisplay[i]
	theDisplay [i][j] = '0';
      }
   }
  }  //one arg constructor where the parameter is the gridSize

  TextDisplay::~TextDisplay()
  {
   for ( int i = 0; i < gridSize; i++) 
   {
      delete[] theDisplay[i];
   }
   delete[] theDisplay ;
  }  //dtor
  
  /*
   * The Controller calls notify to update the (row,column) location to be ch
   */
  void TextDisplay::notify(int row, int column, char ch)
  {
     theDisplay[row][column]=ch;
  }

  /*
   * Prints the grid as specified in the assignment specification.
   */
  void TextDisplay::print(std::ostream &out) const 
  {
   for ( int i = 0 ; i < gridSize; i++)
   { 
      for ( int j = 0 ; j < gridSize; j++) 
      { 
	out<<theDisplay[i][j];
       }
       out<<endl;
   }
  }


